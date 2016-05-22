#include <Wire.h>
#include <Adafruit_MotorShield.h> 
#include <math.h> 
#include <breadboardbot.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Define Constants

const byte LEFT_BUMP_PIN = 47;    // Define DIGITAL Pins for left
const byte RIGHT_BUMP_PIN = 46;   // and right bump sensors

const byte FORWARD_SPEED = 150;   // Define normal speeds
const byte BACKWARD_SPEED = 100;  // and backup/turn speed
const int  TURN_DURATION = 600;   // Turn length in milliseconds

// Define 'ports' for motors.
const byte LEFT_MOTOR_PORT = 3;
const byte RIGHT_MOTOR_PORT = 1;
// Create pointers to motor control objects
Adafruit_DCMotor *motorLeft = AFMS.getMotor(LEFT_MOTOR_PORT);
Adafruit_DCMotor *motorRight = AFMS.getMotor(RIGHT_MOTOR_PORT);


//The setup
void setup() {
  AFMS.begin(); // Start by stopping all motors
 
}

void loop() {
  // put your main code here, to run repeatedly:
    motorLeft->setSpeed(100);
    motorRight->setSpeed(100);
  //Set the speed for the robot
  //What direction to
    motorLeft->run(FORWARD);
    motorRight->run(FORWARD);
     




}
