/* 
En esta pestaña voy a definir las distintas funciones que vamos a utilizar en el menu
La nomenclatura sera menuNombreFuncion, p.e. menuEstrategia 
Tambien voy a meter aqui las funciones que muestran el escritorio o ejecutan la aplicacion*/

//Esta funcioin ejecuta la aplicacion del menu que este seleccionada en ese momento.
void ejecutarAplicacion() {
  switch (menu) {
     case ESTRATEGIA:      elegirEstrategia(); break;
     case SHARP:           menuSharp(); break;
     case SHARP2:          menuSharp2(); break;
     case CNY70:           menuCNY70(); break;
     case BATERIA:         menuBateria(); break;
     case LUZ:             menuLuz(); break;
     case FANTASTICO:      menuFantastico(); break;
     case RESET:           softwareReset(); break;
     case RADAR:           menuRadar(); break;
     case PRUEBAMOTOR:     menuPruebaMotor(); break;
     case PRUEBAHUIR:      menuPruebaHuir(); break;
     case PRUEBAESTRATEGIA: menuPruebaEstrategia(); break;
     case VERTICAL:        menuVertical(); break;
     case HORIZONTAL2:     menuHorizontal2(); break;
     case VELOCIDAD:       menuVelocidad(); break;
     case BANCOPRUEBAS:    menuBancoPruebas(); break;
     case SONIDO:          menuSonido(); break;
     case SENSORTRASERO:   menuSensorTrasero(); break;
     default:              borrarEscribirLCD(" FALLO EN "," MENU");
  }
}

//Esta funcion muestra la posicion del menu en la que nos encontramos
void mostrarMenu() {
  goTo(6);
  lcd.print("MENU");
  switch (menu) {
        case ESTRATEGIA:    goTo(16);lcd.print("^  ESTRATEGIA  >"); break;      
        case SHARP:         goTo(16);lcd.print("^  LEER SHARP  >"); break;   
        case SHARP2:        goTo(16);lcd.print("^  LEER SHARP2 >"); break;     
        case CNY70:         goTo(16);lcd.print("^  LEER CNY70  >"); break;        
        case BATERIA:       goTo(16);lcd.print("^   BATERIA    >"); break;        
        case LUZ:           goTo(16);lcd.print("^     LUZ      >"); break;        
        case FANTASTICO:    goTo(16);lcd.print("^ C.FANTASTICO >"); break;        
        case RESET:         goTo(16);lcd.print("^    RESET     >"); break;        
        case RADAR:         goTo(16);lcd.print("^    RADAR     >"); break;
        case VERTICAL:      goTo(16);lcd.print("^  VERTICAL    >"); break;
        case HORIZONTAL2:   goTo(16);lcd.print("^CAIDA FORZADA >"); break;
        case VELOCIDAD:     goTo(16);lcd.print("^  VELOCIDAD   >"); break;
        case BANCOPRUEBAS:  goTo(16);lcd.print("^BANCO PRUEBAS >"); break;
        case SONIDO:        goTo(16);lcd.print("^    SONIDO    >"); break;
        case SENSORTRASERO: goTo(16);lcd.print("^SENSOR TRASERO>"); break;
        case PRUEBAMOTOR:             goTo(16);lcd.print("^ PRUEBA MOTOR >"); break;
        case PRUEBAHUIR:              goTo(16);lcd.print("^ PRUEBA HUIR  >"); break;
        case PRUEBAESTRATEGIA:        goTo(16);lcd.print("^ PRUEBA ESTRA >"); break;   
        default:            borrarEscribirLCD(" FALLO EN "," MENU");
      }
}

