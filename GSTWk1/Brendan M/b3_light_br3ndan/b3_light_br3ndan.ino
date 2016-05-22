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

// Define 'ports' for motors.
const byte LEFT_MOTOR_PORT = 3;
const byte RIGHT_MOTOR_PORT = 1;

// Create pointers to motor control objects
Adafruit_DCMotor *motorLeft = AFMS.getMotor(LEFT_MOTOR_PORT);
Adafruit_DCMotor *motorRight = AFMS.getMotor(RIGHT_MOTOR_PORT);


void setup(void) {
  AFMS.begin();  // create with the default frequency 1.6KHz
  // Turn off all motors to start, just a good habit
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);

  pinMode(47, INPUT_PULLUP);
  pinMode(46, INPUT_PULLUP);

  Serial.begin(9600);  //Begin serial communcation
}

void loop() {
  /*  First determine the relative light levels and print the
      results out to the serial monitor */
  int leftLight = analogRead(LEFT_PR_PIN);
  int rightLight = analogRead(RIGHT_PR_PIN);

  /* Now that we have some light levels, make each motor's speed
     a function of light level and drive either towards or
     away from the light depending on the value of PHOTOAXIS  */

  int lightLeft = map(rightLight, 0 , 1024, 100, 200);
  int lightRight = map(leftLight, 0 , 1024, 100, 200);

  int newLeft = map(lightLeft, 100 , 200, 0, 9);
  int newRight = map(lightRight, 100, 200, 0, 9);

  //Figuring out the strongest, and by how much.
  int difference;
  int priority; // 0 stands for left, 1 for right
  if (newLeft > newRight) {
    difference = newLeft - newRight;
    priority = 0;
  } else {
    difference = newRight - newLeft;
    priority = 1;
  }


  motorLeft->run(FORWARD);
  motorRight->run(FORWARD);
  if ( (priority == 0) && (difference >= 1) ) {

    pivot(60., lightLeft, *motorLeft, *motorRight);
    motorLeft->run(RELEASE);
    motorRight->run(RELEASE);
  } else if (  (priority == 1) && (difference >= 1) ) {

    pivot(-60., lightRight, *motorLeft, *motorRight);
    motorLeft->run(RELEASE);
    motorRight->run(RELEASE);
  } else {

    motorLeft->setSpeed(lightLeft);
    motorRight->setSpeed(lightRight);
  }

  if ( (! digitalRead(46) ) ) { // the RIGHT side switch was bumped
    backUp(500);
    spin(-90., 200, *motorLeft, *motorRight);

    motorLeft->run(RELEASE);               // Then stop power to the motors
    motorRight->run(RELEASE);              // and move to next section of code

  } else if (! digitalRead(47)) {
    backUp(500);
    spin(90, 200, *motorLeft, *motorRight);

    motorLeft->run(RELEASE);               // Then stop power to the motors
    motorRight->run(RELEASE);              // and move to next section of code
  }


  delay(10); //short delay for faster response to light.
}

/*  /* Find the direction of the strongest light by taking the difference
     between the readings */
// int deltaLight = leftLight - rightLight;

void backUp(int howLong) {
  motorLeft->run(BACKWARD);
  motorRight->run(BACKWARD);

  motorLeft->setSpeed(100);
  motorRight->setSpeed(100);

  delay(howLong);                  // for specified duration
  motorLeft->run(RELEASE);               // Then stop power to the motors
  motorRight->run(RELEASE);              // and move to next section of code
}
