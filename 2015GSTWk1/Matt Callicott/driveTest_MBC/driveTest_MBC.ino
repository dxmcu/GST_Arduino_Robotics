/* Drive the BreadBoardBot forward ~ Test
  Matt Callicott
  6/15/15
  GSSM
*/

// Includes All External Packages
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <breadboardbot.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Define Constants
#define TESTTIME 1000 //Milliseconds

// Define Constant Bytes
const byte SPEED = 150; // Default Speed For Motors

// Define 'ports' for motors
const byte LEFTMOTORPORT = 3;
const byte RIGHTMOTORPORT = 1;

// Create Pointers To Motor Control Objects
Adafruit_DCMotor *motorLeft = AFMS.getMotor(LEFTMOTORPORT);
Adafruit_DCMotor *motorRight = AFMS.getMotor(RIGHTMOTORPORT);


void setup(void) {
  AFMS.begin(); // Create With The Default Frequency 1.6 KHz
  // Turn OFF All Motors To Start, Just A Good Habit
  motorLeft->run(RELEASE); //Release = off (robot will coast)
  motorRight->run(RELEASE);  
}


// Moves Robot In A Clockwise Motion
void circleRight(void) {
  motorLeft->setSpeed(SPEED);
  motorRight->setSpeed(0);
  motorLeft->run(FORWARD);
  motorRight->run(FORWARD);
  delay(TESTTIME);
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
}

// Moves Robot In A Counter-Clockwise Motion
void circleLeft(void) {
  motorLeft->setSpeed(0);
  motorRight->setSpeed(SPEED);
  motorLeft->run(FORWARD);
  motorRight->run(FORWARD);
  delay(TESTTIME);
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
}

//// Moves Robot In A Reverse Motion
void reverseStraight(void) {
  motorLeft->setSpeed(SPEED);
  motorRight->setSpeed(SPEED + 12);
  motorLeft->run(BACKWARD);
  motorRight->run(BACKWARD);
  delay(1000);
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
}

void loop(void) {
  motorLeft->setSpeed(SPEED); // Set Both Speeds
  motorRight->setSpeed(SPEED * 1.06); //150 = (SPEED + 12) about 6% of power added to right 
  motorLeft->run(FORWARD); // Powers Motors Forward
  motorRight->run(FORWARD); 
  /*
  spin(90, 155, *motorLeft, *motorRight);
  motorLeft->run(RELEASE); // Releases Power
  motorRight->run(RELEASE);*/
}
