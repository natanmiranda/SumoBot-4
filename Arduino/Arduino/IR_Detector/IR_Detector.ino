const int switchPin = 2;  
const int ledPin = 7;
const int irPin1 = A0;

void setup() {
  //initialize LED
  pinMode(ledPin, OUTPUT);
  //turn on LED
  digitalWrite(ledPin, HIGH);
  
  //initialize microswitch
  pinMode(switchPin, INPUT); 
  
  //don't start until switch pushed
  while(digitalRead(switchPin) == HIGH) {  }
  
  Serial.begin(9600);

  pinMode(irPin1, INPUT);
}

void loop(){
  Serial.println(analogRead(irPin1));
  delay(200);
}
