
const int Motor1Pin1 = 3;
const int Motor1Pin2 = 5;
const int Motor2Pin1 = 6;
const int Motor2Pin2 = 11;
const int IRpin1 = 0;
const int IRpin2 = 1;

float distance = 0.0;

void setup() {
  Serial.begin(9600);
  pinMode(Motor1Pin1, OUTPUT);  
  pinMode(Motor1Pin2, OUTPUT);   
  pinMode(Motor2Pin1, OUTPUT);   
  pinMode(Motor2Pin2, OUTPUT);   
  
}


void loop() {
  
  float volts1 = analogRead(IRpin1)*0.0048828125;
  float distance1 = 65*pow(volts1,-1.10);
  float volts2 = analogRead(IRpin2)*0.0048828125;
  float distance2 = 65*pow(volts2,-1.10);
  
  if (distance1 - distance2 > 5.0 ){
    GoRight();    
  }
  else if (distance1 - distance2 < -5.0 ){
    GoLeft();
  }
  else {
    GoForward();
    
  }
 
  
  
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

  

  
