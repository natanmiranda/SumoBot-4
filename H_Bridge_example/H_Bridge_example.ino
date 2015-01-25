
const int Motor1Pin1 = 3;
const int Motor1Pin2 = 5;
const int Motor2Pin1 = 6;
const int Motor2Pin2 = 11;
const int LineSOut = 2;
const int LineSVin = 7;
const int LineSGnd = 4;
const int IRFrontLeft = 0;
const int IRFrontRight= 1;

void setup() {                
  pinMode(Motor1Pin1, OUTPUT);   
  pinMode(Motor1Pin2, OUTPUT);   
  pinMode(Motor2Pin1, OUTPUT);   
  pinMode(Motor2Pin2, OUTPUT);     
  pinMode(LineSVin, OUTPUT);
  pinMode(LineSGnd,OUTPUT);
  digitalWrite(LineSVin,HIGH);
}

void loop() {
  if ((readQD()) <2500){
    GoLeft();
    delay(1000);
  }else{
    if ((SharpSensor(IRFrontLeft)) < 40){
      GoForward();
    }else{
      Stop();
    }
  }.
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

int readQD(){
  pinMode(LineSOut,OUTPUT);
  digitalWrite(LineSOut,HIGH);
  delay(100);
  pinMode(LineSOut,INPUT);
  
  long time = micros();

  //time how long the input is HIGH, but quit after 3ms as nothing happens after that
  while (digitalRead(LineSOut) == HIGH && micros() - time < 3000); 
  int diff = micros() - time;

  return diff;
}

float SharpSensor(int sensorPin){
  return (65*pow((analogRead(sensorPin)*0.0048828125),-1.10)); 
}
//Oringinal Code for Sharp Sensor
//void loop(){
  //float volts= analogRead(IRpin)*0.0048828125;
  //float distance= 65*pow(volts,-1.10);
  //Serial.println(distance);
  //delay(100);
//}
  
