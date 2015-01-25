const int sensorP1 = 0;
const int sensorP2 = 1;
int val1 = 0;
int val2 = 0;
int distance = 0;
int distance1 = 0;
int distance2 = 0;

void setup(){
  Serial.begin(9600);
}

void loop(){
  val1 = analogRead(sensorP1);
  val2 = analogRead(sensorP2);
  distance1 = abs(2400/(val1 - 20));
  distance2 = abs(2400/(val2 - 20));
  distance = (distance1 - distance2);
  Serial.print("L ");
  Serial.print(distance1);
  Serial.print( "   R ");
  Serial.print(distance2);
  Serial.print("   Diff ");
  Serial.print(distance);
  Serial.println();
  
  delay(1000);
}

