void setup() {
  pinMode(13, OUTPUT); //intitial light output
}
void loop() 
{
  digitalWrite(13, HIGH); // 13 value with high voltage
  delay(1000); // wait for one second
  digitalWrite(13, LOW); // 13 value with low voltage
  delay(3000); // wait for three seconds
}
