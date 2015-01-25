/*
Estas funciones se utilizan para trabajar con las serLCD, creo que las he sacado del foro de Arduino
No hay que usar lcd.println porque surgen simbolos raros en pantalla
Me dice que en Arduino 1.0 no se puede hacer    lcd.print(0xFE, BYTE  );  se hace simplemente Serial.write(0xFE);
No se pueden escribir más de 16 caracteres por línea

Muchas veces al programar se queda la pantalla tonta y hay que conectar y desconectar Arduino
*/
 

//Esta funcion escribe dos lineas. Si no llegamos a los 16 caracteres y habia algo no sera borrado.
//Es más rápida que borrar la pantalla y luego escribir.
void escribirLCD (String linea1, String linea2) {
  lcd.selectLine(1);
  lcd.print(linea1);
  lcd.selectLine(2);
  lcd.print(linea2);
}

//Esta función primero borra la pantalla y luego escribe, es más lenta por eso deberá ser usada solo en el menú
//Nunca usarla en combate porque perderemos eficiencia
void borrarEscribirLCD (String linea1, String linea2) {
  lcd.clear();
  lcd.selectLine(1);
  lcd.print(linea1);
  lcd.selectLine(2);
  lcd.print(linea2);
}

void goTo(int posicion) {
  if (posicion<16) {
    lcd.setCursor(1,posicion+1);
  }
  else {
    lcd.setCursor(2,posicion-15);
  }
}

//
////Vamos a la linea 1
//void selectLineOne(){  //puts the cursor at line 0 char 0.
//   Serial.write(0xFE );   //command flag
//   Serial.write(128  );    //position
//   delay(10);
//}
//
////Vamos a la linea 2
//void selectLineTwo(){  //puts the cursor at line 0 char 0.
//   Serial.write(0xFE  );   //command flag
//   Serial.write(192  );    //position
//   delay(10);
//}
//
////Envia el cursor a cualquier posicion
//void goTo(int position) { //position = line 1: 0-15, line 2: 16-31, 31+ defaults back to 0
//if (position<16){ Serial.write(0xFE  );   //command flag
//              Serial.write((position+128)  );    //position
//}else if (position<32){Serial.write(0xFE  );   //command flag
//              Serial.write((position+48+128)  );    //position 
//} else { goTo(0); }
//   delay(10);
//}
//
////Borra la pantalla
//void lcd.clear(){
//   Serial.write(0xFE  );   //command flag
//   Serial.write(0x01  );   //clear command.
//   delay(10);
//}
//
////Enciende la luz de la pantalla
//void backlightOn(){  //turns on the backlight
//    Serial.write(0x7C  );   //command flag for backlight stuff
//    Serial.write(157  );    //light level.
//   delay(10);
//}
//
////Apaga la luz de la pantalla, Aún se puede leer aun con la luz apagada. Podemos usarlo para ahorrar batería
//void backlightOff(){  //turns off the backlight
//    Serial.write(0x7C  );   //command flag for backlight stuff
//    Serial.write(128  );     //light level for off.
//   delay(10);
//}
////a general function to call the command flag for issuing all other commands
//void serCommand(){      
//  Serial.write(0xFE  );
//}
//
//void turnLCDOn () {
//  Serial.write(0xFE);
//  Serial.write(0x0C);
//}
//
//void turnLCDOff () {
//  Serial.write(0xFE);
//  Serial.write(0x08);
//}

