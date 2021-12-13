#include <Wire.h>
#include <ZumoShield.h>

#define LED 13

// this might need to be tuned for different lighting conditions, surfaces, etc.
#define QTR_THRESHOLD  1500 // microseconds

// these might need to be tuned for different motor types
#define REVERSE_SPEED     200 // 0 is stopped, 400 is full speed
#define TURN_SPEED        200
#define FORWARD_SPEED     250
#define REVERSE_DURATION  200 // ms
#define TURN_DURATION     100 // ms
#define MAX_SPEED     300 // ms

ZumoBuzzer buzzer;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON); // pushbutton on pin 12

#define NUM_SENSORS 6
unsigned int sensor_values[NUM_SENSORS];

ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);

void waitForButtonAndCountDown()
{
  digitalWrite(LED, HIGH);
  button.waitForButton();
  digitalWrite(LED, LOW);
  delay(1000);

  // play audible countdown
 
}

#define echoPin 1 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 4 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
bool onlyOnce= false;
bool wait= false;
void setup()
{
  // uncomment if necessary to correct motor directions
  //motors.flipLeftMotor(true);
  //motors.flipRightMotor(true);
  
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
  pinMode(LED, HIGH);

  waitForButtonAndCountDown();
  Serial.begin(9600);
}

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 2500;

void loop()
{
  
  
  if (button.isPressed())
  {
    // if button is pressed, stop and wait for another press to go again
    motors.setSpeeds(0, 0);
    button.waitForRelease();
    waitForButtonAndCountDown();
  }
  // 1 meter is traveled in 8200 ms
   
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  
  
  if(wait==false){
    motors.setSpeeds(100, 100);
    delay(24600);
  
  }

  
  if (distance<20){
    
    delay(500);
    motors.setSpeeds(0, 0);
    
    delay(1000);
    
    motors.setSpeeds(200, -200);
    delay(300);
    
    motors.setSpeeds(0, 0);
    
    delay(300);
    
    motors.setSpeeds(100, 100);
    delay(4100);
    
    motors.setSpeeds(0, 0);
    
    delay(300);
    
    motors.setSpeeds(200, -200);
    delay(300);
    
    motors.setSpeeds(100, 100);
    
    delay(24600);
    exit(0);
  }
  
  else{
    wait=true;
    motors.setSpeeds(0,0);
//    delay(2000);
  
  }
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");



 
}
