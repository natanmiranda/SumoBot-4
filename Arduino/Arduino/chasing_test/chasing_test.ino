const int Motor1Pin1 = 3;
const int Motor1Pin2 = 5;
const int Motor2Pin1 = 6;
const int Motor2Pin2 = 11;
const int LineFrontLeft = 2;
const int LineFrontRight = 4;
const int LineBackLeft = 7;
const int LineBackRight = 8;
const int IRFrontLeft = 0;
const int IRFrontRight= 1;
const int IRBack = 2;
const int IRRight = 3;
const int IRLeft = 4;
int LRdiff= 0;

void setup() {                
  pinMode(Motor1Pin1, OUTPUT);  //set up for motor   
  pinMode(Motor1Pin2, OUTPUT);   
  pinMode(Motor2Pin1, OUTPUT);   
  pinMode(Motor2Pin2, OUTPUT);
  Serial.begin(9600);
}
void loop(){
  if (((Distance(IRFrontLeft) - Distance(IRFrontRight)) < 500) ||((Distance(IRFrontLeft) - Distance(IRFrontRight)) > -500)) {
    Chase();
  }else{
    Stop();
    delay(100);
  }
  Serial.println((Distance(IRFrontLeft) - Distance(IRFrontRight)));
  delay(100);
}

void Angle(int a){    // a is the amount of angle that you need the robot turn
 int t = 5*a;   // Important !!!  the equation need to be determined !!!
  delay(t);
}

void GoForward(){
  digitalWrite(Motor1Pin2, LOW);
  digitalWrite(Motor1Pin1, HIGH);
  digitalWrite(Motor2Pin2, LOW);
  digitalWrite(Motor2Pin1, HIGH);
}

void GoBackward(){
  digitalWrite(Motor1Pin1, LOW);
  digitalWrite(Motor1Pin2, HIGH);
  digitalWrite(Motor2Pin1, LOW);
  digitalWrite(Motor2Pin2, HIGH);
}

void GoLeft(){
  digitalWrite(Motor1Pin1, LOW);
  digitalWrite(Motor1Pin2, HIGH);
  digitalWrite(Motor2Pin2, LOW);
  digitalWrite(Motor2Pin1, HIGH);
}

void GoRight(){
  digitalWrite(Motor1Pin2, LOW);
  digitalWrite(Motor1Pin1, HIGH);
  digitalWrite(Motor2Pin1, LOW);
  digitalWrite(Motor2Pin2, HIGH);
}

void Stop(){
  digitalWrite(Motor1Pin2, LOW);
  digitalWrite(Motor1Pin1, LOW);
  digitalWrite(Motor2Pin1, LOW);
  digitalWrite(Motor2Pin2, LOW);
}

float Distance(int sensorPin){
  return (abs(2400/(analogRead(sensorPin) -20))); 
}
void Chase(){
  LRdiff = Distance(IRFrontLeft) - Distance(IRFrontRight);
  
  if ((LRdiff < 500) && (LRdiff > -500)){
  if ((LRdiff > -15) && (LRdiff < 15)){
    if (((Distance(IRFrontLeft)-Distance(IRFrontRight)) > -15) && ((Distance(IRFrontLeft)-Distance(IRFrontRight)) < 15)){
      GoForward();
      delay(100);
    }
  }else if ((LRdiff > -100) && (LRdiff < -15)){
    if (((Distance(IRFrontLeft)-Distance(IRFrontRight)) > -100) && ((Distance(IRFrontLeft)-Distance(IRFrontRight)) < -15)){
      GoRight();
      Angle(7);}
  }else if ((LRdiff < -100)&& (LRdiff > -500)) {
    if (((Distance(IRFrontLeft)-Distance(IRFrontRight)) < -100) && ((Distance(IRFrontLeft)-Distance(IRFrontRight)) < -500)){
    GoRight();
    Angle(9);}
  }
  else if ( (LRdiff < 100) && (LRdiff > 15)){
    if (((Distance(IRFrontLeft)-Distance(IRFrontRight)) < 100) && ((Distance(IRFrontLeft)-Distance(IRFrontRight)) > 15)){
    GoLeft();
    Angle(4);}
  }
  else if ((LRdiff > 100)&& (LRdiff < 500)){
    if (((Distance(IRFrontLeft)-Distance(IRFrontRight)) > 100) && ((Distance(IRFrontLeft)-Distance(IRFrontRight)) < 500)){
    GoLeft();
    Angle(6);}
  }
  delay(100);
  }
}

int readQD(int sensorP){
  pinMode(sensorP,OUTPUT);
  digitalWrite(sensorP,HIGH);
  delay(100);
  pinMode(sensorP,INPUT);
  
  long time = micros();

  //time how long the input is HIGH, but quit after 3ms as nothing happens after that
  while (digitalRead(sensorP) == HIGH && micros() - time < 3000); 
  int diff = micros() - time;

  return diff;
}
