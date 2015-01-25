
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
}

void loop() {                                // Line Sensor need to be used in priority 
  if ((readQD(LineFrontRight)) < 2500){     //Front Right Line Sensor reading
    GoLeft();
    Angle(45);               // The amount of angle need to be determined !!!!!!!!   please set up a function for it by your obsevation 
  }else if (readQD(LineFrontLeft) < 2500){     // The value of "2500" need to be determined !!!
    GoRight();                                // Front Left Line Sensor reading 
    Angle(45);
  }else if (readQD(LineBackLeft) < 2500){      // Back Left Line Sensor reading
    GoForward();
    delay(1000);
  }else if (readQD(LineBackRight) < 2500){      // Back Right Line Sensor reading
    GoForward();
    delay(1000);
  }else{                               // if all above condition fail, then start doing the IR sensor
    if (Distance(IRBack) < 121){                //Back IR sensor start detecting
      if (Distance(IRBack) < 121){
        GoLeft();
        Angle(180);
      }
    }else if (Distance(IRRight) < 121){
      if (Distance(IRRight) < 121){
        GoRight();
        Angle(90);}
    }else if (Distance(IRLeft) < 121){
      if (Distance(IRLeft) < 121){
        GoLeft();
        Angle(90);}
    }else if (Distance(IRFrontLeft) < 500 || Distance(IRFrontRight) < 500){        // Chasing Mode, Front IR sensor start detecting
      Chase();
    }else{
      GoRight();
      Angle(10);
    }
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

float Distance(int sensorPin){
  return (abs(2400/(analogRead(sensorPin) -20))); 
}
//Oringinal Code for Sharp Sensor
//void loop(){
  //float volts= analogRead(IRpin)*0.0048828125;
  //float distance= 65*pow(volts,-1.10);
  //Serial.println(distance);
  //delay(100);
//}

void Chase(){
  int distance1 = Distance(IRFrontLeft);
  int distance2 = Distance(IRFrontRight);
  LRdiff = distance1 - distance2;
  if ((LRdiff > -15) && (LRdiff < 15)){
    GoForward();
    delay(500);
  }else if ((LRdiff > -100) && (LRdiff < -15)){
    GoLeft();
    Angle(7);
  }else if (LRdiff < -100) {
    GoLeft();
    Angle(9);
  }
  else if ( (LRdiff < 100) && (LRdiff > 15)){
    GoRight();
    Angle(4);
  }
  else if ((LRdiff > 100)){
    GoRight();
    Angle(6);
  }
  
  
}

void Angle(int a){    // a is the amount of angle that you need the robot turn
 int t = a* 2.035481;   // Important !!!  the equation need to be determined !!!
  delay(t);
}
