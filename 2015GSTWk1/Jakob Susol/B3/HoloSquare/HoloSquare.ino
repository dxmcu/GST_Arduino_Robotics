/* HoloSquare.ino
   This is a test sketch for autonomous driving mode of
   the three-wheeled drive Bread Board Bot (BBbot, B^3) 

   Arduino: Arduino Mega 256 v3 Clone
   Motor Shield: Adafruit assembled Motor Shield for Arduino v2
   ---->  http://www.adafruit.com/products/1438

   Programmer: Dave Eslinger; December 2, 2014
   Revisions: May 25, 2015
*/
#include <Wire.h>
#include <Adafruit_MotorShield.h> 
//#include <"utility/Adafruit_PWMServoDriver.h"
#include <math.h>

float theta;
int direction;
float magnitude;
float duration;
byte brake;
byte mLdir;
byte mBdir;
byte mRdir;

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Define 'ports' M1, M2, M3 or M4 for motors.
Adafruit_DCMotor *mL = AFMS.getMotor(3);
Adafruit_DCMotor *mB = AFMS.getMotor(2);
Adafruit_DCMotor *mR = AFMS.getMotor(1);


void setup(void){
  Serial.begin(9600);
  AFMS.begin();  // create with the default frequency 1.6KHz
  // Turn off all motors
  mL->run(RELEASE);
  mB->run(RELEASE);
  mR->run(RELEASE);
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
    mB->run((wB > 0) ? 1: 2 );
    mL->run((wL > 0) ? 1: 2 );
    mR->run((wR > 0) ? 1: 2 );

    /* // Set the brakes */
    /* mB->setBrake(brake); */
    /* mL->setBrake(brake); */
    /* mR->setBrake(brake); */

    // Set the speeds
    mB->setSpeed(wB_speed);
    mL->setSpeed(wL_speed);
    mR->setSpeed(wR_speed);
    
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
    mB->setSpeed(0);
    mL->setSpeed(0);
    mR->setSpeed(0);
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
