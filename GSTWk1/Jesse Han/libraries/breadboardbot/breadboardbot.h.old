/* Stuff for GoSciTech */

#include <Adafruit_MotorShield.h> 

#define TURNLEFT 0
#define TURNRIGHT 1
/*#define tireDiam 2.75;   // inches  N.B. The units used here determine
#define trackWidth  9.0; // inches       the units used everywhere for distance
*/
/*const byte TURNLEFT = 0;
const byte TURNRIGHT = 1;
*/
const float tireDiam = 2.75; // inches. 
const float trackWidth = 10.0; // inches

void allStop(int direction, Adafruit_DCMotor motorLeft, Adafruit_DCMotor motorRight) {
  motorLeft.setSpeed(100);  // Note that we reset the speeds here; therefore, 
  motorRight.setSpeed(100); // we need ot reset them in other routine.
  if (direction == FORWARD) {
    motorLeft.run(BACKWARD);
    motorRight.run(BACKWARD);
  }
  else {
    motorLeft.run(BACKWARD);
    motorRight.run(BACKWARD);
  }
  delay(50);
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
  return;
}

float duration_per_distance( float distance, byte speed) {
  /* Find drive time in milliseconds from relationship developed from
     observations of distance/time for a speed.  */
  float dist_per_sec = (0.117 * float(speed)) - 1.5;// in inches, from data
  float duration = abs(distance) / dist_per_sec;    // needed time in sec
  return duration * 1000.0 ;                        // Return in milliseconds
}


void drive(float distance, byte speed,
	   Adafruit_DCMotor mLeft, Adafruit_DCMotor mRight) {
  byte direction;
  mLeft.setSpeed(speed);  // Set both speeds
  mRight.setSpeed(speed);

  if (distance > 0) {   // Postive distance is forward
    direction = FORWARD;
  }
  else {
    direction = BACKWARD;
  }
  float duration = duration_per_distance(distance, speed);
  /* Now move in the desired directions for that duration */
  mLeft.run(direction);
  mRight.run(direction);
  delay(duration);
  allStop(direction, mLeft, mRight);
  return;
}

void spin(float degrees, byte speed,
	    Adafruit_DCMotor mLeft, Adafruit_DCMotor mRight) {
  /* A spin turns moves the wheels in opposite directions.  Each
     needs to go the same distance, which is determined by the
     degrees parameter, around a circle with a diameter of the
     robot track width.

    The actual distance will be the Circumference * the fraction of the
    circle needed, given by the ratio degrees/360. */
  // float distance = PI * trackWidth * degrees / 360.;
  float distance = PI * trackWidth * degrees / 360.;
  float duration = duration_per_distance(distance, speed);
  if (degrees > 0) {
    /* Positive angle is spin turn to the right; therefore right motor goes
       backwards and left side goes forward */
    mRight.run(BACKWARD);
    mLeft.run(FORWARD);
  }
  else { // Negative or 0 angle, turn to the left
    mRight.run(FORWARD);
    mLeft.run(BACKWARD);
  }
  delay(duration);
  return;
}

void pivot(float degrees, byte speed,
	   Adafruit_DCMotor mLeft, Adafruit_DCMotor mRight) {
  /* A pivot turns moves only one wheel, the one opposite the turn 
     directions.  The needed distance is determined by the
     degrees parameter, around a circle with a RADIUS of the
     robot track width.
     
     The actual distance will be the Circumference * the fraction of the
     circle needed, given by the ratio degrees/360. */
  float distance = PI * trackWidth * degrees / 360.;
  float duration = duration_per_distance(distance, speed);
  if (degrees > 0) {
    /* Positive angle is spin turn to the right; therefore right motor 
       does nothing and left side goes forward */
    mRight.run(RELEASE);
    mLeft.run(FORWARD);
  }
  else { // Negative or 0 angle, turn to the left
    mRight.run(FORWARD);
    mLeft.run(RELEASE);
  }
  delay(duration);
  return;
}

float Distance_inches(int ping) {
  float inches_per_sec = 13582.67;  // Equivilent to 345 m/s
  return ping * inches_per_sec * 1e-6 *0.5;
}

float Distance_cm(int ping) {
  float cm_per_sec = 34500.;        // Equivilent to 345 m/s
  return ping * cm_per_sec * 1e-6 *0.5;
}
