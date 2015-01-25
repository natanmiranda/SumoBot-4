const int left = 9; //left motor
const int right = 11; //right motor
//be sure to connect these pins through transistors.

int val = 0; //store value from sensor

void setup() {
  pinMode(right, OUTPUT);
  pinMode(left, OUTPUT);
}
void loop() {
  val = analogRead(0);
 
  if(val < 100){
    digitalWrite(right, LOW);
    digitalWrite(left, HIGH); //if the surface is white turn the left motor
                              //on and the right off.
  } else{
    digitalWrite(left, LOW);
    digitalWrite(right, HIGH); // if the surface is black turn the right motor on
                               //and the left motor off.
  }
}
