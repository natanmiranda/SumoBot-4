/*  Initial BrutusBot Code
    Author:  Mark Martens  (BRuTuS) for Solarbotics Ltd.
    Date: July 9, 2012
    Binary sketch size: 5466 bytes (of a 32256 byte maximum) using ATMega328P with optiboot bootloader
 
    Chassis: BrutusBot
       http://www.solarbotics.com/products/60125/
    Motor Driver: CMDR Shield
       http://www.solarbotics.com/products/39290/
    Front Sensor: Sharp 10-80cm Infrared sensor 
       http://www.solarbotics.com/products/35238/
    
    Supplier:  Solarbotics
    
    General Overview:
    This is a simple roamer sketch for the brutusbot platform.  Customize to your needs.
    
    Motor control lines: D3, D5, D6, & D11
    Servo control line: D9
    Analog input line: A1
*/

#include <Servo.h>


/*#define bit9600Delay 84  
#define halfBit9600Delay 42
#define bit4800Delay 188 
#define halfBit4800Delay 94*/

#define threshold 200
#define delay_per_degree 4
#define reaction_delay 350
#define pan_offset -8
#define headlight1 19 //Headlight LEDs connected to Analog 5
#define headlight2 18 //Headlight LEDs connected to Analog 5
#define drivespeed 255
#define reversespeed 225
#define spinspeed 190

#define NODRIVE 0  //Set to 1 to disable drive

// Setup objects from Libraries
Servo servo_pan;

// Initialize Global Variables
int ledPin = 13;  // LED connected to digital pin 13
int lastlook=0;
int distance;
int watchdog=0;
unsigned long last_event = 0;
int left_motor=150;  //Set left motor speed
int right_motor=140;  // Set right motor speed
int spin_speed=140;  // Motor Speed during a speed.

// Function Declarations *****  (This helps read main code)
int look(int dir);
void drive(int command);
void roamer(void);


//Main Setup Function
void setup() 
{
  last_event=millis();
  //Randomize seed based on unconnected pin.
  randomSeed(analogRead(2));
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output
  pinMode(headlight1,OUTPUT);
  pinMode(headlight2,OUTPUT);
  digitalWrite(ledPin,HIGH);
  digitalWrite(headlight1,HIGH);
  digitalWrite(headlight2,HIGH);
  Serial.begin(57600); 
  servo_pan.attach(9);
  delay(250);  //Make sure servo is set and ready
  servo_pan.write(90 + pan_offset);
  delay(4000);
  digitalWrite(ledPin,LOW);
  digitalWrite(headlight1,LOW);
  digitalWrite(headlight2,LOW);
  
}



//  ********************  Main Loop
void loop()
{
  
   roamer(); 
  
}

// Functions


