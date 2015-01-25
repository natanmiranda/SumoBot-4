int IRpin1=0;  // analog pin for sensor
void setup(){
  Serial.begin(9600);
}

void loop(){
  float volts1= analogRead(IRpin1)*0.0048828125;
  float distance1= 65*pow(volts1,-1.10);
  Serial.println(distance1);
  delay(100);
}
