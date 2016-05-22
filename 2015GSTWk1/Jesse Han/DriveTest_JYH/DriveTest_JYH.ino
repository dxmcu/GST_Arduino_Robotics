//Breadboard Bot vroom vroom

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <math.h>
#include <breadboardbot.h>

  //Create the motor shield object with the default f2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

  //Define constants
#define TESTTIME 1000

  //Default speed for motors
const byte SPEED = 200;

  //Define 'ports' for motors.
const byte LEFTMOTORPORT = 3;
const byte RIGHTMOTORPORT = 1;

  //Create pointers to motor control objects
Adafruit_DCMotor *motorLeft = AFMS.getMotor(LEFTMOTORPORT);
Adafruit_DCMotor *motorRight = AFMS.getMotor (RIGHTMOTORPORT);

boolean running;

void setup(void)
{
  AFMS.begin(); //create with the default frequency 1.6KHz
      //Turns off all motors to start, just a good habit
  motorLeft -> run(RELEASE);
  motorRight -> run(RELEASE);   
  
  pinMode (13, OUTPUT);
  
  running = true;
}

void blink (void)
{
  digitalWrite (13, HIGH);
  delay (1000);
  digitalWrite (13, LOW);
  delay (15);
}

void infiniteRun(void)
{
  //Runs infinitely
  motorLeft -> setSpeed (SPEED);  //Set both speeds
  motorRight -> setSpeed (SPEED);
  motorLeft -> run (FORWARD);
  motorRight -> run (FORWARD);
  delay (TESTTIME);  //Runs for 1 second
}

void delayedRun(void)
{
  //Runs infinitely with delay intervals

    //Runs infinitely
  motorLeft -> setSpeed (SPEED);  //Set both speeds
  motorRight -> setSpeed (SPEED);
  motorLeft -> run (FORWARD);
  motorRight -> run (FORWARD);
  delay (TESTTIME);  //Runs for 1 second
  
    //Adds 1 second delays
  motorLeft -> run (RELEASE);
  motorRight -> run (RELEASE);
  delay (TESTTIME);
}

void infiniteDelay (void)
{  
  //Runs once then delays infinitely
    
    //Runs once
  motorLeft -> setSpeed (SPEED);  //Set both speeds
  motorRight -> setSpeed (SPEED);
  motorLeft -> run (FORWARD);
  motorRight -> run (FORWARD);
  delay (TESTTIME);  //Runs for 1 second

    //Delays infinitely
  motorLeft -> run (RELEASE);
  motorRight -> run (RELEASE);
  while (true) {}
}
  
void circle(void)
{
    //Do rad doughnuts
  motorLeft -> setSpeed (255);  //Set both speeds
  motorRight -> setSpeed (255);
  motorLeft -> run (FORWARD);
  motorRight -> run (BACKWARD);  //Set one wheel to run backwards for maximum doughnuttage
  delay (6000);  //Runs for 6 seconds
  /*  motorLeft -> run (RELEASE);
  motorRight -> run (RELEASE);
  delay (TESTTIME);  */
}

void square (void)
{  
  delay(1000); // Delay for a second to give time to place the robot.

  // Autonomous loop for driving in a square
  for ( byte leg = 1; leg <= 4; leg++ ) 
    {
      drive(12, (100), *motorLeft, *motorRight);// Forward for 10 inches
      pivot(-80., (100), *motorLeft, *motorRight); // 90 deg. to left
      allStop(FORWARD, *motorLeft, *motorRight);
      delay(500);  // Pause for 1/2 a second after turning
    }
  delay(2000);
  for ( byte leg = 1; leg <= 4; leg++ ) {
    drive(12., (100), *motorLeft, *motorRight);// Forward for 10 inches
    pivot(80., (100), *motorLeft, *motorRight); // 90 deg. to left
    allStop(FORWARD, *motorLeft, *motorRight);
    delay(500);  // Pause for 1/2 a second after turning
  }
}

void loop(void) 
{
  //while (running == true)
  //{
    //blink();
    circle();
  //}
}
