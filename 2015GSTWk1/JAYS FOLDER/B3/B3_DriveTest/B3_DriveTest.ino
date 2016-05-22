/* B3_DriveTest.ino
   Drive the TWO-WHEELED Bread Board Bot (BBbot, B^3)
   in a series of timed intervals, stopping at end of each.
   Start new one after a 5 second time interval.

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

// Define Pin Assignments
#define TESTPIN 33
// Define Constants
#define TESTTIME 1000
#define TRIALWAITTIME 5000
#define TREATMENTWAITTIME 3000

// Define 'ports' for motors.
const byte LEFTMOTORPORT = 3;
const byte RIGHTMOTORPORT = 1;
// Create pointers to motor control objects
Adafruit_DCMotor *motorLeft = AFMS.getMotor(LEFTMOTORPORT);
Adafruit_DCMotor *motorRight = AFMS.getMotor(RIGHTMOTORPORT);

void setup(void){
  AFMS.begin();  // create with the default frequency 1.6KHz
  // Turn off all motors to start, just a good habit
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);

  pinMode(TESTPIN, INPUT_PULLUP);
}

void loop(void){
  
  // delay(2000); // Delay for two seconds to give time to place the robot.
  while(digitalRead(TESTPIN)){}
  /* Autonomous loop for determining power and distance, will
     run through each power 5 times, for replicates, then advance power
     by 50.  Therefore it tests: 50, 100, 150, 200 and 250.
  */
  
  for ( byte leg = 0; leg <= 4; leg++ ) {
    byte speed = 50 + 50*leg;
    for (byte trial = 1; trial <=5; trial++ ) {
      motorLeft->setSpeed(speed);  // Set both speeds
      motorRight->setSpeed(speed);
      motorLeft->run(FORWARD);
      motorRight->run(FORWARD);
      delay(TESTTIME);  // Run for 1 second
      allStop(FORWARD, *motorLeft, *motorRight);
      while(!digitalRead(TESTPIN)){}
      while(digitalRead(TESTPIN)){}
      delay(TREATMENTWAITTIME);
    }
    while(!digitalRead(TESTPIN)){}
    while(digitalRead(TESTPIN)){}
    //delay(TREATMENTWAITTIME);
  }
  // One last loop for full speed, 255, just for fun!
  for (byte trial = 1; trial <=5; trial++ ) {
    motorLeft->setSpeed(255);  // Set both speeds
    motorRight->setSpeed(255);
    motorLeft->run(FORWARD);
    motorRight->run(FORWARD);
    delay(TESTTIME);  // Run for 1 second
    allStop(FORWARD, *motorLeft, *motorRight);
    while(!digitalRead(TESTPIN)){}
    while(digitalRead(TESTPIN)){}
    delay(TREATMENTWAITTIME);
  }
  while(1){}
}
