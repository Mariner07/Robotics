#include <Wire.h>
#include <ZumoShield.h>

ZumoBuzzer buzzer;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON); // pushbutton on pin 12
void waitForButtonAndCountDown()
{
  button.waitForButton();
  delay(1000);

  // play audible countdown
 
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  waitForButtonAndCountDown(); 
}

void loop() {
  // put your main code here, to run repeatedly:
  if (button.isPressed())
  {
    // if button is pressed, stop and wait for another press to go again
    motors.setSpeeds(100, 100);
    button.waitForRelease();
    waitForButtonAndCountDown();
  }

  motors.setSpeeds(60, 60);
  delay(2000);
  motors.setSpeeds(0, 100);
  delay(500);
  motors.setSpeeds(60, 60);
  delay(2000);
  motors.setSpeeds(100, 0);
  delay(500);
  
}
