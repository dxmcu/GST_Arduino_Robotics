#include <Wire.h>
#include <Adafruit_MotorShield.h> 
#include <math.h> 
#include <breadboardbot.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Define Constants

// Define 'ports' for motors.
const byte LEFT_MOTOR_PORT = 3;
const byte RIGHT_MOTOR_PORT = 1;
const byte BACK_MOTOR_PORT = 2;
// Create pointers to motor control objects
Adafruit_DCMotor *motorLeft = AFMS.getMotor(LEFT_MOTOR_PORT);
Adafruit_DCMotor *motorRight = AFMS.getMotor(RIGHT_MOTOR_PORT);
Adafruit_DCMotor *motorBack = AFMS.getMotor(BACK_MOTOR_PORT);

// Define global variables
float theta;
int direction;
float magnitude;
float duration;

byte motorLeftdir;
byte motorBackdir;
byte motorRightdir;

/* void setup(void){
  AFMS.begin();  // create with the default frequency 1.6KHz
  // Turn off all motors to start, just a good habit
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
*/


void setup(void){
  AFMS.begin();  // create with the default frequency 1.6KHz
  // Turn off all motors
  motorLeft->run(RELEASE);
  motorBack->run(RELEASE);
  motorRight->run(RELEASE);
}

void loop() {
 for ( byte leg = 1; leg < 2; leg++ ) {
  motorLeft->run(FORWARD);
  motorRight->run(FORWARD);
  motorBack->run(FORWARD);
  motorLeft->setSpeed(20);
  motorRight->setSpeed(20);
  motorBack->setSpeed(120);
 }
  delay(1000);
 for ( byte leg = 1; leg < 3; leg++ ) {
  motorLeft->run(FORWARD);
  motorRight->run(FORWARD);
  motorBack->run(FORWARD);
  motorLeft->setSpeed(20);
  motorRight->setSpeed(20);
  motorBack->setSpeed(120);
 }
  delay(500);
  for ( byte leg = 1; leg < 2; leg++ ) {
  motorLeft->run(FORWARD);
  motorRight->run(FORWARD);
  motorBack->run(BACKWARD);
  motorLeft->setSpeed(20);
  motorRight->setSpeed(20);
  motorBack->setSpeed(120);
 }
  delay(1000);
 for ( byte leg = 1; leg < 3; leg++ ) {
  motorLeft->run(FORWARD);
  motorRight->run(FORWARD);
  motorBack->run(BACKWARD);
  motorLeft->setSpeed(20);
  motorRight->setSpeed(20);
  motorBack->setSpeed(120);
 }
  delay(500);
  motorLeft->run(FORWARD);
  motorRight->run(RELEASE);
  motorBack->run(FORWARD);
  motorLeft->setSpeed(120);
  motorRight->setSpeed(RELEASE);
  motorBack->setSpeed(120);
  delay(3000);
  motorLeft->run(BACKWARD);
  motorRight->run(RELEASE);
  motorBack->run(BACKWARD);
  motorLeft->setSpeed(240);
  motorRight->setSpeed(RELEASE);
  motorBack->setSpeed(240);
  delay(1500);
  motorLeft->run(RELEASE);
  motorRight->run(FORWARD);
  motorBack->run(BACKWARD);
  motorLeft->setSpeed(RELEASE);
  motorRight->setSpeed(120);
  motorBack->setSpeed(120);
  delay(3000);
  motorLeft->run(RELEASE);
  motorRight->run(FORWARD);
  motorBack->run(BACKWARD);
  motorLeft->setSpeed(RELEASE);
  motorRight->setSpeed(240);
  motorBack->setSpeed(240);
  delay(1500);
}
