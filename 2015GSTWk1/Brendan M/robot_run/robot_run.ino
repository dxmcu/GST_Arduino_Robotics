#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"


//Create Motorshield with defaults
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
  
//Creating motor objects with classes
Adafruit_DCMotor *rightMotor = AFMS.getMotor(1);
Adafruit_DCMotor *leftMotor = AFMS.getMotor(3);

void setup() {
  //Serial
  Serial.begin(9600);
  Serial.println("Enter speed (increments of 25): ");
  
  AFMS.begin(); //Default frequency of 1.6 KHz
 
  //Setting beginning speeds
  rightMotor->setSpeed(80);
  leftMotor->setSpeed(80);
  
  //Telling motors to turn in "Forward" direction
  rightMotor->run(FORWARD);
  leftMotor->run(FORWARD);
  
  //Turning on motor?
   
  
}

void loop() {
  uint8_t i; //Default address
  
  int enterSpeed;
  int newSpeed;
  
  if (Serial.available() > 0) {
     enterSpeed = Serial.read();
     newSpeed = enterSpeed - 48;
     newSpeed = newSpeed * 25;
     
     Serial.println(enterSpeed);
     Serial.println(newSpeed);
     
     if (newSpeed == 0) {
       newSpeed = 0;
       rightMotor->run(RELEASE);
       leftMotor->run(RELEASE);
     } else if (newSpeed == 400) {
       newSpeed = 50;
       rightMotor->run(FORWARD);
       leftMotor->run(FORWARD);
     } else if (newSpeed == 1250){
       newSpeed = 100;
       rightMotor->run(BACKWARD);
       leftMotor->run(BACKWARD);   
     } else {      
       rightMotor->setSpeed(newSpeed);
       leftMotor->setSpeed(newSpeed);
     }
     
  }

}
