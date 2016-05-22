/*
 Cool Blink
 Only for cool kids
 
 
 Made by: JAY
 
 
 */


// The setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output
  pinMode(13, OUTPUT);
}

// The loop function runs over and over again forever
void loop() {
   int a = 0;
//While loop keeps the "a" variable counter going five times
  while(a < 5){
  delay(200);
  digitalWrite(13, HIGH);
  delay(100);  
  digitalWrite(13, LOW); 
  a++;
  
}

//After the loop it turns off
digitalWrite(13, LOW);
while(1);
}
