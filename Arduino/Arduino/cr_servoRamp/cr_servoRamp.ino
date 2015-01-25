#include <Servo.h>
Servo myServo;        // Create Servo object to control the servo 

void setup() { 
  myServo.attach(9);  // Servo is connected to digital pin 9 
} 

void loop() { 
  myServo.writeMicroseconds(1300);
  delay(550);
  myServo.writeMicroseconds(1500);
  delay(2000);



}
