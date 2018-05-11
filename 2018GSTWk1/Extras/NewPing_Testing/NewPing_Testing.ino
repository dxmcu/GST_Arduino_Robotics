/* NewPing_Testing.ino

    JUST FOR TESTING the different functions in NewPing Library and to see if the
    HC-SR04 can be made more reliable
    sonar.ping_median
    
    This program is based on Servo_Sonic.ino code; including keeping the DC motor and Servo motor
    functionality to see if they are introducing spurious noise.

    Arduino: Arduino Mega 256 v3 Clone
    Motor Shield: Generic clone of Adafruit Motor Shield for Arduino v2
    ---->  http://www.adafruit.com/products/1438

    Programmer: Dave Eslinger; 2018-04-04
*/
#include <Wire.h>
#include <Adafruit_MotorShield.h> 
#include <math.h> 
#include <BreadBoardBot.h>
#include <NewPing.h>
#include <Servo.h>

#if defined PING_MEDIAN_DELAY
    #undef PING_MEDIAN_DELAY
    #define PING_MEDIAN_DELAY 23000
#else
    #define PING_MEDIAN_DELAY 23000
#endif
    
#if defined NO_ECHO
    #undef NO_ECHO
    #define NO_ECHO 65535               // Value returned if there's no ping echo within the specified MAX_SENSOR_DISTANCE or max_cm_distance. Default=0
#else
    #define NO_ECHO 65535
#endif

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Define Servos 
Servo panServo;
Servo tiltServo;

/* Define Constants */

// IO Pins used
const byte LEFT_BUMP_PIN = 47;    // Define DIGITAL Pins for left
const byte RIGHT_BUMP_PIN = 46;   // and right bump sensors
const byte SONIC_TRIGGER_PIN = 51;
const byte SONIC_ECHO_PIN = 50;

// Parameters controlling program behavior
// Bump behavior
const byte FORWARD_SPEED = 100;   // Define normal speeds
const byte BACKWARD_SPEED = 100;  // and backup/turn speed
const int  TURN_DURATION = 600;   // Turn length in milliseconds

// Sonic sensor
const float TARGET_DISTANCE_INCHES = 15; 
const int MAX_SONIC_DISTANCE = 500;      // cm, optional, 500 cm is default

// Define 'ports' for motors.
const byte LEFT_MOTOR_PORT = 3;
const byte RIGHT_MOTOR_PORT = 1;
// Create pointers to motor control objects
Adafruit_DCMotor *motorLeft = AFMS.getMotor(LEFT_MOTOR_PORT);
Adafruit_DCMotor *motorRight = AFMS.getMotor(RIGHT_MOTOR_PORT);

/* Define new ultrasonic sensor with trigger & echo pins and 
   the maximum distance to be sensed. */
NewPing sonic(SONIC_TRIGGER_PIN, SONIC_ECHO_PIN, MAX_SONIC_DISTANCE); 

/* Define servo pins */
const byte PANSERVOPIN = 10; // Servo 1 on AdaFruit Motor Shield
const byte TILTSERVOPIN = 9; // Servo 2

float pingDist; // define variable to use for distance measurements
String msg="";
unsigned long thisMean;
unsigned int pingTime;

/* This code is based on the NewPing::ping_median function found in the 
    NewPing library.
    
    Changed from a median calculation to the mean over it non-NO_ECHO returns.
    Note that NO_ECHO is defined in NewPing.h
    */
