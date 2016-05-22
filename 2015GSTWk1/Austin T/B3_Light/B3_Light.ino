/* B3_Light.ino

   Drive the TWO-WHEELED Bread Board Bot (BBbot, B^3)
   either towards the light or away from the light, based on readings 
   from two photresistors.  Each resistor is set up in a simple voltage
   divider circuit:
   ----------------------------------------------------

                       PhotoR   ~7.5-10K
               +5  o---/\/\/--.--/\/\/---o GND
                              |
       Sensor Pins o-----------

   ----------------------------------------------------
   Modified from: http://playground.arduino.cc/Learning/PhotoResistor

   Arduino: Arduino Mega 256 v3 Clone
   Motor Shield: Adafruit assembled Motor Shield for Arduino v2
   ---->  http://www.adafruit.com/products/1438

   Programmer: Dave Eslinger; June 7, 2015
   Revisions: 
*/
#include <Wire.h>
#include <Adafruit_MotorShield.h> 
#include <math.h> 
#include <breadboardbot.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Define Constants

const byte LEFT_PR_PIN = A15;    // Define light sensor pins for left 
const byte RIGHT_PR_PIN = A14;   // and right sides

//const bool PHOTOTAXIS = true;

// Define 'ports' for motors.
const byte LEFT_MOTOR_PORT = 3;
const byte RIGHT_MOTOR_PORT = 1;
// Create pointers to motor control objects
Adafruit_DCMotor *motorLeft = AFMS.getMotor(LEFT_MOTOR_PORT);
Adafruit_DCMotor *motorRight = AFMS.getMotor(RIGHT_MOTOR_PORT);


void setup(void){
  AFMS.begin();  // create with the default frequency 1.6KHz
  // Turn off all motors to start, just a good habit
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
  Serial.begin(9600);  //Begin serial communcation
}

void loop(){
  /*  First determine the relative light levels and print the 
      results out to the serial monitor */
  int leftLight = analogRead(LEFT_PR_PIN);
  int rightLight = analogRead(RIGHT_PR_PIN);
  Serial.print(leftLight);           // We can only write ONE thing
  Serial.print(" = left, right = "); // at a time, therefore it takes
  Serial.println(rightLight);        // three statemens to get our output.

  /* Now that we have some light levels, make each motor's speed 
     a function of light level and drive either towards or
     away from the light depending on the value of PHOTOAXIS  */

  motorLeft->setSpeed(map(rightLight,0,500,50,255));
  motorRight->setSpeed(map(leftLight,0,500,50,255));
  byte direction;
  if (PHOTOTAXIS) {
    direction = FORWARD;
  }
  else {
    direction = BACKWARD;
  }
  motorLeft->run(direction);
  motorRight->run(direction);
  
  delay(10); //short delay for faster response to light.
}

/*  /* Find the direction of the strongest light by taking the difference 
     between the readings */
// int deltaLight = leftLight - rightLight;
  
