#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include "utility/Adafruit_PWMServoDriver.h"
#include <breadboardbot.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();  

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *rightMotor = AFMS.getMotor(1);
Adafruit_DCMotor *leftMotor = AFMS.getMotor(3);

 
void setup() {

  AFMS.begin();  // create with the default frequency 1.6KHz
  
}

void loop() {
  uint8_t i;
  
  delay (1000); //Wait a second to put it down

  for (byte three60 = 0; three60 < 4; three60++) {
    pivot(90., 100, *leftMotor, *rightMotor);
    
    rightMotor->run(RELEASE);
    leftMotor->run(RELEASE);
    
    delay(2000);
  }
  
  while(1){}


}




