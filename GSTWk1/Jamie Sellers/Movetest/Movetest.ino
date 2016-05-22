// test of driving forward a robot
 
#include <Wire.h> 
#include <Adafruit_MotorShield.h>
  // put your setup code here, to run once: 
  Adafruit_MotorShield AFMS = Adafruit_MotorShield();
  // define constants
  #define TESTTIME 10000
  const byte SPEED1 = 200;
  const byte SPEED2 = 100;
  const byte SPEED3 = 50;
  // define motors' ports
  const byte LEFTMOTORPORT = 3;
  const byte RIGHTMOTORPORT = 1;
  // create pointers to motor conrtol ports
  Adafruit_DCMotor *motorLeft = AFMS.getMotor (LEFTMOTORPORT);
  Adafruit_DCMotor *motorRight = AFMS.getMotor (RIGHTMOTORPORT);

void setup(void) {
  // put your main code here, to run repeatedly:
  AFMS.begin();
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
}
void loop (void)
{
  // delay (2000);
  motorLeft->setSpeed(SPEED3);  // Set both speeds
  motorRight->setSpeed(SPEED1);
  motorLeft->run(FORWARD);
  motorRight->run(FORWARD);
  delay(TESTTIME);  // Run for 1 second
     // Turn off all motors 
    motorLeft->run(RELEASE);
    motorRight->run(RELEASE);
      delay(TESTTIME);  // Do not drive the motors for 1 second  
   while (1); //Does nothing    
}

