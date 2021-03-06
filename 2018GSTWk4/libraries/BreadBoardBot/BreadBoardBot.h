/* Common Functions for Bread Board Bot

   Arduino Robotics summer camp at GoSciTech 
   SC Governor's School of Science and Math, 2015 and beyond

   Arduino: Arduino Mega 256 v3 Clone
   Motor Shield: Clone of Adafruit Motor Shield for Arduino V2
   ---->  http://www.adafruit.com/products/1438

   Programmer & Instructor: Dave Eslinger; June 6, 2015
   Major revisions: 
         July 3, 2015 DLE (changed motorshield pointer passing) 
		 July 18, 2018 DLE (added constants for slope and intercept)
*/

#include <Adafruit_MotorShield.h> 

/* By using the SLOPE and INTERCEPT in the regression equations derived from
	DistanceTrials.xls, there is no need for the TIRE_DIAMETER variable.
	Start with the SLOPE and INTERCEPT found in the spreadsheet.  Tune, if needed,
	just to get straight-line distance correct.  Then tune TRACK_WIDTH to get turns
	accurate.  If not turning enough, INCREASE TRACK_WIDTH.
	*/
const float SLOPE = 0.1064;
const float INTERCEPT = - 1.457;
//const float TIRE_DIAMETER = 2.75; // inches.  N.B. The units here determine units
const float TRACK_WIDTH = 8.75; // inches      used everywhere for distance

void allStop(int oldDirection, 
	     Adafruit_DCMotor *mLeft, Adafruit_DCMotor *mRight) {
  mLeft->setSpeed(50);  // Note that we reset the speeds here; therefore, 
  mRight->setSpeed(50); // we need to reset them in other routine.
  if (oldDirection == FORWARD) {
    mLeft->run(BACKWARD);
    mRight->run(BACKWARD);
  }
  else {
    mLeft->run(FORWARD);
    mRight->run(FORWARD);
  }
  delay(50);
  mLeft->run(RELEASE);
  mRight->run(RELEASE);
  return;
}
void spinStop(int angle, 
	     Adafruit_DCMotor *mLeft, Adafruit_DCMotor *mRight) {
  mLeft->setSpeed(50);  // Note that we reset the speeds here; therefore, 
  mRight->setSpeed(50); // we need to reset them in other routine.
  if (angle > 0) {
    mLeft->run(BACKWARD);
    mRight->run(FORWARD);
  }
  else {
    mLeft->run(BACKWARD);
    mRight->run(FORWARD);
  }
  delay(50);
  mLeft->run(RELEASE);
  mRight->run(RELEASE);
  return;
}

float duration_per_distance( float distance, byte speed) {
  /* Find drive time in milliseconds from relationship developed from
     observations of distance/time for a speed.  */
  float dist_per_sec = (SLOPE * float(speed)) + INTERCEPT;// in inches, from data
//  float dist_per_sec = (0.1294 * float(speed)) - 1.457;// in inches, from data
  float duration = abs(distance) / dist_per_sec;    // needed time in sec
  return duration * 1000.0 ;                        // Return in milliseconds
}


void drive(float distance, byte speed,
	   Adafruit_DCMotor *mLeft, Adafruit_DCMotor *mRight) {
  byte direction;
  mLeft->setSpeed(speed);  // Set both speeds
  mRight->setSpeed(speed);

  if (distance > 0) {   // Postive distance is forward
    direction = FORWARD;
  }
  else {
    direction = BACKWARD;
  }
  float duration = duration_per_distance(distance, speed);
  /* Now move in the desired directions for that duration */
  mLeft->run(direction);
  mRight->run(direction);
  delay(duration);
  allStop(direction, mLeft, mRight);
  return;
}

void spin(float degrees, byte speed,
	    Adafruit_DCMotor *mLeft, Adafruit_DCMotor *mRight) {
  /* A spin turns moves the wheels in opposite directions.  Each
     needs to go the same distance, which is determined by the
     degrees parameter, around a circle with a diameter of the
     robot track width.

    The actual distance will be the Circumference * the fraction of the
    circle needed, given by the ratio degrees/360. */
  float distance = PI * TRACK_WIDTH * degrees / 360.;
  float duration = duration_per_distance(distance, speed);
  mLeft->setSpeed(speed);  // Set both speeds
  mRight->setSpeed(speed);
  if (degrees > 0) {
    /* Positive angle is spin turn to the right; therefore right motor goes
       backwards and left side goes forward */
    mRight->run(BACKWARD);
    mLeft->run(FORWARD);
  }
  else { // Negative or 0 angle, turn to the left
    mRight->run(FORWARD);
    mLeft->run(BACKWARD);
  }
  delay(duration);
  return;
}

void pivot(float degrees, byte speed,
	   Adafruit_DCMotor *mLeft, Adafruit_DCMotor *mRight) {
  /* A pivot turns moves only one wheel, the one opposite the turn
     directions.  The needed distance is determined by the
     degrees parameter, around a circle with a RADIUS of the
     robot track width.
     
     The actual distance will be the Circumference * the fraction of the
     circle needed, given by the ratio degrees/360. */
  float distance = 2.0 * PI * TRACK_WIDTH * degrees / 360.;
  float duration = duration_per_distance(distance, speed);
  mLeft->setSpeed(speed);  // Set both speeds
  mRight->setSpeed(speed);
  if (degrees > 0) {
    /* Positive angle is spin turn to the right; therefore right motor
       does nothing and left side goes forward */
    mRight->run(RELEASE);
    mLeft->run(FORWARD);
  }
  else { // Negative or 0 angle, turn to the left
    mRight->run(FORWARD);
    mLeft->run(RELEASE);
  }
  delay(duration);
  return;
}
