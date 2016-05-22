
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <math.h>
#include <breadboardbot.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Define 'ports' for motors.
const byte LEFT_MOTOR_PORT = 3;
const byte RIGHT_MOTOR_PORT = 1;
const byte BACK_MOTOR_PORT = 2;
// Create pointers to motor control objects
Adafruit_DCMotor *motorLeft = AFMS.getMotor(LEFT_MOTOR_PORT);
Adafruit_DCMotor *motorRight = AFMS.getMotor(RIGHT_MOTOR_PORT);
Adafruit_DCMotor *motorBack = AFMS.getMotor(BACK_MOTOR_PORT);

//Constants
const int MOVING_SPD = 75;
const int SPIN_SPD = 130;
float theta;
int direction;
float magnitude;
float duration;

byte motorLeftdir;
byte motorBackdir;
byte motorRightdir;

void setup(void) {
  AFMS.begin();  // create with the default frequency 1.6KHz
  // Turn off all motors to start, just a good habit
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
  motorBack->run(RELEASE);

  delay(1000);  // One second delay to get the robot ready
}


void loop() {


  toRightLeft();
  //delay(1000);
  //nowKick();
  //delay(1000);
  //walkItByYourself();

  while(1){}


}


void toRightLeft () {
  case 2: // Move right
      direction = 90.;
      break;
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
  motorBack->run(RELEASE)
  motorLeft->setSpeed(MOVING_SPD);
  motorRight->setSpeed(MOVING_SPD);
  motorBack->setSpeed(MOVING_SPD);
  case 1: // Move forward
      direction = 0.;
      break;
  delay(5000);
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
  motorBack->run(RELEASE);
  
  case 3: // Move backward
      direction = 180.;
      break;
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
  motorBack->run(RELEASE);
  motorLeft->setSpeed(MOVING_SPD);
  motorRight->setSpeed(MOVING_SPD);
  motorBack->setSpeed(MOVING_SPD);
  case 1: // Move forward
      direction = 0.;
      break;
  delay(5000);
  
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
  motorBack->run(RELEASE);
  case 2: // Move right
      direction = 90.;
      break;
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE); 
  motorBack->run(RELEASE);
}

void nowKick () {
 case 1: // Move forward
      direction = 0.;
      break;
  case 2: // Move right
      direction = 90.;
      break;

   
  case 1: // Move forward
      direction = 0.;
      break;
  
  motorLeft->setSpeed(MOVING_SPD);
  motorRight->setSpeed(MOVING_SPD);
  motorBack->setSpeed(MOVING_SPD);
  delay(1000);

  case 3: // Move backward
      direction = 180.;
      break;
  motorLeft->setSpeed(MOVING_SPD);
  motorRight->setSpeed(MOVING_SPD);
  motorBack->setSpeed(MOVING_SPD);
  delay(1000);
  
 case 1: // Move forward
      direction = 0.;
      break;
  case 4: // Move left
      direction = -90.;
      break;
  case 1: // Move forward
      direction = 0.;
      break;
  motorLeft->setSpeed(MOVING_SPD);
  motorRight->setSpeed(MOVING_SPD);
  motorBack->setSpeed(MOVING_SPD);
  delay(1000);
  case 3: // Move backward
      direction = 180.;
      break;


  
  motorLeft->setSpeed(MOVING_SPD);
  motorRight->setSpeed(MOVING_SPD);
  motorBack->setSpeed(MOVING_SPD);
  delay(1000);

case 1: // Move forward
      direction = 0.;
      break;
  case 2: // Move right
      direction = 90.;
      break;

  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
  motorBack->run(RELEASE);

}

void walkItByYourself() {
  case 1: // Move forward
      direction = 0.;
      break;
  motorLeft->setSpeed(150);
  motorRight->setSpeed(150);
  motorBack->setSpeed(150);
  delay(2000);
  
  case 3: // Move backward
      direction = 180.;
      break;
  motorLeft->setSpeed(150);
  motorRight->setSpeed(150);
  motorBack->setSpeed(150);
  delay(2000);
  
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
  motorBack->run(RELEASE);
  
  
}

