  
  
  #include <Wire.h>
  #include<Adafruit_MotorShield.h>
  
  //create the motor shield object with the default I2C address
  Adafruit_MotorShield AFMS = Adafruit_MotorShield();
  
  // Define Constants
  #define TESTTIME 1500
  const byte SPEED = 150;  //Default speed for motors
  const byte SPEED2= 160; 
  //Define 'ports' for motors.
  const byte LEFTMOTORPORT = 3;
  const byte RIGHTMOTORPORT = 1; 
// Create pointers to motor control objects
Adafruit_DCMotor  *motorLeft = AFMS.getMotor(LEFTMOTORPORT);
Adafruit_DCMotor  *motorRight = AFMS.getMotor(RIGHTMOTORPORT); 
void setup() {
 AFMS. begin();  // create with default frequency 1.6KHz
  // Turn off all motors to start, just a good habit 
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);

}

void loop(void) {
  delay (1500); // delay motors for 1.5 seconds to set bot down
  motorLeft-> setSpeed(SPEED); // set the speeds for the motors 
  motorRight->setSpeed(SPEED2); 
  motorLeft-> run (FORWARD);// left motor spins bot and right motor doesnt run
  motorRight->run (RELEASE);
  delay(TESTTIME);
  motorLeft->run(RELEASE);// reverse. Right motor spins and left motor doesnt run.
  motorRight-> run(FORWARD);
  delay (TESTTIME);  
  

}
