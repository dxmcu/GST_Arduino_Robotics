/* Drive the two-wheeled BBB Forward
  Programmer:Jakob Susol; June 15, 2015
 */
 #include <Adafruit_MotorShield.h> //included the file
 #include <Wire.h>                //included the file 
  

  //Create the motor shield object with the default I2C address
  Adafruit_MotorShield AFMS = Adafruit_MotorShield();
  
  //Define Constants
#define TESTTIME 1000
const byte SPEED = 150; // Default speed for motors.
// Define 'ports' for motors.
const byte LEFTMOTORPORT = 3;
const byte RIGHTMOTORPORT = 1;
//Create pointers to motor control objects
Adafruit_DCMotor *motorLeft = AFMS.getMotor (LEFTMOTORPORT);
Adafruit_DCMotor *motorRight = AFMS.getMotor (RIGHTMOTORPORT);

void setup (void) {
  AFMS.begin();  //create with the default frequency 1.6KHz
  //Turn off all motors to start, just a good habit.
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
}

void loop(void){
 
 //delay(2000); //Delay for two seconds to give time to place the robot. 

   motorLeft->setSpeed(SPEED);
   motorRight->setSpeed(SPEED);
   motorLeft->run(FORWARD);
   motorRight->run(FORWARD);
    while (true) {
   motorRight->run(RELEASE);
   motorLeft->run(RELEASE);
  }
}
   
   //delay(TESTTIME);  //Run for 1 second
   
   

   
