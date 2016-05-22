/* B3_HoloLineFollow.ino
   This is a test sketch for autonomous driving mode of
   the three-wheeled drive Bread Board Bot (BBbot, B^3), 
   during which, the B^3 follows a line using holonomic driving 

   Arduino: Arduino Mega 256 v3 Clone
   Motor Shield: Adafruit assembled Motor Shield for Arduino v2
   ---->  http://www.adafruit.com/products/1438
*/
#include <Wire.h>
#include <Adafruit_MotorShield.h> 
#include <math.h> 
#include <breadboardbot.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Define Constants

// Define 'ports' for motors.
const byte LEFT_MOTOR_PORT = 3;
const byte RIGHT_MOTOR_PORT = 1;
const byte BACK_MOTOR_PORT = 2;
// Create pointers to motor control objects
Adafruit_DCMotor *motorLeft = AFMS.getMotor(LEFT_MOTOR_PORT);
Adafruit_DCMotor *motorRight = AFMS.getMotor(RIGHT_MOTOR_PORT);
Adafruit_DCMotor *motorBack = AFMS.getMotor(BACK_MOTOR_PORT);


// Line Following
const byte FOLLOW_LEFT_SIDE = 1;
const float HI_LIGHT = 0.80;     // Keep the BRIGHT side of the line ABOVE this
// fraction of the Maximum read by that sensor
const float LO_LIGHT = 0.20;     // Keep the DARK side of the line BELOW this
// fraction of the Maximum read by that sensor

// IO Pins used
const byte LEFT_BUMP_PIN = 47;    // Define DIGITAL Pins for left
const byte RIGHT_BUMP_PIN = 46;   // and right bump sensors
const byte LEFT_IR_LED_PIN = 43;
const byte LEFT_IR_PIN = A11;
const byte RIGHT_IR_LED_PIN = 42;
const byte RIGHT_IR_PIN = A10;

// Define global variables
float theta;
int direction;
float magnitude;
float duration;

byte motorLeftdir;
byte motorBackdir;
byte motorRightdir;

int leftIR;
int minLeftIR = 1026;
int maxLeftIR = -1024;
int rightIR;
int minRightIR = 1026;
int maxRightIR = -1024;
float brightLeft;
float darkRight;
float leftRange;
float rightRange;

byte lightLoop = 0;
byte darkLoop = 0;

void setup(void){
  AFMS.begin();  // create with the default frequency 1.6KHz
  // Turn off all motors
  motorLeft->run(RELEASE);
  motorBack->run(RELEASE);
  motorRight->run(RELEASE);
  Serial.begin(9600);
  
  /*Set up Bump Pins with Arduino internal pullup resistors
    This will make them always high unless a bump switch is hit,
    which will make a connection to ground and they will read low. */
  pinMode(LEFT_BUMP_PIN, INPUT_PULLUP);
  pinMode(RIGHT_BUMP_PIN, INPUT_PULLUP);

  /* Define IR LED source pins as OUTPUTs and turn on the IR LEDs */
  pinMode(13, OUTPUT);
  pinMode(LEFT_IR_LED_PIN, OUTPUT);
  pinMode(RIGHT_IR_LED_PIN, OUTPUT);
  digitalWrite(LEFT_IR_LED_PIN, HIGH);
  digitalWrite(RIGHT_IR_LED_PIN, HIGH);

  /* Calibrate the IR sensors
     1) Place over the brightest target and hold down right bumper switch.
     2) Place over the darkest target and hold down right bumper again.
     3) All done!  The program
        calculates the 80% and 20% (or as set by HI_LIGHT% and LO_LIGHT% values)
        target values to keep the sensors at.
  */
  while (digitalRead(RIGHT_BUMP_PIN) == HIGH) {} // Pause until the pin is grounded (our switch)
  while (digitalRead(RIGHT_BUMP_PIN) == LOW||lightLoop < 10) { // Get high light values until the pin
    // is no longer grounded
    leftIR = analogRead(LEFT_IR_PIN);
    rightIR = analogRead(RIGHT_IR_PIN);
    Serial.print(leftIR);
    Serial.print("  = leftIR, Calibrate LIGHT rightIR = ");
    Serial.println(rightIR);
    if ( leftIR > maxLeftIR ) {
      maxLeftIR = leftIR;
    }
    if ( rightIR > maxRightIR ) {
      maxRightIR = rightIR;
    }
    lightLoop++;
  }
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  
  /*Do the same, but over a dark target */
  while (digitalRead(RIGHT_BUMP_PIN) == HIGH) {} // Pause until the pin is grounded (our switch)
  while (digitalRead(RIGHT_BUMP_PIN) == LOW||darkLoop < 10) {   // Get dark light values until the pin
    // is no longer grounded
    leftIR = analogRead(LEFT_IR_PIN);
    rightIR = analogRead(RIGHT_IR_PIN);
    Serial.print(leftIR);
    Serial.print("  = leftIR, Calibrate DARK  rightIR = ");
    Serial.println(rightIR);
    if ( leftIR < minLeftIR ) {
      minLeftIR = leftIR;
    }
    if ( rightIR < minRightIR ) {
      minRightIR = rightIR;
    }
    darkLoop++;
  }
  leftRange = maxLeftIR - minLeftIR;
  rightRange = maxRightIR - minRightIR;
  brightLeft = maxLeftIR - ((1.0 - HI_LIGHT) * leftRange);
  darkRight = minRightIR + (LO_LIGHT * rightRange);

  while ( digitalRead(LEFT_BUMP_PIN) == HIGH) {} // Pause until you trigger the left bump switch
  delay(1000);                      // Then wait 1 second and start line following.
}

void loop(void){
    
    leftIR = analogRead(LEFT_IR_PIN);
    rightIR = analogRead(RIGHT_IR_PIN);
    
    Serial.print(leftIR);
    Serial.print("  = leftIR,brightLeft = ");
    Serial.print(brightLeft);
    Serial.print(", darkRight = ");
    Serial.print(darkRight);
    Serial.print(", rightIR = ");
    Serial.println(rightIR);
    
    motorLeft->setSpeed(100);
    motorRight->setSpeed(100);
    motorBack->setSpeed(100);
    
    if(leftIR < brightLeft ){
      motorBack->run(1);
      motorLeft->setSpeed(50);
    }else if(rightIR > darkRight){
      motorBack->run(2);
      motorRight->setSpeed(50);
    }else{
      motorBack->run(RELEASE);
    }
    motorLeft->run(FORWARD);
    motorRight->run(FORWARD);
}


/*
 SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
/* void serialEvent() { */
/*   while (Serial.available()) { */
/*     // get the new byte: */
/*     char inChar = (char)Serial.read();  */
/*     // add it to the inputString: */
/*     inputString += inChar; */
/*     // if the incoming character is a newline, set a flag */
/*     // so the main loop can do something about it: */
/*     if (inChar == '\n') { */
/*       stringComplete = true; */
/*     }  */
/*   } */
/* } */
