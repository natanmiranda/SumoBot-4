#include <AFMotor.h>
AF_DCMotor motor2(2, MOTOR12_64KHZ);
AF_DCMotor motor1(1, MOTOR12_64KHZ);
void setup(){
  Serial.begin(9600);
  motor1.setSpeed(250);
  motor2.setSpeed(250);

}

void loop(){
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  delay(1000);
}
