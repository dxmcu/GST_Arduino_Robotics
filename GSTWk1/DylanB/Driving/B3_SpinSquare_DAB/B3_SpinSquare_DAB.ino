/* B3_SpinSquare.ino
   Drive the TWO-WHEELED Bread Board Bot (BBbot, B^3)
   in a square, stopping at (or near!) end point.

   Arduino: Arduino Mega 256 v3 Clone
   Motor Shield: Adafruit assembled Motor Shield for Arduino v2
   ---->  http://www.adafruit.com/products/1438

   Programmer: Dave Eslinger; June 7, 2015
   Revisions: 
*/
#include <Wire.h>
#include <Adafruit_MotorShield.h> 
#include <math.h> 
#include <breadboardbot.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Define Constants
const byte TESTSPEED = 100;
const byte DIRECTION = TURNLEFT;

// Define 'ports' for motors.
const byte LEFT_MOTOR_PORT = 3;
const byte RIGHT_MOTOR_PORT = 1;
// Create pointers to motor control objects
Adafruit_DCMotor *motorLeft = AFMS.getMotor(LEFT_MOTOR_PORT);
Adafruit_DCMotor *motorRight = AFMS.getMotor(RIGHT_MOTOR_PORT);

void setup(void){
  AFMS.begin();  // create with the default frequency 1.6KHz
  // Turn off all motors to start, just a good habit
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
  pinMode(13, OUTPUT);
}

void loop(void){
  
  for(int i = 0; i < 3; i++){ //delays for three seconds, LED blinking, so you can place the robot
    digitalWrite(13, HIGH);
    delay(500); 
    digitalWrite(13, LOW);
    delay(500);
  }
  for(int i = 0; i < 14; i++){ //Blinks really fast when it's about to go.
    digitalWrite(13, HIGH);
    delay(50); 
    digitalWrite(13, LOW);
    delay(50);
  }

  // Autonomous loop for driving in a square
  for ( byte leg = 1; leg <= 4; leg++ ) {
    drive(10., TESTSPEED, *motorLeft, *motorRight);// Forward for 10 inches
    allStop(FORWARD, *motorLeft, *motorRight);
    spin(-90., TESTSPEED, *motorLeft, *motorRight); // 90 deg. to left
    //allStop(FORWARD, *motorLeft, *motorRight);
    spinStop(-90., *motorLeft, *motorRight);
    delay(500);  // Pause for 1/2 a second after turning
  }
  delay(3000);
  for ( byte leg = 1; leg <= 4; leg++ ) {
    drive(10., TESTSPEED, *motorLeft, *motorRight);// Forward for 10 inches
    allStop(FORWARD, *motorLeft, *motorRight);
    spin(90., TESTSPEED, *motorLeft, *motorRight); // 90 deg. to left
//    allStop(FORWARD, *motorLeft, *motorRight);
    spinStop(90., *motorLeft, *motorRight);
    delay(500);  // Pause for 1/2 a second after turning
  }
  while(1){}
}