//Esta función permite seleccionar entre las estrategias disponibles
void elegirEstrategia (){
  goTo(3);lcd.print("ESTRATEGIA");
  switch (menuEstrategia) {     
        //case AGRESIVA:      goTo(16);lcd.print("^   AGRESIVA   >"); break;
        case VUELTAS:       goTo(16);lcd.print("^    VUELTAS   >"); break;    
        case FLUIDO:        goTo(16);lcd.print("^    FLUIDO    >"); break;
        case SUICIDA:       goTo(16);lcd.print("^   SUICIDA    >"); break;  
        case WALLRACE:      goTo(16);lcd.print("^  WALL RACE   >"); break;
        case COBARDE:       goTo(16);lcd.print("^  COBARDERR   >"); break;
        default:            borrarEscribirLCD(" FALLO EN ","MENU ESTRATEGIA");
  }
  if (digitalRead(btnSiguiente)==LOW) {
    switch (menuEstrategia) {                                          
        //case AGRESIVA:      menuEstrategia=VUELTAS; break; 
        case VUELTAS:       menuEstrategia=FLUIDO; break;
        case FLUIDO:        menuEstrategia=SUICIDA; break; 
        case SUICIDA:       menuEstrategia=WALLRACE; break;
        case WALLRACE:      menuEstrategia=COBARDE; break;
        case COBARDE:       menuEstrategia=VUELTAS; break;
        default:            borrarEscribirLCD(" FALLO EN ","MENU ESTRATEGIA");
    }
    delay(delayBoton);
  }
  if (digitalRead(btnIntro)==LOW) {
    switch (menuEstrategia) {                                          
        //case AGRESIVA:      estrategia=AGRESIVA; lcd.clear();        delay(500); borrarEscribirLCD("ELEGIDA ESTRTGIA",">>> AGRESIVA <<<"); delay(1000);break;
        case VUELTAS:       estrategia=VUELTAS; lcd.clear();         delay(500); borrarEscribirLCD("ELEGIDA ESTRTGIA",">>>  VUELTAS <<<"); delay(1000);break;
        case FLUIDO:        estrategia=FLUIDO; lcd.clear();          delay(500); borrarEscribirLCD("ELEGIDA ESTRTGIA",">>>  FLUIDO  <<<"); delay(1000);break;
        case SUICIDA:       estrategia=SUICIDA; lcd.clear();         delay(500); borrarEscribirLCD("ELEGIDA ESTRTGIA",">>> SUICIDA  <<<"); delay(1000);break;   
        case WALLRACE:      estrategia=WALLRACE; lcd.clear();        delay(500); borrarEscribirLCD("ELEGIDA ESTRTGIA",">>>WALL RACE <<<"); delay(1000);break;  
        case COBARDE:       estrategia=COBARDE; lcd.clear();        delay(500); borrarEscribirLCD("ELEGIDA ESTRTGIA",">>> COBARDERR <<<"); delay(1000);break; 
        default:            borrarEscribirLCD(" FALLO EN ","MENU ESTRATEGIA");
    }
    delay(delayBoton);
    lcd.clear();
  }

    
}
      
  


// Esta función lee el valor de los sensores Sharp y lo muestra por pantalla. Esta optimizada para que los valores salgan siempre 
// En la misma posición
void menuSharp () {
  lcd.clear();
  int lecturaDI=analogRead(sharpDI);
  goTo(25);
  if (lecturaDI>99) lcd.print("DI"+String(lecturaDI));
  else 
    if (lecturaDI>9) lcd.print("DI "+String(lecturaDI));
    else lcd.print("DI  "+String(lecturaDI));
  
  int lecturaDD=analogRead(sharpDD);
  goTo(18);
  if (lecturaDD>99) lcd.print("DD"+String(lecturaDD));
  else 
    if (lecturaDD>9) lcd.print("DD "+String(lecturaDD));
    else lcd.print("DD  "+String(lecturaDD));
  
  int lecturaI=analogRead(sharpI);
  goTo(11);
  if (lecturaI>99) lcd.print("I"+String(lecturaI));
  else 
    if (lecturaI>9) lcd.print("I "+String(lecturaI));
    else lcd.print("I  "+String(lecturaI));
  
  int lecturaT=analogRead(sharpT);
  goTo(6);
  if (lecturaT>99) lcd.print("T"+String(lecturaT));
  else 
    if (lecturaT>9) lcd.print("T "+String(lecturaT));
    else lcd.print("T  "+String(lecturaT));
  
  int lecturaD=analogRead(sharpD);
  goTo(1);
  if (lecturaD>99) lcd.print("D"+String(lecturaD));
  else 
    if (lecturaD>9) lcd.print("D "+String(lecturaD));
    else lcd.print("D  "+String(lecturaD));
  delay(100);
}

