#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <math.h>
#include <BreadBoardBot.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Define Constants
const float cos30sin60 = sqrt(3.0) / 2.0; // cos(30 deg) = sin(60 deg), need for wheel
// vector calcs.

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

void setup() {
  // put your setup code here, to run once:
  AFMS.begin();  // create with the default frequency 1.6KHz
  // Turn off all motors
  motorLeft->run(RELEASE);
  motorBack->run(RELEASE);
  motorRight->run(RELEASE);
}

void loop() {
  // put your main code here, to run repeatedly:
  duration = 2;                          // Constants per leg: Two seconds/leg
  for ( byte leg = 1; leg < 36; leg++ ) {  // 5 times through loop for a square, why?

    magnitude = 100;                        //                    50% max power
    bool brake = false;                    //                    No braking
    switch (leg) {
      case 1:   // To the Right
        direction = -90.;
        duration = 1;
        break;
      case 2:
        duration = -.5;
        break;
      case 3:   // To the Right
        direction = -90;
        duration = 1;
        break;
      case 4:
        duration = -.5;
        break;
      case 5:   // To the Right
        direction = -90;
        duration = 1;
        break;
      case 6:
        duration = -.5;
        break;
      case 7:   // To the Right
        direction = -90;
        duration = 1;
        break;
      case 8:
        duration = -.5;
        break;
      case 9:   // To the Left
        direction = 90;
        duration = 1;
      case 10:
        duration = -.5;
        break;
      case 11:    // To the Left
        direction = 90;
        duration = 1;
        break;
      case 12:
        duration = -.5;
        break;
      case 13:    // To the Left
        direction = 90;
        duration = 1;
        break;
      case 14:
        duration = -.5;
        break;
      case 15:    // To the Left
        direction = 90;
        duration = 1;
        break;
      case 16:
        duration = -1;
        break;
      case 17:    // Now Kick
        direction = -20;
        duration = .2;
        break;
      case 18:
        direction = 160;
        duration = .2;
        break;
      case 19:
        duration = -1;
      //     delay(2000);
      case 20:    // Now Kick
        direction = 20;
        duration = .2;
        break;
      case 21:
        direction = -160;
        duration = .2;
        break;
      case 22:
        duration = -1;
        break;
      case 23:    // Now Kick
        direction = -20;
        duration = .2;
        break;
      case 24:
        direction = 160;
        duration = .2;
        break;
      case 25: //slight pause
        duration = -1;
        break;
      case 26:    // Now Kick
        direction = 20;
        duration = .2;
        break;
      case 31:
        direction = -160;
        duration = .2;
        break;
      case 32:
        duration = 0;
        motorBack-> setSpeed(255);
        motorLeft-> setSpeed(50);
        motorRight->setSpeed(50);
        //        motorLeft-> setSpeed(255);
        //        motorRight->setSpeed(255);
        motorBack-> run (FORWARD);
        motorLeft-> run (FORWARD);
        motorRight-> run (FORWARD);
        delay (2000);
        break;
      case 33:
        duration = -1;
        break;
      case 34:
        duration = 0;
        motorBack-> setSpeed(255);
        motorLeft-> setSpeed(50);
        motorRight->setSpeed(50);
        motorBack-> run (FORWARD);
        motorLeft-> run (FORWARD);
        motorRight-> run (FORWARD);
        delay (500);
        break;
      case 35:
        duration = -1;
        break;
      default:
        duration = 0;
    }

    if ( duration > 0 ) {
      Serial.print("direction = ");
      Serial.print(direction);
      Serial.print(", magnitude = ");
      Serial.print(magnitude);
      Serial.print(" and duration = ");
      Serial.println(duration);

      float xVector = magnitude * sin((M_PI * direction) / 180.);
      float yVector = magnitude * cos((M_PI * direction) / 180.);
      Serial.print("xVector, yVector = ");
      Serial.print(xVector);
      Serial.print(", ");
      Serial.println(yVector);

      // Find relative power needed for each wheel based on the target velocity vector
      float backPower = -xVector;  // Multiply by fudge factor to prevent rotation if needed
      float leftPower = 0.5 * xVector - cos30sin60 * yVector;
      float rightPower = 0.5 * xVector + cos30sin60 * yVector;

      // Find the actual motor speeds, 0-255, needed.  N.B. still need motor direction!
      byte backSpeed  = map(abs(backPower),  0, 100, 0, 255);
      byte leftSpeed  = map(abs(leftPower),  0, 100, 0, 255);
      byte rightSpeed = map(abs(rightPower), 0, 100, 0, 255);

      // Set the speeds
      motorBack-> setSpeed(backSpeed);
      motorLeft-> setSpeed(leftSpeed);
      motorRight->setSpeed(rightSpeed);

      /* Set Motor directions.  For Adafruit V2 Motorshield:
           1 is Clockwise (Positive motor direction, FORWARD)
           2 is Counterclockwise (Negative vector direction, BACKWARD)
           3 is Brake (Doesn't work at present)
           4 is Release = stop power, not driving, but not brake

         We can use a trinary operator to set direction within run call
      */
      motorBack-> run((backPower  > 0) ? FORWARD : BACKWARD );
      motorLeft-> run((leftPower  > 0) ? BACKWARD : FORWARD );
      motorRight->run((rightPower > 0) ? FORWARD : BACKWARD );

      //Print out motor control details
      Serial.print("Speeds Back,Left,Right = ");
      Serial.print(copysign(backPower, backSpeed));
      Serial.print(", ");
      Serial.print(copysign(leftPower, leftSpeed));
      Serial.print(", ");
      Serial.println(copysign(rightPower, rightSpeed));

      // Run motors for the duration needed, converting from seconds to milliseconds
      delay(1000 * duration);
      if (brake) {            // Not a real brake, but set power = 0, stop driving motors
        motorBack->setSpeed(0);
        motorLeft->setSpeed(0);
        motorRight->setSpeed(0);
        motorBack-> run(RELEASE);
        motorLeft-> run(RELEASE);
        motorRight->run(RELEASE);
      }
    }
    else {                    // no duration entered, so stop all motors
      motorBack->setSpeed(0);
      motorLeft->setSpeed(0);
      motorRight->setSpeed(0);
      motorBack-> run(RELEASE);
      motorLeft-> run(RELEASE);
      motorRight->run(RELEASE);
      delay(abs(1000 * duration));
    }
  }
}
