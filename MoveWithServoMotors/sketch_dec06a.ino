#include <Servo.h>

Servo myservo1;  // create servo object to control a servo
Servo myservo2;
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int pin1 =  9;
int pin2 = 10;

void setup() {
  myservo1.attach(pin1);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(pin2);
}

void loop() {


  

  for (int i=0; i<4; i++){
    myservo2.write(180);
    myservo1.write(0);
    delay(4000);

    if(i==3){
      break;
    }
    myservo2.write(90);
    myservo1.write(0);
    delay(500);
  }

  myservo2.detach();
  myservo1.detach();
  
}
