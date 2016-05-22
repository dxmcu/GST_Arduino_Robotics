/*Drive the two wheel bread-board bot forward. Test one. 
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>
  // Create the motor shield object with the default I2C address
 Adafruit_MotorShield AFMS =Adafruit_MotorShield();
  // Define Constants
#define TESTTIME 1000
const byte SPEED = 150; //Default speed for motors
  //Define 'ports' for motors.
const byte LEFTMOTORPORT = 1;
const byte RIGHTMOTORPORT = 3;
  //Create pointers to motor control objects.
  Adafruit_DCMotor *motorLeft = AFMS.getMotor(LEFTMOTORPORT);
  Adafruit_DCMotor *motorRight = AFMS.getMotor(RIGHTMOTORPORT);

void setup(void) {
  AFMS.begin(); // create with the default freqency 1.6KHz
  // Turn off all motors th start, just a good habit
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
}

void loop(void) {
  // delay(2000); // Delay for two seconds to give time to place the robot.
    int testwhile = 0;
    motorLeft->setSpeed(SPEED); //set both speed
    motorRight->setSpeed(SPEED);
    motorBack->setSpeed(SPEED);
    motorLeft->run(FORWARD);
    motorRight->run(FORWARD);
    motorBack->run(Backwords);
    delay(TESTTIME);  //run for 1 second
    /* I took off the turn off all motors i got this idea because i was running bump and 
    i lost my feeliers */
    //Turn off all motors
    // motorLeft->run(RELEASE);
    // motorRight->run(RELEASE);
     //delay(TESTTIME); //Do no drive the motors for 1 second.
    //while(testwhile < 3) {
   // testwhile++;

    }

    

    
 
     