void menuSharp2 () {
  int lecturaDI=analogRead(sharpDI);
  goTo(26);
  if (lecturaDI>200) lcd.print("XXX"); else lcd.print("   "); 
  int lecturaDD=analogRead(sharpDD);
  goTo(18);
  if (lecturaDD>200) lcd.print("XXX"); else lcd.print("   "); 
  int lecturaI=analogRead(sharpI);
  goTo(12);
  if (lecturaI>200) lcd.print("XXX"); else lcd.print("   "); 
  int lecturaT=analogRead(sharpT);
  goTo(6);
  if (lecturaT>200) lcd.print("XXX"); else lcd.print("   ");
  int lecturaD=analogRead(sharpD);
  goTo(1);
  if (lecturaD>200) lcd.print("XXX"); else lcd.print("   ");
  //delay(25);
}

//La funcion lee el valor de los sensores CNY70 y lo muestra por pantalla.
void menuCNY70 () {
  lcd.clear();
  byte lecturaDI=digitalRead(CNY70DI);
  goTo(25);
  lcd.print("DI="+String(lecturaDI));
  byte lecturaDD=digitalRead(CNY70DD);
  goTo(18);
  lcd.print("DD="+String(lecturaDD));
  byte lecturaTI=digitalRead(CNY70TI);
  goTo(9);
  lcd.print("TI="+String(lecturaTI));
  byte lecturaTD=digitalRead(CNY70TD);
  goTo(2);
  lcd.print("TD="+String(lecturaTD));
  delay(50);
}

//Esta funcion lee el voltaje de la batería y lo muestra por pantalla.
//Si puedo hay que actualizarla a 1023=11*31*3
void menuBateria () {
  int lectura = analogRead(bateria);
  //float voltaje = lectura*5/1023*2*1000;  //En milivoltios
  //Estoy teniendo algún problema de desbordamiento. Voy a usar un truco matematico. En vez de utilizar 1023 voy a usar 1024
  //10000/1024=10^4/2^10=5^4/2^6=625/64
  //La precision va a ser de 10mV aproximadamente
  int voltaje=lectura*25/32*25/2; //Aqui estoy perdiendo precision porque multiplico por 25 y divido entre 32. Hay que evitar las contracciones. 0.781*12.5
  //Pero utilizando 1023 la perdida de precisión sería aun mayor porque lo mejor que puedo hacer es 20/31=0.645
  //El orden de la operación es importante para que no se desborde o se pierda precisión.
  //Hay que cuidar que no tengamos algo mayor de 32000 y dividir al final para no perder precisión. Métodos numéricos
  // voltaje=lectura/64*625 <> voltaje=lectura*25/64*25 <> voltaje=lectura*25/32*25/2
  int voltios = divisionEntera(voltaje,1000);
  int milivoltios = voltaje - 1000*voltios;
  if (voltaje>7200) {
    if (milivoltios>99) borrarEscribirLCD("BATERIA: "+String(voltios)+"."+String(milivoltios)+"V","VOLTAJE OK");
    else {
      if (milivoltios>9) borrarEscribirLCD("BATERIA: "+String(voltios)+".0"+String(milivoltios)+"V","VOLTAJE OK");
      else borrarEscribirLCD("BATERIA: "+String(voltios)+".00"+String(milivoltios)+"V","VOLTAJE OK");
    }
  }
    else {
      if (milivoltios>99) borrarEscribirLCD("BATERIA: "+String(voltios)+"."+String(milivoltios)+"V","RECARGAME YA");
      else {
        if (milivoltios>9) borrarEscribirLCD("BATERIA: "+String(voltios)+".0"+String(milivoltios)+"V","RECARGAME YA");
        else borrarEscribirLCD("BATERIA: "+String(voltios)+".00"+String(milivoltios)+"V","RECARGAME YA");
    }
    }
  //delay(1000);
  /*delay(500);
  borrarEscribirLCD(String(voltaje),String(milivoltios));
  delay(500);
  */
  delay(50);
}