unsigned long ping_mean(uint8_t it=5, unsigned int max_cm_distance=500) {
    unsigned int last;
    uint8_t  i = 0;
    unsigned long sum_pings, t;

    while (i < it) {
        t = micros();                  // Start ping timestamp.
        last = sonic.ping(max_cm_distance);  // Send ping.

        if (last != NO_ECHO && last > 0) {         // Ping in range, include as part of sum.
            if (i > 0) {               // Don't start sort till second ping.
                sum_pings = sum_pings + last;     // Add latest ping to sum
            } else sum_pings = last;   // Initialize sum_pings with first ping.
            i++;                       // Move to next ping.
        }
        // else it--;                 // Ping out of range, skip and don't include as part of sum.
        // Serial.println(String("i, ping, sum_pings = " + String(i) + ", " + String(last) + ", " + String(sum_pings)));

        if (i < it && micros() - t < PING_MEDIAN_DELAY) {
            // Serial.println("Delay in ping_mean");
            delay((PING_MEDIAN_DELAY + t - micros()) / 1000); // Millisecond delay between pings.
        }
    }
    return (sum_pings/it); // Return the ping distance mean.
}

  
void setup(void){
  AFMS.begin();  // create with the default frequency 1.6KHz
  // Turn off all motors to start, just a good habit
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);

  panServo.attach(PANSERVOPIN);
  tiltServo.attach(TILTSERVOPIN);
  panServo.write(90);
  tiltServo.write(90);
  
  Serial.begin(9600);  //Begin serial communcation
  
  /*Set up Bump Pins with Arduino internal pullup resistors
    This will make them always high unless a bump switch is hit, 
    which will make a connection to ground and they will read low. */
  pinMode(LEFT_BUMP_PIN,INPUT_PULLUP);
  pinMode(RIGHT_BUMP_PIN,INPUT_PULLUP);

  pinMode(SONIC_TRIGGER_PIN,OUTPUT);
  pinMode(SONIC_ECHO_PIN,INPUT);
  // delay(2000);  // Two second delay to get the robot placed
}

void loop(){

  // Test some of the sonic library functions:  
/*    Serial.print(sonic.ping_in());
      Serial.print(" inches, cm = ");
      Serial.print(sonic.ping_cm());
      Serial.print(", ping time (ms) = ");
      // int ping_milli = sonic.ping();
      int ping_milli = sonic.ping_median();
      Serial.print(ping_milli);
      Serial.print(", real inches = ");
      Serial.print(Distance_inches(ping_milli));
      Serial.print(", real cm = ");
      Serial.print(Distance_cm(ping_milli));
      Serial.print(", med ping = ");
      Serial.println(sonic.ping_median(7,500));
 */   // delay(100); // Just to slow things down
 
 
    msg = "\r\n10 lines with sonic.ping()\r\n";
    for (int i=1; i<=10; i++) {
        for (int j=1; j<10; j++) {
            pingTime = sonic.ping(200);  // Send ping.
            if (pingTime != NO_ECHO && pingTime > 0) {         // Ping in range, include as part of sum.
                msg += String(String(pingTime) + "\t");
			}
			else {
				j--;
			}
            delay(PING_MEDIAN_DELAY/1000);
        }
        Serial.println(String(msg + String(sonic.ping())));
        msg = "";
    }

    msg = "\r\n10 lines with sonic.ping_median()\r\n";
    for (int i=1; i<=10; i++) {
        for (int j=1; j<10; j++) {
            msg += String(String(sonic.ping_median(5,200)) + "\t");
        }
        Serial.println(String(msg + String(sonic.ping_median(5,200))));
        msg = "";
    }

    msg = "\r\n10 lines with ping_mean()\r\n";
    for (int i=1; i<=10; i++) {
        for (int j=1; j<10; j++) {
            msg += String(String(ping_mean(5,200)) + "\t");
        }
        Serial.println(String(msg + String(ping_mean(5,200))));
        msg = "";
    }

    // for (int i = 1; i <=5; i++) {
        // thisMean = ping_mean(3,500);
        // Serial.println(String("Ping Mean is " + String(thisMean) + ", Dist is " + String(thisMean/ US_ROUNDTRIP_IN)));
    // }
    while(digitalRead(RIGHT_BUMP_PIN)) {}  //Stop after going through the loop once and wait for right bump switch  
}
