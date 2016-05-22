#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <math.h> 
#include <breadboardbot.h>
// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Define 'ports' for motors.
const byte LEFT_MOTOR_PORT = 3;
const byte RIGHT_MOTOR_PORT = 1;
// Create pointers to motor control objects
Adafruit_DCMotor *motorLeft = AFMS.getMotor(LEFT_MOTOR_PORT);
Adafruit_DCMotor *motorRight = AFMS.getMotor(RIGHT_MOTOR_PORT);
void setup() {
  AFMS.begin();  // create with the default frequency 1.6KHz
  // Turn off all motors to start, just a good habit
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
}

void loop() {
 delay(1000);
 drive(36., 100, *motorLeft, *motorRight);
 allStop(FORWARD, *motorLeft, *motorRight);
 spin(360., 50, *motorLeft, *motorRight);






 while(1){}



}
