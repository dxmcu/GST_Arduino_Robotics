/* B3_Bump.ino

 Drive the TWO-WHEELED Bread Board Bot (BBbot, B^3)
 forward.  When a whisker bump sensor on either side hits something,
 back up and turn slightly away from that direction and resume
 forward path.

 Arduino: Arduino Mega 256 v3 Clone
 Motor Shield: Adafruit assembled Motor Shield for Arduino v2
 ---->  http://www.adafruit.com/products/1438

 Programmer: Dave Eslinger; June 12, 2015
 Revisions:
*/
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
  Serial.begin(9600);  //Begin serial communcation

  delay(1000);  // Two second delay to get the robot ready
}


void loop() {


  //Running to the right
  toRightLeft();
  delay(2000);
  nowKick();





}


void toRightLeft () {
  spin(90., SPIN_SPD, *motorLeft, *motorRight);
  motorLeft->setSpeed(MOVING_SPD);
  motorRight->setSpeed(MOVING_SPD);
  

  delay(2000);

  spin(180., SPIN_SPD, *motorLeft, *motorRight);
  motorLeft->setSpeed(MOVING_SPD);
  motorRight->setSpeed(MOVING_SPD);

  delay(2000);

  spin(90., SPIN_SPD, *motorLeft, *motorRight);

  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
}

void nowKick () {
  motorLeft->run(FORWARD);
  motorRight->run(FORWARD);

  spin(45., SPIN_SPD, *motorLeft, *motorRight);
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);

  motorLeft->setSpeed(MOVING_SPD);
  motorRight->setSpeed(MOVING_SPD);
  delay(1000);

  motorLeft->run(BACKWARD);
  motorRight->run(BACKWARD);
  motorLeft->setSpeed(MOVING_SPD);
  motorRight->setSpeed(MOVING_SPD);
  delay(1000);
  
  spin(-90., SPIN_SPD, *motorLeft, *motorRight);
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
  
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




