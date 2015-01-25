const int vin = 1;
const int gnd = 0;
const int out = 3; 

void setup(){
  pinMode(vin, OUTPUT);
  pinMode(gnd,OUTPUT);
  digitalWrite(vin,HIGH);
  Serial.begin(9600);
}

void loop(){
  int value = analogRead(out);
  Serial.begin(value);
}

