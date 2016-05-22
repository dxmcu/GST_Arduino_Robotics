/*
  Blink
  Turns on an LED and makes it gradually get brighter.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://arduino.cc
 
 created by Dylan Bruss
 
 uses code from 'Blink' by Scott Fitzgerald
 */


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
//  digitalWrite(13, HIGH); // turn the LED on (HIGH is the voltage level)
//  delay(100);             // wait for 100 ms
//  digitalWrite(13, LOW);  // turn the LED off by making the voltage LOW
//  delay(1000);            // wait for a second
//  digitalWrite(13, HIGH); //turn LED on
//  delay(100);             //wait for 100 ms
//  digitalWrite(13, LOW);  //turn LED off
//  delay(100);             //wait for 100 ms
//  digitalWrite(13, HIGH); //turn LED on
//  delay(100);             //wait for 100 ms
//  digitalWrite(13, LOW);  //turn LED off
//  delay(1000);            //wait one second before repeating
  for(int i = 0; i < 100; i += 0.2){
//    for(int o = 0; o<5; o++){
      digitalWrite(13, HIGH);
      delay((i/10));
      digitalWrite(13, LOW);
      delay(((100-i)/10));
//    }
  }
}