void comprobarBateria () {
  int lectura = analogRead(bateria);
  //float voltaje = lectura*5/1023*2*1000;  //En milivoltios
  //Estoy teniendo algún problema de desbordamiento. Voy a usar un truco matematico. En vez de utilizar 1023 voy a usar 1024
  //10000/1024=10^4/2^10=5^4/2^6=625/64
  //La precision va a ser de 10mV aproximadamente
  int voltaje=lectura*25/32*25/2; //Aqui estoy perdiendo precision porque multiplico por 25 y divido entre 32. Hay que evitar las contracciones. 0.781*12.5
  //Pero utilizando 1023 la perdida de precisión sería aun mayor porque lo mejor que puedo hacer es 20/31=0.645
  //El orden de la operación es importante para que no se desborde o se pierda precisión.
  //Hay que cuidar que no tengamos algo mayor de 32000 y dividir al final para no perder precisión. Métodos numéricos
  // voltaje=lectura/64*625 <> voltaje=lectura*25/64*25 <> voltaje=lectura*25/32*25/2
  int voltios = divisionEntera(voltaje,1000);
  int milivoltios = voltaje - 1000*voltios;
  if (voltaje<7250) {
    goTo(0);
    lcd.print("!B!");
    goTo(13);
    lcd.print("!B!");
    delay(1);
    }
  //delay(1000);
  /*delay(500);
  borrarEscribirLCD(String(voltaje),String(milivoltios));
  delay(500);
  */

}



//Enciende o apaga la luz de la pantalla LCD
void menuLuz() {
  if (luz==ENCENDIDA) { 
    lcd.setBrightness(1);
   luz=APAGADA;
  } 
  else {
  lcd.setBrightness(30);
  luz=ENCENDIDA;
  }
  nivel=FUERA;
}

//Muestra por pantalla el efecto clasico de coche fantastico
void menuFantastico() {
//  for (int i=0;i<16;i++) cocheFantastico2(i);
//  for (int i=15;i>=0;i--) cocheFantastico2(i);
  cocheFantastico2(contadorFantastico);
  delay(4);
  if (contadorFantastico==0) direccionFantastico=1;
  if (contadorFantastico==15) direccionFantastico=0;
  if (direccionFantastico) contadorFantastico++;
  else contadorFantastico--;
}

//Muestra por pantalla la posicion de lo que haya delante dle robot. Se podria llamar Tracking
void menuRadar(){
  lcd.clear();
  int lecturaDI=analogRead(sharpDI);
  int lecturaDD=analogRead(sharpDD);
  //Escribimos los valores por pantalla
  if (lecturaDD>99) {
    goTo(1);
    lcd.print("DD:"+String(lecturaDD));
  }
  else {
    if (lecturaDD>9) {
      goTo(1);
      lcd.print("DD: "+String(lecturaDD));
    }
    else {
      goTo(1);
      lcd.print("DD:  "+String(lecturaDD));
    }
  }
  
  if (lecturaDI>99) {
    goTo(9);
    lcd.print("DI:"+String(lecturaDI));
  }
  else {
    if (lecturaDD>9) {
      goTo(9);
      lcd.print("DI: "+String(lecturaDI));
    }
    else {
      goTo(9);
      lcd.print("DI:  "+String(lecturaDI));
    }
  }
  
  //Ahora tenemos que determinar la posicion
  //Con el siguiente algoritmo podemos detectar si estamos a la derecha, delante o izquierda, muy izquierda y supermuyizquierda
  //Como no podemos distinguir entre izquierda y delante tendremos que poner que gire ligeramente a la derecha en esas situaciones
  //Primero pongo un umbral de sensibilidad, si no lo cumple me salgo
  if ((lecturaDI<200)&&(lecturaDD<200)) {
    goTo(21);
    lcd.print("??");
    delay(50);
    return;
  }
  int posicion; //posicion tiene que estar al final entre 0 y 15.
  //Ahora tengo que distinguir los casos de izquierda o derecha
  if (lecturaDD>lecturaDI) {
    //Tenemos tres franjas, una en la que lecturaDI es muy pequeña, otra en la que va creciendo y una última en la que son muy parecidos.
    //Esta podría ser la condición de muy derecha
    if (lecturaDI<10) {  //En la derecha los valoresDI bajan muy rápido, no es necesario un umbral
      posicion=0;
    }
    else {
      posicion=7-7*(lecturaDD-lecturaDI)/(lecturaDD+lecturaDI);
    }
  }
  else {
    if (lecturaDD<60) {  //Cuando tenemos algo muy a la izquierda del sensor oscila mucho, por eso el umbral lo ponemos mucho más alto aquí
      posicion=14;
    }
    else {
      posicion=7+7*(lecturaDI-lecturaDD)/(lecturaDD+lecturaDI);
    }
  }
  
  goTo(posicion+16);
  lcd.print("##");
  delay(50);
}

