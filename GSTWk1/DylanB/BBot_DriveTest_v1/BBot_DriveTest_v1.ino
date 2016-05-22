/*
Drive the TWO-WHEELED model of the bread board bot (BBbot/B^3) 

Uses Arduino Mega 2560 v3 
*/
// import/include packages
#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); // create a new "Adafruit_MotorShield" object called "AFMS"
int count = 20; // set the integer "count" to 20

// Define Constants
#define TESTTIME 1000
const byte SPEED = 200; // default speed for motors

// Define "ports"
const byte LEFTMOTORPORT = 3;
const byte RIGHTMOTORPORT = 1;

// Create pointers to motor control objects
Adafruit_DCMotor *motorLeft = AFMS.getMotor(LEFTMOTORPORT);
Adafruit_DCMotor *motorRight = AFMS.getMotor(RIGHTMOTORPORT);

void setup(void) {
  AFMS.begin(); // create with the default frequency 1.6KHz
  // turn off all motors at start (not exactly necessary, just a good habit)
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
  pinMode(13, OUTPUT);
}

void loop(void) {
  uint8_t i;
  // set both the motors speed
  motorLeft->setSpeed(SPEED);
  motorRight->setSpeed(SPEED);
  motorLeft->run(FORWARD);
  motorRight->run(BACKWARD);
  digitalWrite(13, HIGH); // turn LED on while moving
  delay(TESTTIME); // Run for 1 second
  
  // turn off the motors
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
  digitalWrite(13, LOW); // turn LED off while stopped
  delay(TESTTIME); //Do not drive 
}
