/*
  Melody:
  Plays Teen Wolf Theme Song
  circuit:
   6-ohm speaker on digital pin TONE_PIN = 16
  http://www.arduino.cc/en/Tutorial/Tone

  July 10, 2019: Copied and modified for GoSciTech Arduino Robotics
     -- Changed origianl hard-coded pin 8 to TONE_PIN: Dave Eslinger

*/
#include "pitches.h"
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <math.h>
#include <BreadBoardBot.h>


Adafruit_MotorShield AFMS = Adafruit_MotorShield();

const byte TONE_PIN = 14;

const byte LEFT_BUMP_PIN = 47;
const byte RIGHT_BUMP_PIN = 46;
const byte SONIC_TRIGGER_PIN = 60;
const byte SONIC_ECHO_PIN = 61;
const byte LEFT_IR_LED_PIN = 43;
const byte LEFT_IR_PIN = A11;
const byte RIGHT_IR_LED_PIN = 42;
const byte RIGHT_IR_PIN = A10;

const byte FORWARD_SPEED = 110;   // Define normal speeds
const byte BACKWARD_SPEED = 100;  // and backup/turn speed
const int  TURN_DURATION = 600;



// Line Following
const byte FOLLOW_LEFT_SIDE = 1;
const float HI_LIGHT = 0.60;     // Keep the BRIGHT side of the line ABOVE this
// fraction of the Maximum read by that sensor
const float LO_LIGHT = 0.20;     // Keep the DARK side of the line BELOW this
// fraction of the Maximum read by that sensor

// Define 'ports' for motors.
const byte LEFT_MOTOR_PORT = 3;
const byte RIGHT_MOTOR_PORT = 1;
// Create pointers to motor control objects
Adafruit_DCMotor *motorLeft = AFMS.getMotor(LEFT_MOTOR_PORT);
Adafruit_DCMotor *motorRight = AFMS.getMotor(RIGHT_MOTOR_PORT);

/* Define new untrasonic sensor with trigger & echo pins and
   the maximum distance to be sensed. */
//NewPing sonic(SONIC_TRIGGER_PIN, SONIC_ECHO_PIN, MAX_SONIC_DISTANCE);

/* Global Variables */
int leftIR;
int minLeftIR = 1026;
int maxLeftIR = -1024;
int rightIR;
int minRightIR = 1026;
int maxRightIR = -1024;
float brightLeft;
float darkRight;
float leftRange;
float rightRange;

// notes in the melody:
int melody[] = {
  NOTE_G3, NOTE_G3, NOTE_A3, NOTE_B3, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_B3, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_B3, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_B3, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_B3, NOTE_C3, NOTE_A3, NOTE_B3, NOTE_G3, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_B3, NOTE_C3, NOTE_A3, NOTE_B3, NOTE_G3, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_B3, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_B3, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_B3, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_B3, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_B3, NOTE_C3, NOTE_A3, NOTE_B3, NOTE_G3, NOTE_D3, NOTE_E3, NOTE_C3, NOTE_D3, NOTE_B3, NOTE_C3, NOTE_A3, NOTE_G3, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_B3, NOTE_C4, NOTE_A3, NOTE_B3, NOTE_G3, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_B3 , NOTE_C4, NOTE_A3, NOTE_B3, NOTE_G3,
};


int melody_length = sizeof(melody) / sizeof(melody[0]);

// note durations: 6 = quarter note, 6 = eighth note, etc.:
int noteDurations[] = {
  6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 ,  6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 ,  6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 ,  6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 ,
};

void setup() {

  AFMS.begin();  // create with the default frequency 1.6KHz

  // Turn off all motors to start, just a good habit
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
  Serial.begin(9600);  //Begin serial communcation

  /*Set up Bump Pins with Arduino internal pullup resistors
    This will make them always high unless a bump switch is hit,
    which will make a connection to ground and they will read low. */
  pinMode(LEFT_BUMP_PIN, INPUT_PULLUP);
  pinMode(RIGHT_BUMP_PIN, INPUT_PULLUP);

  /* Define IR LED source pins as OUTPUTs and turn on the IR LEDs */
  pinMode(LEFT_IR_LED_PIN, OUTPUT);
  pinMode(RIGHT_IR_LED_PIN, OUTPUT);
  digitalWrite(LEFT_IR_LED_PIN, HIGH);
  digitalWrite(RIGHT_IR_LED_PIN, HIGH);
  
  delay(8000);
  // iterate over the notes of the melody:
  for (int thisNOTE = 0; thisNOTE < melody_length; thisNOTE++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/6, etc.
    int noteDuration = 1000 / noteDurations[thisNOTE];
    tone(TONE_PIN, melody[thisNOTE], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNOTEs = noteDuration * 1.30;
    delay(pauseBetweenNOTEs);
    // stop the tone playing:
    noTone(TONE_PIN);
  }

  Serial.println("Ready to calibrate");
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, true);
  delay(500);
  digitalWrite(LED_BUILTIN, false);

  int lightNum = 0;
  //while (digitalRead(RIGHT_BUMP_PIN) == HIGH) {} // Pause until the pin is grounded (our switch)
  //delay(100);
  while (digitalRead(RIGHT_BUMP_PIN) == LOW) { // Get high light values until the pin
    // is no longer grounded
    leftIR = analogRead(LEFT_IR_PIN);
    rightIR = analogRead(RIGHT_IR_PIN);
    Serial.print(leftIR);
    Serial.print("  = leftIR, Calibrate LIGHT & Dark rightIR = ");
    Serial.println(rightIR);
    if ( leftIR > maxLeftIR ) {
      maxLeftIR = leftIR;
    }
    if ( leftIR < minLeftIR ) {
      minLeftIR = leftIR;
    }
    if ( rightIR > maxRightIR ) {
      maxRightIR = rightIR;
    }
    if ( rightIR < minRightIR ) {
      minRightIR = rightIR;
    }
  }

  leftRange = maxLeftIR - minLeftIR;
  rightRange = maxRightIR - minRightIR;
  brightLeft = maxLeftIR - ((1.0 - HI_LIGHT) * leftRange);
  darkRight = minRightIR + (LO_LIGHT * rightRange);

  while ( digitalRead(LEFT_BUMP_PIN) == HIGH) {} // Pause until you trigger the left bump switch
  delay(1000);                      // Then wait 1 second and start line following.
}

void loop() {

  //  tone(6, melody, noteDuration);
  //  int pauseBetweenNOTEs = noteDuration * 1.30;
  //  delay(pauseBetweenNOTEs);
  //  // stop the tone playing:
  //  noTone(6);

  leftIR = analogRead(LEFT_IR_PIN);
  rightIR = analogRead(RIGHT_IR_PIN);
  Serial.print(leftIR);           // We can only write ONE thing
  Serial.print(" = left, right = "); // at a time, therefore it takes
  Serial.println(rightIR);        // three statemens to get our output.

  if (leftIR >= brightLeft && rightIR <= darkRight) {
    motorLeft->setSpeed(FORWARD_SPEED);
    motorRight->setSpeed(FORWARD_SPEED);
  }
  else if (leftIR < brightLeft ) {
    motorLeft->setSpeed(20);       // Too far left, stop LEFT motor
    motorRight->setSpeed(FORWARD_SPEED);
  }
  else if (rightIR > darkRight) {
    motorRight->setSpeed(20);
    motorLeft->setSpeed(FORWARD_SPEED);

  }
  motorLeft->run(FORWARD);
  motorRight->run(FORWARD);
  delay(20);
}