//Esto es para comprobar que los motores están bien conectados y funcionan correctamente
void menuPruebaMotor() {
  delay(2000);  //Esperamos un poco antes de empezar la prueba
//Ahora hacemos una prueba de los dos motores conjuntamente
  goTo(0);
  lcd.print("IZQ ATRAS");
  motorIAtrasPWM(80);
  delay(200);
  moverFrenar();
  delay(1000);
  goTo(0);
  lcd.print("DER ATRAS");
  motorDAtrasPWM(80);
  delay(200);
  moverFrenar();
  delay(1000);
  goTo(0);
  lcd.print("IZQ ADEL");
  motorIAdelantePWM(80);
  delay(200);
  moverFrenar();
  delay(1000);
  goTo(0);
  lcd.print("DER ADEL");
  motorDAdelantePWM(80);
  delay(200);
  moverFrenar();
  delay(1000);

  nivel=FUERA;
  lcd.clear();
}

void menuPruebaHuir() {  
  //Primero activo motores y eso y muestro los valores de los sensores
  moverFrenar();

  menuCNY70();
  delay(2000);
  //Ahora activo el mecanismo de huida
  eCNY70 estado=sensoresSuelo();
  switch (estado) {
    case Z:  break;
    default: maniobraEvasivaFluido(estado);
  }
  //Lo repito por si estaba todo un lado en lo blanco
  estado=sensoresSuelo();
  switch (estado) {
    case Z:  break;
    default: maniobraEvasivaFluido(estado);
  }
  moverFrenar();
  nivel=FUERA;
  lcd.clear();
}

void menuPruebaEstrategia() {
  menuSharp();
  delay(2000);
  int herzios=0;
  movimientoAnterior=QUIETO;
  contadorDD=0;
  contadorDI=0;
  contadorD=0;
  contadorI=0;
  contadorT=0;
  tiempoLento=millis();
  unsigned long tiempoEstrategia= millis();
  while (millis()-tiempoEstrategia<2000) { 
    switch (estrategia) {
      //case AGRESIVA:     estrategiaAgresiva() ; break;
      case VUELTAS:      estrategiaVueltas(); break; 
      case FLUIDO:       estrategiaFluido(); break; 
      case SUICIDA:      estrategiaSuicida(); break;
      case WALLRACE:     estrategiaWallRace(); break;
      case COBARDE:      estrategiaCobarde(); break;
      default: borrarEscribirLCD(" FALLO EN "," ESTRATEGIA"); delay(500); lcd.clear(); break;
    }
    herzios++;
  }
  nivel=FUERA;
  menu=ESTRATEGIA;
  moverFrenar();
  delay(1000);
  borrarEscribirLCD(" HERZIOS: "," "+String(herzios/2));
  delay(2000);
  lcd.clear();
}



//Modo para poner el robot vertical.
void menuVertical() {
  borrarEscribirLCD("CAMBIO A MODO","  VERTICAL");
  delay(2000);
  moverFrenar();

  moverAtrasPWM(255);
  delay(75);
  moverAdelantePWM(255);
  delay(500);  
  //Ahora está levantado y lo que hay que hacer es frenarlo sin que se caiga. Primero frenamos el motor izquierdo
for (byte i=0;i<128;i++) {
    motorIAdelantePWM(255-2*i); 
    delay(1);
  }
  
  for (byte i=0;i<128;i++) {
    motorIAtrasPWM(2*i); 
    delay(1);
  }
  
  for (byte i=255;i>30;i--) {
    girarIzquierdaPWM(i,0);
    delay(25);
  }
  
  
//Lo que hacemos es ir girando cada vez más lentamente para que vaya perdiendo la inercia que ha adquirido al ponerse de pie
//De esta manera cuando frena del todo no tiene inercia y no se cae.
//  for (byte i=0;i<255;i++) {
//    girarIzquierdaPWM(255-i,10); 
//    borrarEscribirLCD(String(255-i),"");
//    delay(50);
//  }

//Esta es otra forma de frenar que ha funcionado cuando la otra ha fallado, pero unas veces va y otras no. Es como si hubiese una caída de tensión
//  motorIAdelantePWM(0);
//  motorIDisable();
  //Ahora frenamos el motor derecho.
  //delay(200); //Esto lo hago para que se estabilice girando
//  for (byte i=0;i<235;i++) {
//    motorDAdelantePWM(255-i); 
//    borrarEscribirLCD(String(255-i),"");
//    delay(50);
//  }
  

  moverFrenar();
  nivel=FUERA;
  lcd.clear();
}



