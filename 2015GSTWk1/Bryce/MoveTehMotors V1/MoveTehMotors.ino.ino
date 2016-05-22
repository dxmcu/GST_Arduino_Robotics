// DRIVE THE BREADBOARD BOT
//Include these items
#include <Wire.h>
#include <Adafruit_MotorShield.h>
  Adafruit_MotorShield AFMS = Adafruit_MotorShield();
//Define Constants
  #define TESTTIME 1000
  const byte SPEED = 130;

//Define Motor Ports

    const byte LEFTMOTORPORT = 3;
    const byte RIGHTMOTORPORT = 1;
//Create the pointers for the motors
Adafruit_DCMotor *motorLeft = AFMS.getMotor(LEFTMOTORPORT);
Adafruit_DCMotor *motorRight = AFMS.getMotor(RIGHTMOTORPORT);


//The setup
void setup() {
  AFMS.begin(); // Start by stopping all motors
 delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
    motorLeft->setSpeed(SPEED);
    motorRight->setSpeed(SPEED);
  //Set the speed for the robot
  //What direction to
    motorLeft->run(FORWARD);
    motorRight->run(FORWARD);
      delay(1000);
    motorLeft->run(BACKWARD);
    motorRight->run(BACKWARD);
       delay(2000);
    motorLeft->run(FORWARD);
    motorRight->run(FORWARD);
      delay(1000);
    motorLeft->run(FORWARD);
    motorRight->run(BACKWARD);  
      delay(3000);
    motorLeft->run(BACKWARD);
    motorRight->run(FORWARD);  
      delay(3000);
    motorRight->setSpeed(SPEED);
    motorLeft->setSpeed(100);
    motorLeft->run(FORWARD);
    motorRight->run(FORWARD);
    delay(1000);
    motorRight->setSpeed(SPEED);
    motorLeft->setSpeed(100);
    motorLeft->run(BACKWARD);
    motorRight->run(BACKWARD);
    delay(1000);
    motorRight->setSpeed(100);
    motorLeft->setSpeed(SPEED);
    motorLeft->run(FORWARD);
    motorRight->run(FORWARD);
    delay(1000);
    motorRight->setSpeed(100);
    motorLeft->setSpeed(SPEED);
    motorLeft->run(BACKWARD);
    motorRight->run(BACKWARD);
    delay(1000);
    motorLeft->run(FORWARD);
    motorRight->run(BACKWARD);  
    delay(3000);
    motorLeft->run(BACKWARD);
    motorRight->run(FORWARD);  
    delay(3000);
    motorLeft->run(FORWARD);
    motorRight->run(FORWARD); 
    motorLeft->setSpeed(130);
    motorRight->setSpeed(40);
    delay(5000);
    motorRight->setSpeed(0);
    delay(2000);
    motorLeft->run(BACKWARD);
    motorRight->run(BACKWARD);
    delay(1500);
    motorLeft->run(FORWARD);
    motorRight->run(FORWARD); 
    motorRight->setSpeed(130);
    motorLeft->setSpeed(40);
    delay(5000);
    motorRight->setSpeed(0);
    delay(2000);
    motorLeft->run(FORWARD);
    motorRight->run(FORWARD);
    delay(1500);
    







}
