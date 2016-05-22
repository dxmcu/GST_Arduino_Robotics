/* DriveFirst
Test of driving foward

*/
#include <Wire.h>
#include <Adafruit_MotorShield.h>

void setup() {
  // Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_Motorshield ();
}

//Define Constants
#define TESTIME 1000

const byte SPEED = 200; // Default speedfor motors
//Define 'ports' for motors.
const byte LEFTMOTORPORT = 3;
const byte RIGHTMOTORPORT = 1;
//Create pointers to motor control objects
Adafruit_DCMotor *motoLeft = AFMS.getMotor (LEFTMOTORPORT);
Adafruit_DCMotor *motorRight = AFMS.getMotor (RIGHTMOTORPORT);


void setup(void){
  AFMS.begin(); // create with the default frequency 1.6KHz
  // Turn off all motors to start, just a good habit
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE)
}
  
  void loop(void) {
  // delay(2000); // Delay for two seconds to give time to place the robot.
  
    motorLeft->setSpeed(SPEED); // Set both speeds
    motorRight->setSpeed(SPEED);
    motorLeft->run(FORWARD)
    motorRight->(FORWARD);
delay(TESTIME); // Run for 1 second  
// Turn off all motors to start, just a good habit
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE)
       delay(TESTIME); // Do not drive the motors for 1 second
}

void allStop(int direction) {
  motorLeft->setSpeed(100);  // Note that we reset the speeds here; therefore, 
  motorRight->setSpeed(100); // we need ot reset them in other routine.
  if (direction == FORWARD) {
    motorLeft->run(BACKWARD);
    motorRight->run(BACKWARD);
  }
  else {
    motorLeft->run(BACKWARD);
    motorRight->run(BACKWARD);
  }
  delay(50);
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
  return;
}

