
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <math.h>
#include <breadboardbot.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Define 'ports' for motors.
const byte LEFT_MOTOR_PORT = 3;
const byte RIGHT_MOTOR_PORT = 1;
// Create pointers to motor control objects
Adafruit_DCMotor *motorLeft = AFMS.getMotor(LEFT_MOTOR_PORT);
Adafruit_DCMotor *motorRight = AFMS.getMotor(RIGHT_MOTOR_PORT);

//Constants
const int MOVING_SPD = 75;
const int SPIN_SPD = 130;

void setup(void) {
  AFMS.begin();  // create with the default frequency 1.6KHz
  // Turn off all motors to start, just a good habit
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);

  delay(1000);  // One second delay to get the robot ready
}


void loop() 
{
  toRightLeft();
  //delay(1000);
  //nowKick();
  //delay(1000);
  //walkItByYourself();

  while(1){}
}


void toRightLeft () {
  //spin(90, SPIN_SPD, *motorLeft, *motorRight);
  //motorLeft->run(RELEASE);
  //motorRight->run(RELEASE);
  //motorLeft->setSpeed(MOVING_SPD);
  //motorRight->setSpeed(MOVING_SPD);
  //motorLeft->run(FORWARD);
  //motorRight->run(FORWARD);
  //delay(2000);
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
  
  spin(180., SPIN_SPD, *motorLeft, *motorRight);
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
  motorLeft->setSpeed(MOVING_SPD);
  motorRight->setSpeed(MOVING_SPD);
  motorLeft->run(FORWARD);
  motorRight->run(FORWARD);

  delay(2000);

  spin(90., SPIN_SPD, *motorLeft, *motorRight);
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE); 
}

void nowKick () {
  motorLeft->run(FORWARD);
  motorRight->run(FORWARD);

  spin(45., SPIN_SPD, *motorLeft, *motorRight); 
  motorLeft->run(FORWARD);
  motorRight->run(FORWARD);
  
  motorLeft->setSpeed(MOVING_SPD);
  motorRight->setSpeed(MOVING_SPD);
  delay(1000);

  motorLeft->run(BACKWARD);
  motorRight->run(BACKWARD);
  motorLeft->setSpeed(MOVING_SPD);
  motorRight->setSpeed(MOVING_SPD);
  delay(1000);
  
  motorLeft->run(FORWARD);
  motorRight->run(FORWARD);
  spin(-90., SPIN_SPD, *motorLeft, *motorRight);
  motorLeft->run(FORWARD);
  motorRight->run(FORWARD);
  motorLeft->setSpeed(MOVING_SPD);
  motorRight->setSpeed(MOVING_SPD);
  delay(1000);


  motorLeft->run(BACKWARD);
  motorRight->run(BACKWARD);
  motorLeft->setSpeed(MOVING_SPD);
  motorRight->setSpeed(MOVING_SPD);
  delay(1000);

  motorLeft->run(FORWARD);
  motorRight->run(FORWARD);
  spin(45., SPIN_SPD, *motorLeft, *motorRight);
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);

}

void walkItByYourself() {
  motorLeft->run(FORWARD);
  motorRight->run(FORWARD);
  motorLeft->setSpeed(150);
  motorRight->setSpeed(150);
  delay(2000);
  
  motorLeft->run(BACKWARD);
  motorRight->run(BACKWARD);
  motorLeft->setSpeed(150);
  motorRight->setSpeed(150);
  delay(2000);
  
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
  
  
}