void drive(int command)
{
  /*
  0 = all stop
  1 = drive forward
  2 = drive reverse
  3 = spin left
  4 = spin right
  9 = disable chip  
  */
  
  //3&5 are Left Motor
  //6&11 are Right Motor
  int rightspeed;
  int leftspeed;
  
  rightspeed=drivespeed-20;
  leftspeed=drivespeed;
  
  if (NODRIVE == 1)
  {
    command=9;
  }
  
  switch (command)
  {
    case 0:
    // All Stop
    digitalWrite(headlight1,LOW);
    digitalWrite(headlight2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(11,LOW);
    break;
    
    case 1:
    // Forward
    digitalWrite(headlight1,HIGH);
    digitalWrite(headlight2,HIGH);
    analogWrite(3,leftspeed);
    digitalWrite(5,LOW);
    analogWrite(6,rightspeed);
    digitalWrite(11,LOW);
    break;
    
    case 2:
    // Reverse
    digitalWrite(headlight1,HIGH);
    digitalWrite(headlight2,HIGH);
    digitalWrite(3,LOW);
    analogWrite(5,reversespeed);
    digitalWrite(6,LOW);
    analogWrite(11,reversespeed);
    break;
    
    case 4:
    // Spin Left
    digitalWrite(headlight1,LOW);
    digitalWrite(headlight2,HIGH);
    digitalWrite(3,LOW);
    analogWrite(5,spinspeed);
    analogWrite(6,spinspeed);
    digitalWrite(11,LOW);
    break;

    case 3:
    // Spin Right
    digitalWrite(headlight1,HIGH);
    digitalWrite(headlight2,LOW);
    analogWrite(3,spinspeed);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    analogWrite(11,spinspeed);
    break;
    
    case 9:
    // Disable chip
    digitalWrite(headlight1,LOW);
    digitalWrite(headlight2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(11,LOW);
    break;
    
  }
  
  if (command != 0)
  {
    watchdog=0;
  }
  
}
  
int look(int dir)
{
  /*This routine sets robot to look in a certain direction, then 
  measure distance at that direction.
  90 degrees is straight ahead
  45 degrees is to the right
  135 degrees is to the left
  Function returns the distance.
  */
    
  int reading;
  int sample=0;
  int x=0;

  
  
  //digitalWrite(ultraviolet, HIGH); //Show reading begin
  
  servo_pan.write(dir + pan_offset); //Send Servo Where it is supposed to go.
  delay(abs(dir-lastlook)*delay_per_degree);  //Wait for the servo to get where its going

  
  delayMicroseconds(500);
  
  while ( x < 8)
  {
    sample=sample+analogRead(1);
    delayMicroseconds(200);   
    x++; 
  }
  
  
  reading=sample/8;
  //Serial.println(reading);
  
  if (dir == 90)  //If We're looking ahead
  {
    if (reading > threshold)
    {
      digitalWrite(ledPin, HIGH); //Head on object detected!
    }
    else
    {
      digitalWrite(ledPin, LOW);  //No objects to worry about
    }
  }
  
  if (dir == 135)  //If We're looking right
  {
    if (reading > (threshold*2))
    {
      digitalWrite(ledPin, HIGH); //Object detected!
    }
    else
    {
      digitalWrite(ledPin, LOW);  //No objects to worry about
    }
  }
  
  if (dir == 45)  //If We're looking left
  {
    if (reading > (threshold*2))
    {
      digitalWrite(ledPin, HIGH); //Head on object detected!
    }
    else
    {
      digitalWrite(ledPin, LOW);  //No objects to worry about
    }
  }

  
  lastlook=dir;
  return(reading); 
}


void roamer() 
{
  int left;
  int straight;
  int right;
  int boredomControl;
  int breakout=0;
  int dir;
  unsigned long last_looked_around;
  
  last_looked_around=millis()-5000;
  while (1)
  {
    straight=look(90);
    if (straight > threshold)
      {
        // Something Ahead!
        drive(0);
        right=look(135);
        left=look(45);
        straight=look(90);
        if (right > left)
        {
          //Turn left until clear
          dir=3;
        }
        else
        {
          //Turn Right until clear
          dir=4;
        }
        drive(dir);
        
        while (straight > threshold)
        {
          straight=look(90);
        }
        delay(reaction_delay);
        drive(0);
      }
    else
      {
        // Nothing Ahead!
        if ((millis() - last_looked_around) < 3000)
        {
          //Servo should be tilted down - check left and right all the time
          drive(1);
        }
        else
        {
          //Haven't looked up in a bit, lets check
          drive(0);
      
          right=look(135);
          left=look(45);
          straight=look(90);
    
          if ((right < (threshold*2)) && (left < (threshold*2)) && (straight < threshold))
          {
            //Nothing In front!  Free and Clear!
            last_looked_around=millis();
          }
          else
          {
            drive(0);
            if ((straight > threshold) || ((right > (threshold*2)) && (left > (threshold*2))))
              {
                //Interesting scenario - looked up and something is in our way!
                //Backup, and reasses?
                //Same if we are wedged left and right
                drive(2);
                while (straight > threshold)
                {
                  straight=look(90);
                }
                delay(reaction_delay);
                drive(0);
              }
              else
              {
                //Straight was fine, something is to left or right.
                if (right > (threshold*2))
                {
                  //Something off our Starboard Side Captain!
                  look(135);
                  drive(3);
                  while (right > (threshold*2))
                  {
                    right=look(135);
                  }
                  delay(reaction_delay);
                  drive(0);
                  look(90);
                }
                else
                {
                  //Something off our Port Side Captain!
                  look(45);
                  drive(4);
                  while (left > (threshold*2))
                  {
                    left=look(45);
                  }
                  delay(reaction_delay);
                  drive(0);
                  look(90);
                }
                
                
              }
                
        }//End Some Threshold Passed Else
         
     } //End Haven't Looked Up Else
    }//End Nothing Ahead Else
  }//End While Loop
 }//End of Roamer Function