//Modo de caída forzada. Tratamos de que llegue al suelo lo más rápido posible. En 181 ms conseguimos ponernos horizontales
void menuHorizontal2() {
  borrarEscribirLCD("CAMBIO A MODO","  HORIZONTAL");
  delay(2000);

  caidaForzada();


  moverFrenar();
  nivel=FUERA;
  lcd.clear();
}



//Selección de velocidad
void menuVelocidad() {
  switch (velocidadMaxima) {
    case 128: borrarEscribirLCD("CAMBIANDO A","VELOCIDAD: 160"); cambiarVelocidad(160); break;
    case 160: borrarEscribirLCD("CAMBIANDO A","VELOCIDAD: 192"); cambiarVelocidad(192); break;
    case 192: borrarEscribirLCD("CAMBIANDO A","VELOCIDAD: 224"); cambiarVelocidad(224); break;
    case 224: borrarEscribirLCD("CAMBIANDO A","VELOCIDAD: 255"); cambiarVelocidad(255); break;
    case 255: 
    default: borrarEscribirLCD("CAMBIANDO A","VELOCIDAD: 128"); cambiarVelocidad(128); break;
  }
  delay(1000);
  nivel=FUERA;
  lcd.clear();
}

void cambiarVelocidad(int nuevaVelocidad) {
  velocidadMaxima=nuevaVelocidad;    //De 0-255  Me voy a mover en 128-160-192-224-255
  velocidadAuxiliar=velocidadMaxima;
//  int delayGiroLocoI;  //(v=128->g=130) (v=192->g=150) (v=255->g=155)
//  int delayGiroLocoD;  //(v=128->g=160)  (v=192->g=180) (v=255->g=180)
  switch (velocidadMaxima) {
    case 128: delayGiroLocoI=130; delayGiroLocoD=160; limiteGiro=170-velocidadMaxima*2/5; randomGiro=limiteGiro; tiempoSalvacion=100; break;
    case 160: delayGiroLocoI=140; delayGiroLocoD=170; limiteGiro=170-velocidadMaxima*2/5; randomGiro=limiteGiro; tiempoSalvacion=100; break;
    case 192: delayGiroLocoI=150; delayGiroLocoD=180; limiteGiro=170-velocidadMaxima*2/5; randomGiro=limiteGiro; tiempoSalvacion=125; break;
    case 224: delayGiroLocoI=152; delayGiroLocoD=180; limiteGiro=170-velocidadMaxima*2/5; randomGiro=limiteGiro; tiempoSalvacion=200; break;
    case 255: delayGiroLocoI=155; delayGiroLocoD=180; limiteGiro=170-velocidadMaxima*2/5; randomGiro=limiteGiro; tiempoSalvacion=275; break;  //Con 200 se mantiene pero..
  }
}



//Una opcion del menu para probar cosas
void menuBancoPruebas(){
  delay(2000);
  
//  borrarEscribirLCD("EMPUJANDO A 192","");
//  moverAdelantePWM(80); delay (120);
//  moverAdelantePWM(192); delay(400);
//  moverFrenar();
//  
//  delay(5000);
//  
  borrarEscribirLCD("EMPUJANDO A 255","");
  moverAdelantePWM(80); delay (120);
  moverAdelantePWM(255); delay(400);
  moverFrenar();
  
  delay(1000);
  moverFrenar();
  nivel=FUERA;
  lcd.clear();  
}



//Distintas opciones para el menu de sonido
void menuSonido() {
  int lecturaT=analogRead(sharpT);
  int umbral=200;
  if (lecturaT<umbral) {
  }
  else {
    tone(altavoz,(lecturaT-umbral)*25+100,5);
    delay(5);
  }
}

//void menuSonido2() {
////  for (int i=20;i<14000;i++) {
////  tone(altavoz,i,1);delay(1);
////  }
//  marioBros();
//  noTone(altavoz);
//  nivel=FUERA;
//  lcd.clear();
//}


//Aplicacion que enciende o apaga el uso del sensor Trasero
void menuSensorTrasero() {
  if (sensorTrasero) {
    sensorTrasero=0;
    borrarEscribirLCD("ENCENDIENDO EL","SENSOR TRASERO");
  }
  else {
    sensorTrasero=1;
    borrarEscribirLCD("APAGANDO EL","SENSOR TRASERO");
  }
  delay(1000);
  nivel=FUERA;
  lcd.clear();
}
