//CONSTANTS
//Ports
const byte SWITCHPIN            = 2;
const byte LEFTDRIVEFORWARD     = 3;
const byte LEFTDRIVEBACKWARD    = 4;
const byte RIGHTDRIVEFORWARD    = 5;
const byte RIGHTDRIVEBACKWARD   = 6;
const byte TRIGGER              = 9;
const byte ECHO                 = 10;
const byte ENABLEPIN            = 13;


//Other Constants
const byte FORWARD    = 1;
const byte BACKWARD   = -1;
const byte STOP       = 0;

//FUNCTIONS
void rampDown (void);
boolean proximity (void);
int lineSensors (void);
void pulseDrive (byte, byte, int);  //direction of left, direction of right, percentage (0-100)

//GLOBAL VARIABLES

////////////////////////////////////////////////////////////////////////////////////////////////////

void setup(){
  //INPUTS
  pinMode(SWITCHPIN, INPUT);
  pinMode(ECHO, INPUT);
  
  //OUTPUTS
  pinMode(LEFTDRIVEFORWARD, OUTPUT);
  pinMode(RIGHTDRIVEFORWARD, OUTPUT);
  pinMode(LEFTDRIVEBACKWARD, OUTPUT);
  pinMode(RIGHTDRIVEBACKWARD, OUTPUT);
  pinMode(ENABLEPIN, OUTPUT);
  pinMode(TRIGGER, OUTPUT);
  
  //START UP
  digitalWrite(ENABLEPIN, HIGH);
  digitalWrite(LEFTDRIVEFORWARD, LOW);
  digitalWrite(RIGHTDRIVEFORWARD, LOW);
  
  rampDown(); //Brings the ramp down at beginning of match
}

void loop(void){
  if(proximity()){
    pulseDrive(FORWARD, FORWARD, 100);
  }
  else if(lineSensor == 1){
    pulseDrive(BACKWARD, BACKWARD, 100);
    delay(500)
    pulseDrive(BACKWARD, STOP, 100);
  }
  else if(lineSensor == 2){
    pulseDrive(FORWARD, FORWARD, 100);
    delay(500)
    pulseDrive(FORWARD, STOP, 100);
  }
  else{
    pulseDrive(FORWARD, BACKWARD, 50);
  }
  
}

void rampDown(void){
  pulseDrive(BACKWARD, BACKWARD, 100);
  delay(500); //in Ms
  pulseDrive(STOP, STOP, 100);
}

boolean proximity (void){
  int duration;
  long distance;
  
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(5);
  digitalWrite(TRIGGER, LOW);
  
  duration = pulseIn(ECHO, HIGH);
  distance = duration/29/2;  //Time to distance in cm
  
  if(distance <= 30)
    return true;
  else
    return false;
  //return tripped sensor true - tripped, false - not tripped
}

int lineSensors(void){
  //Check for white lines
  //return tripped sensor 0-none, 1-front, 2-back
}

void pulseDrive (byte leftDriveDir, byte rightDriveDir, int percentage){
  if(leftDriveDir == 1){
    digitalWrite(LEFTDRIVEFORWARD, HIGH);
    digitalWrite(LEFTDRIVEBACKWARD, LOW);
  }
  
  else if(leftDriveDir == -1){
    digitalWrite(LEFTDRIVEFORWARD, LOW);
    digitalWrite(LEFTDRIVEBACKWARD, HIGH);
  }
  else{
      digitalWrite(LEFTDRIVEFORWARD, LOW);
      digitalWrite(LEFTDRIVEBACKWARD, LOW);
  }
  
  if(rightDriveDir == 1){
    digitalWrite(RIGHTDRIVEFORWARD, HIGH);
    digitalWrite(RIGHTDRIVEBACKWARD, LOW);
  }
  else if(rightDriveDir == -1){
    digitalWrite(RIGHTDRIVEFORWARD, LOW);
    digitalWrite(RIGHTDRIVEBACKWARD, HIGH);
  }
  else
      digitalWrite(RIGHTDRIVEFORWARD, LOW);
      digitalWrite(RIGHTDRIVEBACKWARD, LOW);
}

  
