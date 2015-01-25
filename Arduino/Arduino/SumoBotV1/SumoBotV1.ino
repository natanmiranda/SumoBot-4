
#include <Servo.h>
Servo servo;                                
const int LeftForward = 3;
const int LeftBackward = 5;
const int RightForward = 6;
const int RightBackward = 11;
const int LineFrontLeft = 2;
const int LineFrontRight = 4;
const int LineBackLeft = 7;
const int LineBackRight = 8;
const int IRFrontLeft = 0;
const int IRFrontRight= 1;
const int IRBack = 2;
const int IRRight = 3;
const int IRLeft = 4;


void setup() {
  servo.attach(2);  
  servo.write(10);
  pinMode(LeftForward, OUTPUT);   
  pinMode(LeftBackward, OUTPUT);   
  pinMode(RightForward, OUTPUT);   
  pinMode(RightBackward, OUTPUT);
  Serial.begin(9600);

  
}

void loop(){
  if ((readQD(LineFrontRight)) <2500){     //Front Right Line Sensor reading
    GoLeft();
    Angle(45);
  }else{
    Stop();
    delay(500);
  }
}


int readQD(){
  pinMode(out,OUTPUT);
  digitalWrite(out,HIGH);
  delay(100);
  pinMode(out,INPUT);
  
  long time = micros();

  while (digitalRead(out) == HIGH && micros() - time < 3000); 
  int diff = micros() - time;

  return diff;
}


void GoForward(){
  digitalWrite(LeftForward, LOW);
  digitalWrite(LeftBackward, HIGH);
  digitalWrite(RightForward, LOW);
  digitalWrite(RightBackward, HIGH);
}

void GoBackward(){
  digitalWrite(LeftForward, LOW);
  digitalWrite(LeftBackward, HIGH);
  digitalWrite(RightForward, LOW);
  digitalWrite(RightBackward, HIGH);
}

void GoLeft(){
  digitalWrite(LeftForward, LOW);
  digitalWrite(LeftBackward, HIGH);
  digitalWrite(RightForward, LOW);
  digitalWrite(RightBackward, HIGH);
}

void GoRight(){
  digitalWrite(LeftForward, LOW);
  digitalWrite(LeftBackward, HIGH);
  digitalWrite(RightForward, LOW);
  digitalWrite(RightBackward, HIGH);
}

void Stop(){
  digitalWrite(LeftForward, LOW);
  digitalWrite(LeftBackward, LOW);
  digitalWrite(RightForward, LOW);
  digitalWrite(RightBackward, LOW);
} 



  



