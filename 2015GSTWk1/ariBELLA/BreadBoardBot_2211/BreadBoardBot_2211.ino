// This is an include file for the breadboard bot.
// Stops all motors.

void allStop(int direction) {
  motorLeft->setSpeed(100);  // Note that we reset the speeds here; therefore, 
  motorRight->setSpeed(100); // we need ot reset them in other routine.
  if (direction == FORWARD) {
    motorLeft->run(BACKWARD);
    motorRight->run(BACKWARD);
  }
  else {
    motorLeft->run(BACKWARD);
    motorRight->run(BACKWARD);
  }
  delay(50);
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
  return;
}
