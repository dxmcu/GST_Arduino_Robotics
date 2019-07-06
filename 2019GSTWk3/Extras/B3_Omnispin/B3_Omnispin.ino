/* B3_Omnispin.ino
This is a test sketch for autonomous driving mode of
the three-wheeled drive Bread Board Bot (BBbot, B^3)

Arduino: Arduino Mega 256 v3 Clone
Motor Shield: Adafruit assembled Motor Shield for Arduino v2
---->  http://www.adafruit.com/products/1438

Programmer: Dave Eslinger; 2019, July 5

*/
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <math.h>
#include <BreadBoardBot.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Define Constants
// IO Pins used
const byte LEFT_BUMP_PIN = 47;    // Define DIGITAL Pins for left
const byte RIGHT_BUMP_PIN = 46;   // and right bump sensors

// Define 'ports' for motors.
const byte LEFT_MOTOR_PORT = 3;
const byte RIGHT_MOTOR_PORT = 1;
const byte BACK_MOTOR_PORT = 2;
// Create pointers to motor control objects
Adafruit_DCMotor *motorLeft = AFMS.getMotor(LEFT_MOTOR_PORT);
Adafruit_DCMotor *motorRight = AFMS.getMotor(RIGHT_MOTOR_PORT);
Adafruit_DCMotor *motorBack = AFMS.getMotor(BACK_MOTOR_PORT);

// Define global variables
float direction;       // Velocity Vector Angle (DEGREES) from forward to drive
float magnitude;       // Magnitude (0-100) of movement vector in given direction
float duration;        // Duration to drive at given velocity vector

byte motorLeftdir;     // Clockwise or Counter clockwise for the 3 wheels
byte motorBackdir;
byte motorRightdir;

void setup(void) {
  Serial.begin(9600);  //Begin serial communcation
  AFMS.begin();  // create with the default frequency 1.6KHz
  // Turn off all motors
  motorLeft->run(RELEASE);
  motorBack->run(RELEASE);
  motorRight->run(RELEASE);
  /*Set up Bump Pins with Arduino internal pullup resistors
  This will make them always high unless a bump switch is hit,
  which will make a connection to ground and they will read low. */
  pinMode(LEFT_BUMP_PIN, INPUT_PULLUP);
  pinMode(RIGHT_BUMP_PIN, INPUT_PULLUP);
  // Now wait for the RIGHT bumpsensor to be pressed
  while(digitalRead(RIGHT_BUMP_PIN)) {};
  while(digitalRead(RIGHT_BUMP_PIN)!= HIGH) {};
  delay(600); // Bump pin triggered and released, just give 0.2 seconds to get hands out of the way.
  Serial.println("Beginning");
}
void loop(void) {
  // Section for taking commands from Serial Input
  // N.B.  Need to comment out one bracket at end for the autonomous loop below
  /* if (Serial.available() > 0) { */
  /*   direction = Serial.parseInt(); */
  /*   magnitude = Serial.parseInt(); */
  /*   duration = Serial.parseInt(); */
  /* }  */

  // loop for driving an arbitrary pattern
  for ( byte leg = 1; leg < 9; leg++ ) {
    duration = 1000;              // Constants per leg: One second/leg
    magnitude = 150;              //                    50% max power
    bool brake = false;           //                    No braking
    switch (leg) {
      case 1: // Move forward 45 degrees right
      Serial.println("Forward 45 degrees right");
      direction = 45.;
      omnidrive(direction, magnitude, duration, brake, motorLeft, motorRight, motorBack);
      break;
      case 2: // Move forward 45 degrees left
      Serial.println("Forward 45 degrees left");
      direction = 90.;
      omnidrive(direction, magnitude, duration, brake, motorLeft, motorRight, motorBack);
      break;
      case 3: // Move backward
      Serial.println("Back");
      direction = 180.;
      omnidrive(direction, magnitude, duration, brake, motorLeft, motorRight, motorBack);
      break;
      case 4: // Move left
      Serial.println("Left");
      direction = -90.;
      omnidrive(direction, magnitude, duration, brake, motorLeft, motorRight, motorBack);
      break;
      case 5: // Spin clockwise for 2 seconds
      Serial.println("Spin for 2 seconds");
      magnitude = 0;
      duration = 2;
      direction = 0;
      brake = true; // hard stop
      omnidrive(magnitude, duration, brake, motorLeft, motorRight, motorBack);
      break;
      case 6: // Spin counterclockwise for 2 seconds
      Serial.println("Spin for 2 seconds");
      magnitude = 0;
      duration = 2;
      direction = 0;
      brake = true; // hard stop
      omnispin(magnitude, duration, brake, motorLeft, motorRight, motorBack);
      break;
      default: // Stop and pause for 4 seconds at starting point
      Serial.println("Spin for 2 seconds");
      magnitude = 0;
      duration = 2;
      direction = 0;
      brake = true; // hard stop
      omnidrive(magnitude, duration, brake, motorLeft, motorRight, motorBack);
    }
    // omnidrive(magnitude, duration, brake, motorLeft, motorRight, motorBack);

  }
  // Loop complete, so stop until LEFT bumper triggered and released, then rerun
  while(digitalRead(LEFT_BUMP_PIN)) {};  // Wait until pushed
  while(!digitalRead(LEFT_BUMP_PIN)) {}; // and released
  delay (600);                           // and 0.2 seconds to get out of the way
}
