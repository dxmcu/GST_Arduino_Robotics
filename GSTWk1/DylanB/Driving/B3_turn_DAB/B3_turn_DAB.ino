/*
rotates your robot 180 degrees 3 times

coded by Dylan Bruss
*/

//include packages
#include <Wire.h>
#include <Adafruit_MotorShield.h> 
#include <math.h> 

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

//define motor ports 
const byte LEFTMOTORPORT = 3;
const byte RIGHTMOTORPORT = 1;

// Create pointers to motor control objects
Adafruit_DCMotor *motorLeft = AFMS.getMotor(LEFTMOTORPORT);
Adafruit_DCMotor *motorRight = AFMS.getMotor(RIGHTMOTORPORT);

void setup() {
  AFMS.begin();  // create with the default frequency 1.6KHz
  // Turn off all motors to start, just a good habit
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
}

void loop() {
  motorLeft->setSpeed(50);
  motorRight->setSpeed(50);
  
  motorLeft->run(FORWARD);
  motorRight->run(FORWARD);
  
  delay(duration_per_dist(12, 50));
  
  allStop(FORWARD);
  delay(2000);
}

void allStop(int direction) {
  /* This subroutine stops the robot by reversing the mtors for short
     duration.  Parameter is what direction it is initially going.
  */
  motorLeft->setSpeed(100);  // Note that we reset the speeds here; therefore, 
  motorRight->setSpeed(100); // we need to reset them in calling routine.
  if (direction == FORWARD) {
    motorLeft->run(BACKWARD);
    motorRight->run(BACKWARD);
  }
  else {
    motorLeft->run(FORWARD);
    motorRight->run(FORWARD);
  }
  delay(50);
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
  return;
}

float duration_per_dist(float distance, byte speed){
  /* find drive time in milliseconds from relationships developed from
  observations of distance/time */
  float dist_per_sec = (0.117 * float(speed))-1.5;
  float duration = abs(distance) / dist_per_sec;
  return duration * 1000.0;
}

void turnInPlace(){
  
}

void turnPivotLeft(){
  
}

void turnPivotRight(){
  
}
