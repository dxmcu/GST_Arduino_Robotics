/* B3_HoloSquare.ino
   This is a test sketch for autonomous driving mode of
   the three-wheeled drive Bread Board Bot (BBbot, B^3) 

   Arduino: Arduino Mega 256 v3 Clone
   Motor Shield: Adafruit assembled Motor Shield for Arduino v2
   ---->  http://www.adafruit.com/products/1438

   Programmer: Dave Eslinger; December 2, 2014
   Revisions: 2015, May 25:   Changed for new motor configuration
              2015, June 12:  Changed into B3_ code style for GoSciTech 2015.
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

// Define global variables
float theta;
int direction;
float magnitude;
float duration;

byte motorLeftdir;
byte motorBackdir;
byte motorRightdir;

void setup(void){
  AFMS.begin();  // create with the default frequency 1.6KHz
  // Turn off all motors to start, just a good habit
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);



void setup(void){
  AFMS.begin();  // create with the default frequency 1.6KHz
  // Turn off all motors
  motorLeft->run(RELEASE);
  motorBack->run(RELEASE);
  motorRight->run(RELEASE);
}

void loop(void){
  // Section for taking commands from Serial Input
  // N.B.  Need to comment out one bracket at end for the autonomous loop below
    /* if (Serial.available() > 0) { */
    /*   direction = Serial.parseInt(); */
    /*   theta = ( M_PI * direction ) / 180. ; */
    /*   magnitude = Serial.parseInt(); */
    /*   duration = Serial.parseInt(); */
    /* }  */

  // Autonomous loop for driving in a square
  for ( byte leg = 1; leg < 6; leg++ ) {
    duration = 2;
    magnitude = 50;
    //    brake = 0; // No braking
    switch (leg) {
    case 1: // Move forward
      direction = 0.;
      break;
    case 2: // Move right
      direction = 90.;
      break;
    case 3: // Move backward
      direction = 180.;
      break;
    case 4: // Move left
      direction = -90.;
      break;
    default: // Stop and pause at starting point
      magnitude = 0;
      duration = 4;
      direction = 0;
      //      brake = 1; // hard stop
    }
    theta = ( M_PI * direction ) / 180. ; 

  if( duration > 0 ) {
    Serial.print("direction = ");
    Serial.print(direction);
    Serial.print(", theta = ");
    Serial.print(theta);
    Serial.print(", magnitude = ");
    Serial.print(magnitude);
    Serial.print(" and duration = ");
    Serial.println(duration);
      
    float vx = magnitude * sin(theta);
    float vy = magnitude * cos(theta);
    Serial.print("vx, vy = ");
    Serial.print(vx);
    Serial.print(", ");
    Serial.println(vy);
      
    const float sqrt3o2 = 1.0*sqrt(3)/2;
    //STEP 3. Find wheel vectors
    float wB = -vx * .95 ;  // Multiply by fudge factor to prevent rotation if needed
    float wL = 0.5*vx - sqrt3o2 * vy; 
    float wR = 0.5*vx + sqrt3o2 * vy; 
   
    byte wB_speed = (byte) map(abs(wB), 0, 100, 0, 255);
    byte wL_speed = (byte) map(abs(wL), 0, 100, 0, 255);
    byte wR_speed = (byte) map(abs(wR), 0, 100, 0, 255);
    /* Set Motor directions.  For Adafruit V2 Motorshield: 
         1 is Clockwise (Positive motor direction)
         2 is Counterclockwise (Negative vector direction)
	 3 is Brake (May not work)
	 4 is Release = stop power, not driving, but not brake
	 so we can use a logic test since TRUE = 1 and FALSE = 0
    */
    motorBack->run((wB > 0) ? 1: 2 );
    motorLeft->run((wL > 0) ? 1: 2 );
    motorRight->run((wR > 0) ? 1: 2 );

    /* // Set the brakes */   
    /* motorBack->setBrake(brake); */
    /* motorLeft->setBrake(brake); */
    /* motorRight->setBrake(brake); */

    // Set the speeds
    motorBack->setSpeed(wB_speed);
    motorLeft->setSpeed(wL_speed);
    motorRight->setSpeed(wR_speed);
    
    //Print out motor control details
    Serial.print("Speeds F,L,R = ");
    Serial.print(copysign(wB_speed,wB));
    Serial.print(", ");
    Serial.print(copysign(wL,wL_speed));
    Serial.print(", ");
    Serial.println(copysign(wR,wR_speed));

    // Run motors for the duration requested
    delay(1000*duration);
    
  }
  else{ // no duration entered, so stop all motors
    motorBack->setSpeed(0);
    motorLeft->setSpeed(0);
    motorRight->setSpeed(0);
  }
  }  

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
