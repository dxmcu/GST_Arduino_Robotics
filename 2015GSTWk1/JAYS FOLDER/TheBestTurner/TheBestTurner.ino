// DRIVE THE BREADBOARD BOT
//Include these items
#include <Wire.h>
#include <Adafruit_MotorShield.h>
  Adafruit_MotorShield AFMS = Adafruit_MotorShield();
//Define Constants
  #define TESTTIME 1000
  const byte SPEED = 150;

//Define Motor Ports

    const byte LEFTMOTORPORT = 3;
    const byte RIGHTMOTORPORT = 1;
//Create the pointers for the motors
Adafruit_DCMotor *motorLeft = AFMS.getMotor(LEFTMOTORPORT);
Adafruit_DCMotor *motorRight = AFMS.getMotor(RIGHTMOTORPORT);


//The setup
void setup() {
  AFMS.begin(); // Start by stopping all motors
 
}

void loop() {
  // put your main code here, to run repeatedly:
    motorLeft->setSpeed(200);
    motorRight->setSpeed(150);
  //Set the speed for the robot
  //What direction to
    motorLeft->run(FORWARD);
    motorRight->run(FORWARD);
     delay(3000);
}
