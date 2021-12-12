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

void setup()
{
  // uncomment if necessary to correct motor directions
  //motors.flipLeftMotor(true);
  //motors.flipRightMotor(true);

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
  
  int randomSpeed= random(250,400);
  
  if (button.isPressed())
  {
    // if button is pressed, stop and wait for another press to go again
    motors.setSpeeds(0, 0);
    button.waitForRelease();
    waitForButtonAndCountDown();
  }


  sensors.read(sensor_values);




unsigned long currentMillis= millis();

    if(sensor_values[0] < QTR_THRESHOLD)
    {

      motors.setSpeeds(-randomSpeed, -randomSpeed); //TURN: EACH MOVE IN DIFFERENT DIREC WITH 200 FOR 300 MS
      delay(100);
      motors.setSpeeds(randomSpeed, -randomSpeed); //TURN: EACH MOVE IN DIFFERENT DIREC WITH 200 FOR 300 MS
      delay(200);
      

      motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED); // go forward with 200 ms
      

      previousMillis=currentMillis;


    }

  
  else if (sensor_values[5] < QTR_THRESHOLD)
  {
    
    motors.setSpeeds(-randomSpeed, -randomSpeed); //TURN: EACH MOVE IN DIFFERENT DIREC WITH 200 FOR 300 MS
    delay(100);
    motors.setSpeeds(-randomSpeed, randomSpeed);
    delay(200);

    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED); // go forward with 200 ms

        previousMillis=currentMillis;
      }
    
//    Serial.println("Right most corner" );
//    Serial.println();
//    Serial.println(sensor_values[5]);
  
  else
  {
    // otherwise, go straight
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
//    delay(200);
//    Serial.println("Forward values" );
//    Serial.println();
//    Serial.println(sensor_values[1,2,3,4]);


    if(currentMillis - previousMillis >= 2600){
        previousMillis=currentMillis;

        Serial.println(";illis");
        Serial.println("currentMillies is "+currentMillis);
        Serial.println("previous is "+currentMillis);

        
        
        
        motors.setSpeeds(MAX_SPEED, MAX_SPEED);
        delay(400);
        motors.setSpeeds(-MAX_SPEED, -MAX_SPEED);
        delay(100);
        if(sensor_values[0] > QTR_THRESHOLD or sensor_values[5] > QTR_THRESHOLD){
          motors.setSpeeds(MAX_SPEED, MAX_SPEED);
          delay(400);
          }

        if(sensor_values[0] > QTR_THRESHOLD or sensor_values[5] > QTR_THRESHOLD){
            motors.setSpeeds(-MAX_SPEED, 0);
            delay(200);
            motors.setSpeeds(MAX_SPEED, MAX_SPEED);
            delay(500);
        }
      }
  }
    








 
}
