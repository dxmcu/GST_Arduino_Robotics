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
#include <NewPing.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Define Constants

const byte LEFT_BUMP_PIN = 47;    // Define DIGITAL Pins for left
const byte RIGHT_BUMP_PIN = 46;   // and right bump sensors

const byte FORWARD_SPEED = 125;   // Define normal speeds
const byte BACKWARD_SPEED = 100;  // and backup/turn speed
const int  TURN_DURATION = 600;   // Turn length in milliseconds

// Define 'ports' for motors.
const byte LEFT_MOTOR_PORT = 3;
const byte RIGHT_MOTOR_PORT = 1;
// Create pointers to motor control objects
Adafruit_DCMotor *motorLeft = AFMS.getMotor(LEFT_MOTOR_PORT);
Adafruit_DCMotor *motorRight = AFMS.getMotor(RIGHT_MOTOR_PORT);

NewPing sonic(50, 51); 


void setup(void){
  AFMS.begin();  // create with the default frequency 1.6KHz
  // Turn off all motors to start, just a good habit
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
  Serial.begin(9600);  //Begin serial communcation
  
  /*Set up Bump Pins with Arduino internal pullup resistors
    This will make them always high unless a bump switch is hit, 
    which will make a connection to ground and they will read low. */
  pinMode(LEFT_BUMP_PIN,INPUT_PULLUP);
  pinMode(RIGHT_BUMP_PIN,INPUT_PULLUP);

  delay(2000);  // Two second delay to get the robot ready
}


void loop(){
  /*  Assuming no switches closed initially.  Drive forward: */
  motorLeft->setSpeed(FORWARD_SPEED);
  motorRight->setSpeed(FORWARD_SPEED);  
  
  /*int howFar = sonic.ping_in();
  Serial.println(howFar);*/
  while( digitalRead(LEFT_BUMP_PIN) && digitalRead(RIGHT_BUMP_PIN)) {
    
    motorLeft->run(FORWARD);
    motorRight->run(FORWARD);
    
    motorLeft->setSpeed(FORWARD_SPEED);
    motorRight->setSpeed(FORWARD_SPEED);  
    Serial.println("Good");
  }
  
  if( (! digitalRead(RIGHT_BUMP_PIN) ) ) { // the RIGHT side switch was bumped
    backUp(1000);
    spin(-90., 175, *motorLeft, *motorRight);
        
    motorLeft->run(RELEASE);               // Then stop power to the motors      
    motorRight->run(RELEASE);              // and move to next section of code
    
    Serial.println("WOrks?");
  }
  
  else if(! digitalRead(LEFT_BUMP_PIN)) {
    backUp(1000);
    
    spin(90, 150, *motorLeft, *motorRight);
    
    motorLeft->run(RELEASE);               // Then stop power to the motors
    motorRight->run(RELEASE);              // and move to next section of code
  }
  
  else if ( (howFar > 0) && (howFar < 5) ) {
    backUp(1000);
    
    spin(180, 175, *motorLeft, *motorRight);
    
        
    motorLeft->run(RELEASE);               // Then stop power to the motors      
    motorRight->run(RELEASE);              // and move to next section of code
  }

}



void backUp(int howLong) { 
    motorLeft->run(BACKWARD);
    motorRight->run(BACKWARD);
    
    motorLeft->setSpeed(BACKWARD_SPEED); 
    motorRight->setSpeed(BACKWARD_SPEED);
    
    delay(howLong);                  // for specified duration
    motorLeft->run(RELEASE);               // Then stop power to the motors
    motorRight->run(RELEASE);              // and move to next section of code
}



  
  
  

