// BOE shield - Hooking to HobbyKing RC unit
// Arcade Drive style
//#use Serial
#include <Servo.h>
Servo servoLeft;
Servo servoRight;


// declare R/C pins and variables
int ch1; // Right Joysteck, Left - Right reading
int ch2; // Right Joysteck, Front - Back reading
//int ch3; // Left Joysteck, Front - Back reading
//int ch4; // Left Joystick, Left - Right reading
//int ch5; // VR(A)
//int ch6; // VR(B)

int pinch1 = 10;
int pinch2 = 9;
//int pinch3 = 8;
//int pinch4 = 7;
//int pinch5 = 6;
//int pinch6 = 5;
int leftMotor, rightMotor;
int turn;
int throttle;
int t2sign;
int inside;

void setup() {
  servoLeft.attach(12);
  servoRight.attach(11);
  tone(2, 2400, 250);                       // Play tone for 1 second
  delay(250);                               // Delay to finish tone

  pinMode(pinch1, INPUT); // Set our input pins as such
  pinMode(pinch2, INPUT);
  //  pinMode(pinch3, INPUT);
  //  pinMode(pinch4, INPUT); 
  //  pinMode(pinch5, INPUT);
  //  pinMode(pinch6, INPUT);

  Serial.begin(57600); 
}

void loop() {
 
  ch1 = pulseIn(pinch1, HIGH, 25000); // Read the pulse width of 
  ch2 = pulseIn(pinch2, HIGH, 25000); // each channel
  //  ch3 = pulseIn(pinch3, HIGH, 25000);
  //  ch4 = pulseIn(pinch4, HIGH, 25000);
  //  ch5 = pulseIn(pinch5, HIGH, 25000);
  //  ch6 = pulseIn(pinch6, HIGH, 25000);

  throttle = map(ch2,1150,1800,-200,200);
  throttle = constrain(throttle, -200,200);
  turn = map(ch1,1150,1800,-200,200); 
  turn = constrain(turn, -200, 200);
  t2sign = abs(float(turn) * float(throttle))/(float(turn) *float(throttle)); // Use to find the sign of the product
  inside = throttle - (t2sign * turn); 
  // If throttle sign and turn are opposite, add them; if they are the same, subtract them.
  // Use this as the speed for the inside wheel of the turn.

  if (turn >= 0) { // Right Turn, so left motor at full Throttle setting, right motor reduced by turn
    rightMotor = 1500 + inside;
    leftMotor = 1500 + throttle;
  }
  else { // Left Turn, so right motor at full Throttle setting, left motor reduced by turn
    rightMotor = 1500 + throttle; 
    leftMotor = 1500 + inside ;
  }
  // Right Motor is one backwards so remap from 1300 - 1700 to 1700 to 1300
  rightMotor = map(rightMotor, 1300, 1700, 1700, 1300);

  Serial.print("Ch 1: ");
  Serial.print(ch1);        // each channel
  Serial.print(", Throttle = ");
  Serial.print(throttle);        // each channel

  Serial.print(",  Ch 2: ");
  Serial.print(ch2);        // each channel
  Serial.print(", Turn = ");
  Serial.print(turn);        // each channel
  Serial.print(", Inside = ");
  Serial.print(inside);        // each channel
  Serial.print(", t2sign = ");
  Serial.print(t2sign);        // each channel
  Serial.print(", t2 = ");
  Serial.print(turn*throttle);        // each channel

  //  Serial.print("    Channel 3:");
  //  Serial.print(ch3);
  
  servoLeft.writeMicroseconds(leftMotor);
  servoRight.writeMicroseconds(rightMotor);
  Serial.print(",  sLeft = ");
  Serial.print(leftMotor);
  Serial.print(",  sRight = ");
  Serial.println(rightMotor);

  delay(200); // delay for ease in reading
}
