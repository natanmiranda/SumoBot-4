// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
 
Servo Servo1, Servo2;  // create servo object to control a servo 

                // a maximum of eight servo objects can be created 
 
int pos1 = 0;    // variable to store the servo position 
int pos2 = 180; 
 
void setup() 
{ 
  Servo1.attach(1);  // attaches the servo on pin 9 to the servo object 
  Servo2.attach(2);
} 
 
 
void loop() 
{ 
  for(pos1 = 0; pos1 < 180; pos1 += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    Servo1.write(pos);              // tell servo to go to position in variable 'pos' 
    for (pos2 = 180; pos2 >=1; pos2 -= 1 )
    {
      Servo2.write(pos);
      delay(15)
    }
    
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos1 = 180; pos1 >= 1; pos1 -= 1)     // goes from 180 degrees to 0 degrees 
  {                                
    Servo1.write(pos);              // tell servo to go to position in variable 'pos' 
    for(pos2 = 0; pos2 < 180; pos2 += 1 )
    {
      myservo2.write(pos);
      delay(15);
    }
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
} 
