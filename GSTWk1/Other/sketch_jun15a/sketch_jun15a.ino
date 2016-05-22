void setup() {
  pinMode(15, OUTPUT);
}

void loop() {
  digitalWrite(15, HIGH);
  delay(1000);
  digitalWrite(15, LOW);
  delay(1000);
}
  int delayVal()
{
  int v;
  v = analogRead(15);
  v /= 4;
  return v;
}
