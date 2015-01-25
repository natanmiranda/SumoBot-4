/*
En esta pestaña voy a poner cosas extra como por ejemplo el efecto coche fantástico"
*/

//void cocheFantastico(int n) {
//  String dibujo="#";
//  for (int i=0;i<n;i++) {
//    dibujo=" "+dibujo;
//  }
//  for (int i=0;i<16-n-1;i++) {
//    dibujo=dibujo+" ";
//  }
//  escribirLCD(dibujo,dibujo);
//
//}

void cocheFantastico2 (int n) {
  switch (n) {
    case 0:
    goTo(0);
    lcd.print("# ");
    goTo(16);
    lcd.print("# ");
    break;
    case 15:
    goTo(14);
    lcd.print(" #");
    goTo(30);
    lcd.print(" #");
    break;
    default: 
    goTo(n-1);
    lcd.print(" # ");
    goTo(n+15);
    lcd.print(" # ");
  }
}

int divisionEntera(int dividendo, int divisor) {
  int resto=dividendo%divisor;
  return((dividendo-resto)/divisor);
}

void softwareReset() // Restarts program from beginning but does not reset the peripherals and registers
{
asm volatile ("  jmp 0");  
}  

//void marioBros() {
//  tone(altavoz,660,100);
//  delay(75);tone(altavoz,660,100);
//  delay(150);tone(altavoz,660,100);
//  delay(150);tone(altavoz,510,100);
//  delay(50);tone(altavoz,660,100);
//  delay(150);tone(altavoz,770,100);
//  delay(275);tone(altavoz,380,100);
//  delay(287);tone(altavoz,510,100);
//  delay(225);tone(altavoz,380,100);
//  delay(200);tone(altavoz,320,100);
//  delay(250);tone(altavoz,440,100);
//  delay(150);tone(altavoz,480,80);
//  delay(165);tone(altavoz,450,100);
//  delay(75);tone(altavoz,430,100);
//  delay(150);tone(altavoz,380,100);
//  delay(100);tone(altavoz,660,80);
//  delay(100);tone(altavoz,760,50);
//  delay(75);tone(altavoz,860,100);
//  delay(150);tone(altavoz,700,80);
//  delay(75);tone(altavoz,760,50);
//  delay(175);tone(altavoz,660,80);
//  delay(150);tone(altavoz,520,80);
//  delay(75);tone(altavoz,580,80);
//  delay(75);tone(altavoz,480,80);
//  delay(175);tone(altavoz,510,100);
//  delay(275);tone(altavoz,380,100);
//  delay(200);tone(altavoz,320,100);
//  delay(250);tone(altavoz,440,100);
//  delay(150);tone(altavoz,480,80);
//  delay(165);tone(altavoz,450,100);
//  delay(75);tone(altavoz,430,100);
//  delay(150);tone(altavoz,380,100);
//  delay(100);tone(altavoz,660,80);
//  delay(100);tone(altavoz,760,50);
//  delay(75);tone(altavoz,860,100);
//  delay(150);tone(altavoz,700,80);
//  delay(75);tone(altavoz,760,50);
//  delay(175);tone(altavoz,660,80);
//  delay(150);tone(altavoz,520,80);
//  delay(75);tone(altavoz,580,80);
//  delay(75);tone(altavoz,480,80);
//  delay(250);tone(altavoz,500,100);
//  delay(150);tone(altavoz,760,100);
//  delay(50);tone(altavoz,720,100);
//  delay(75);tone(altavoz,680,100);
//  delay(75);tone(altavoz,620,150);
//  delay(150);tone(altavoz,650,150);
//  delay(150);tone(altavoz,380,100);
//  delay(75);tone(altavoz,430,100);
//  delay(75);tone(altavoz,500,100);
//  delay(150);tone(altavoz,430,100);
//  delay(75);tone(altavoz,500,100);
//  delay(50);tone(altavoz,570,100);
//  delay(110);tone(altavoz,500,100);
//  delay(150);tone(altavoz,760,100);
//  delay(50);tone(altavoz,720,100);
//  delay(75);tone(altavoz,680,100);
//  delay(75);tone(altavoz,620,150);
//  delay(150);tone(altavoz,650,200);
//  delay(150);tone(altavoz,1020,80);
//  delay(150);tone(altavoz,1020,80);
//  delay(75);tone(altavoz,1020,80);
//  delay(150);tone(altavoz,380,100);
//  delay(150);tone(altavoz,500,100);
//  delay(150);tone(altavoz,760,100);
//  delay(50);tone(altavoz,720,100);
//  delay(75);tone(altavoz,680,100);
//  delay(75);tone(altavoz,620,150);
//  delay(150);tone(altavoz,650,150);
//  delay(150);tone(altavoz,380,100);
//  delay(75);tone(altavoz,430,100);
//  delay(75);tone(altavoz,500,100);
//  delay(150);tone(altavoz,430,100);
//  delay(75);tone(altavoz,500,100);
//  delay(50);tone(altavoz,570,100);
//  delay(110);tone(altavoz,500,100);
//  delay(150);tone(altavoz,760,100);
//  delay(50);tone(altavoz,720,100);
//  delay(75);tone(altavoz,680,100);
//  delay(75);tone(altavoz,620,150);
//  delay(150);tone(altavoz,650,200);
//  delay(150);tone(altavoz,1020,80);
//  delay(150);tone(altavoz,1020,80);
//  delay(75);tone(altavoz,1020,80);
//  delay(150);tone(altavoz,380,100);
//  delay(150);tone(altavoz,500,100);
//  delay(150);tone(altavoz,760,100);
//  delay(50);tone(altavoz,720,100);
//  delay(75);tone(altavoz,680,100);
//  delay(75);tone(altavoz,620,150);
//  delay(150);tone(altavoz,650,150);
//  delay(150);tone(altavoz,380,100);
//  delay(75);tone(altavoz,430,100);
//  delay(75);tone(altavoz,500,100);
//  delay(150);tone(altavoz,430,100);
//  delay(75);tone(altavoz,500,100);
//  delay(50);tone(altavoz,570,100);
//  delay(210);tone(altavoz,585,100);
//  delay(275);tone(altavoz,550,100);
//  delay(210);tone(altavoz,500,100);
//  delay(180);tone(altavoz,380,100);
//  delay(150);tone(altavoz,500,100);
//  delay(150);tone(altavoz,500,100);
//  delay(75);tone(altavoz,500,100);
//  delay(150);tone(altavoz,500,60);
//  delay(75);tone(altavoz,500,80);
//  delay(150);tone(altavoz,500,60);
//  delay(175);tone(altavoz,500,80);
//  delay(75);tone(altavoz,580,80);
//  delay(175);tone(altavoz,660,80);
//  delay(75);tone(altavoz,500,80);
//  delay(150);tone(altavoz,430,80);
//  delay(75);tone(altavoz,380,80);
//  delay(300);tone(altavoz,500,60);
//  delay(75);tone(altavoz,500,80);
//  delay(150);tone(altavoz,500,60);
//  delay(175);tone(altavoz,500,80);
//  delay(75);tone(altavoz,580,80);
//  delay(75);tone(altavoz,660,80);
//  delay(225);tone(altavoz,870,80);
//  delay(162);tone(altavoz,760,80);
//  delay(300);tone(altavoz,500,60);
//  delay(75);tone(altavoz,500,80);
//  delay(150);tone(altavoz,500,60);
//  delay(175);tone(altavoz,500,80);
//  delay(75);tone(altavoz,580,80);
//  delay(175);tone(altavoz,660,80);
//  delay(75);tone(altavoz,500,80);
//  delay(150);tone(altavoz,430,80);
//  delay(75);tone(altavoz,380,80);
//  delay(300);tone(altavoz,660,100);
//  delay(75);tone(altavoz,660,100);
//  delay(150);tone(altavoz,660,100);
//  delay(150);tone(altavoz,510,100);
//  delay(50);tone(altavoz,660,100);
//  delay(150);tone(altavoz,770,100);
//  delay(225);tone(altavoz,380,100);
//  //tells the user it is over and delays it a little before going to the top again
//  delay(1000);
//  tone(altavoz,440,200);
//  delay(200);
//  delay(200);
//  tone(altavoz,440,400);
//  delay(200);
//  delay(200);
//  delay(5000); 
//}
