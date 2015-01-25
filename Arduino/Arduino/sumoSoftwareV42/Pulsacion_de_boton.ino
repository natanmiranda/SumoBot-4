/*
Esta función va a cambiar el valor de las variables globales de flujo en función de los botones pulsados y del contexto
*/
void pulsacionBoton (){
    
  //Boton siguiente
  if (digitalRead(btnSiguiente)==LOW) {
    switch (modo) {
      case COMBATE:
      //Para no salir del modo combate accidentalmente comprobamos que de verdad se ha pulsado el boton
      delay(delayCombate);
      if (digitalRead(btnSiguiente)==LOW) transicionMenu();
      break;
      
      case MENU:
      //El boton siguiente solo actua si no estamos dentro de una aplicacion
      if (nivel==FUERA) {
        //enum eMenu {ESTRATEGIA, SHARP, CNY70, BATERIA};
        switch (menu) {
          case ESTRATEGIA: menu=VELOCIDAD; break;
          case VELOCIDAD: menu=PRUEBAESTRATEGIA; break;
          case PRUEBAESTRATEGIA: menu=SENSORTRASERO; break;
          case SENSORTRASERO: menu=SHARP; break;
          case SHARP: menu=SHARP2; break;
          case SHARP2: menu=RADAR; break;
          case RADAR: menu=CNY70; break;
          case CNY70: menu=BATERIA; break;
          case BATERIA: menu=PRUEBAMOTOR; break;
          case PRUEBAMOTOR: menu=PRUEBAHUIR; break;
          case PRUEBAHUIR: menu=VERTICAL; break;
          case VERTICAL: menu=HORIZONTAL2; break;
          case HORIZONTAL2: menu=BANCOPRUEBAS; break;
          case BANCOPRUEBAS: menu=LUZ; break;
          case LUZ: menu=FANTASTICO; break;
          case FANTASTICO: menu=SONIDO; break;
          case SONIDO: menu=RESET; break;
          case RESET: menu=ESTRATEGIA; break;
        }
        delay(delayBoton);
      }
      break;
    }
  }
  //Boton Intro
  if (digitalRead(btnIntro)==LOW) {
    switch (modo) {
      case COMBATE:
      //Para no salir del modo combate accidentalmente comprobamos que de verdad se ha pulsado el boton
      delay(delayCombate);
      if (digitalRead(btnIntro)==LOW) transicionMenu();
      break;
      
      case MENU:
      //El boton Intro solo actua si no estamos dentro de una aplicacion
      if (nivel==FUERA) {
        nivel=DENTRO;
        lcd.clear();
        delay(delayBoton);
      }
      break;
    }
  }
  //Boton Atras
  if (digitalRead(btnAtras)==LOW) {
    switch (modo) {
      case COMBATE:
      //Para no salir del modo combate accidentalmente comprobamos que de verdad se ha pulsado el boton
      delay(delayCombate);
      if (digitalRead(btnAtras)==LOW) transicionMenu();
      break;
      
      case MENU:
      switch (nivel) {
        case DENTRO: 
        nivel=FUERA;
        lcd.clear();
        delay(delayBoton);
        break;
        
        case FUERA:
        modo=COMBATE;
        transicionCombate();
        break;
        
      }
      break;
    }
  }
  
}

