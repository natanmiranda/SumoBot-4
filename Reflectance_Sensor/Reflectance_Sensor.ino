const int vin = 7;
const int gnd = 4;
const int out = 2;

void setup(){
  pinMode(vin,OUTPUT);
  pinMode(gnd,OUTPUT);
  digitalWrite(vin,HIGH);
  Serial.begin(9600);
}
void loop(){
  int value = readQD();
  Serial.println(value);
}

int readQD(){
  pinMode(out,OUTPUT);
  digitalWrite(out,HIGH);
  delay(100);
  pinMode(out,INPUT);
  
  long time = micros();

  //time how long the input is HIGH, but quit after 3ms as nothing happens after that
  while (digitalRead(out) == HIGH && micros() - time < 3000); 
  int diff = micros() - time;

  return diff;
}
