/*Drive the two wheel bread-board bot forward. Test one.
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>
  // Create the motor shield object with the default I2C address
 Adafruit_MotorShield AFMS =Adafruit_MotorShield();
  // Define Constants
#define TESTTIME 1000
byte SPEED = 100; //Default speed for motors
  //Define 'ports' for motors.
const byte LEFTMOTORPORT = 1; //Changed because motors are wired backwards and this was eaiser to change
const byte RIGHTMOTORPORT = 3; //Changed because motors are wired backwards and this was eaiser to change
  //Create pointers to motor control objects.
  Adafruit_DCMotor *motorLeft = AFMS.getMotor(RIGHTMOTORPORT); 
  Adafruit_DCMotor *motorRight = AFMS.getMotor(LEFTMOTORPORT);

void setup(void) {
  AFMS.begin(); // create with the default freqency 1.6KHz
  // Turn off all motors to start, just a good habit
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
}

void loop(void) {
    delay(2000); // Delay for two seconds to give time to place the robot.
    motorLeft->setSpeed(SPEED); //set both speed
    motorRight->setSpeed(SPEED);
    motorLeft->run(FORWARD);
    motorRight->run(FORWARD);
    delay(TESTTIME);  //run for 1 second
    //Turn off all motors
     motorLeft->run(RELEASE);
     motorRight->run(RELEASE);
     delay(TESTTIME); //Do not drive the motors for 1 second. 
     motorLeft->setSpeed(SPEED*2); //set both speed
    motorRight->setSpeed(SPEED*2);
    motorLeft->run(FORWARD);
    motorRight->run(FORWARD);
    delay(TESTTIME);  //run for 1 second
    //Turn off all motors
     motorLeft->run(RELEASE);
     motorRight->run(RELEASE);
     delay(TESTTIME); //Do not drive the motors for 1 second. 
}
