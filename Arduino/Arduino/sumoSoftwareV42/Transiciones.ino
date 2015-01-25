/* 
En esta pestaña desarrollamos las transiciones del modo menu al combate y viceversa
Tambien los mensajes de inicio de programa
*/

//Transicion a modo combate. Esperamos los 5 segundos y luego colocamos el robot en posición horizontal
void transicionCombate () {
  secuenciaInicio2();
}

void secuenciaInicio2() {
//  unsigned long time=millis();
  tone(altavoz,1200,100);
  unsigned long pitido=millis();
  lcd.clear();
  for (int i=0;i<=15;i++) {
    for (int j=0;j<58;j++) {
      delay(5); 
      if ((millis()-pitido)>1000) {
        pitido=millis();
        tone(altavoz,1200,100);
      }
    }
    goTo(i); lcd.print(">");
    goTo(16+i); lcd.print(">");
    delay(4);
  }
  movimientoAnterior=ADELANTE;
  lcd.clear();
  tiempoLento=millis();
  delay(12);
  tone(altavoz,400,400);
  
//  time=millis()-time;
//  borrarEscribirLCD("TIEMPO INICIO",String(time));
//  delay(2000);
  
  //caidaForzada();
}

//Transicion a modo menu. Damos a las variables globales los valores adecuados
void transicionMenu () {
  moverFrenar();
  modo=MENU;
  menu=ESTRATEGIA;
  nivel=FUERA;
  lcd.clear();
  velocidadMaxima=velocidadAuxiliar;
  delay(500);  //Este dalay es para evitar que volvamos otra vez al modo combate por tener demasiado tiempo apretado el boton salir.
}

//void mensajeInicio () {
//  turnLCDOff();
//  delay(100);
//  turnLCDOn();
//  delay(500);
//  backlightOn();   //Esto es porque a veces media pantalla se apaga
//  lcd.clear();      //Limpiamos la pantalla
//  delay(250);
//  //Escribimos el texto de bienvenida
//  borrarEscribirLCD(" SUMO  SOFTWARE "," VERSION V07");   
//  delay(500);
//}
//
//void mensajeInicio2 () {
//  borrarEscribirLCD(" SUMO  SOFTWARE "," VERSION V07");
//  delay(1000);
//  lcd.clear();
//  delay(1000);
//  borrarEscribirLCD(" INICIANDO "," SISTEMA");
//  delay(1000);
//}
//
//void mensajeInicio3() {
//  for (byte i=0;i<255;i++) Serial.write(i);
//}

void mensajeInicio4() {
  lcd.clear();
  delay(500);
  borrarEscribirLCD(" SUMO  SOFTWARE "," VERSION V42");
  delay(500);
  lcd.clear();
}

void caidaForzada() {
   //Movemos hacia atras para hacer caer
  moverAdelantePWM(255); delay(5); //Creo que está linea hará el comportamiento más homogeneo. Así daremos el golpe que buscamos
  moverAtrasPWM(255);
  delay(143);  //Con 138 no hay golpe, pero parece que se puede conseguir mejor
  //140 sigue siendo parecido a 138
  //143 va rico rico
  //En el último segundo hacemos que se mueva hacia adelante frenando la caída. 
  moverAdelantePWM(255);
  delay(75);  //Con 50 es suficiente
}
//
//void caidaForzadaControlada() {
//   //Movemos hacia atras para hacer caer
//  moverAdelantePWM(255); delay(5); //Creo que está linea hará el comportamiento más homogeneo. Así daremos el golpe que buscamos
//  moverAtrasPWM(255);
//  while(analogRead(sharpT)>200) {
//    delay(1);
//  }
//  //En el último segundo hacemos que se mueva hacia adelante frenando la caída. 
//  moverAdelantePWM(255);
//  delay(75);  //Con 50 es suficiente
//}
