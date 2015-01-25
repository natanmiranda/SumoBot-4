#include<Servo.h>
Servo servo;
int pos;
void setup (){
  servo.attach(1);
}

void loop(){
  for (pos = 70; pos < 180; pos += 1){
    servo.write(pos);
    delay(15);
  }
  for (pos = 180; pos > 70; pos -= 1){
    servo.write(pos);
    delay(15);
  }
}
