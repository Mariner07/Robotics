// ---------------------------------------------------------------- //
// Arduino Ultrasoninc Sensor HC-SR04
// Re-writed by Arbi Abdul Jabbaar
// Using Arduino IDE 1.8.7
// Using HC-SR04 Module
// Tested on 17 September 2019
// ---------------------------------------------------------------- //
#include <Wire.h>
#include <ZumoShield.h>

#define LED 13

// this might need to be tuned for different lighting conditions, surfaces, etc.
#define QTR_THRESHOLD  1500 // microseconds

// these might need to be tuned for different motor types
#define REVERSE_SPEED     200 // 0 is stopped, 400 is full speed
#define TURN_SPEED        200
#define FORWARD_SPEED     100
#define REVERSE_DURATION  200 // ms
#define TURN_DURATION     100 // ms
#define MAX_SPEED     300 // ms

ZumoBuzzer buzzer;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON); // pushbutton on pin 12

#define NUM_SENSORS 6
unsigned int sensor_values[NUM_SENSORS];
bool made_delivery = false;

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
void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");

  pinMode(LED, HIGH);

  waitForButtonAndCountDown();
  Serial.begin(9600);
}
void loop() {

  if (button.isPressed())
  {
    // if button is pressed, stop and wait for another press to go again
    motors.setSpeeds(0, 0);
    button.waitForRelease();
    waitForButtonAndCountDown();
  }



  
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

  if(made_delivery==false ){
    if(distance>20){
      motors.setSpeeds(100, 100);
      
    }
    else{
      motors.setSpeeds(0,0);
      delay(1000);
      made_delivery=true;
      
    }
   
  }
  else if(onlyOnce==false){
    motors.setSpeeds(100,100);
    delay(2460);

    motors.setSpeeds(0,0);
    delay(100);

    motors.setSpeeds(200,-200);
    delay(300);

    motors.setSpeeds(100,100);
    delay(4100);

    motors.setSpeeds(0,0);
    delay(100);

    motors.setSpeeds(200,-200);
    delay(300);

    made_delivery=false;
    onlyOnce=true;
    
  }
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}
