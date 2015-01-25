/*
Aqui se encuentra la estrategia cobarde que huye de todo lo que tenga cerca, se basa en otras estrategias anteriores
*/

void estrategiaCobarde() {
  cocheFantastico2(contadorFantastico);
  if (contadorFantastico==0) direccionFantastico=1;
  if (contadorFantastico==15) direccionFantastico=0;
  if (direccionFantastico) contadorFantastico++;
  else contadorFantastico--;
  
  determinarDireccionCobarde();
}



//Falta de meter las transiciones entre movimientos
//Hace falta transición entre Atras->Adelante; Quieto->Adelante
void determinarDireccionCobarde() {
  int umbral=200;  //Normalmente vale 200
  unsigned long tiempo;
  velocidadMaxima=velocidadAuxiliar;
  
  //Primero leemos todos los sensores
  int lecturaDD=analogRead(sharpDD);
  int lecturaDI=analogRead(sharpDI);
  int lecturaI=analogRead(sharpI);
  int lecturaD=analogRead(sharpD);
  int lecturaT=analogRead(sharpT);
  if (lecturaDD>umbral) contadorDD++; else contadorDD=0;
  if (lecturaDI>umbral) contadorDI++; else contadorDI=0;
  if (lecturaD>umbral) contadorD++; else contadorD=0;
  if (lecturaI>umbral) contadorI++; else contadorI=0;
  if (lecturaT>umbral) contadorT++; else contadorT=0;
  //Ahora vemos cuales están activados
  boolean bA=(contadorDD>4)||(contadorDI>4);
  boolean bD=(contadorD>4);
  boolean bI=(contadorI>4);
  boolean bT=(contadorT>4);
  
  
  //Rodeado o no hay nadie
  if ((bD&&bI&&bA&&bT)||!(bD||bI||bA||bT)) {
    //Transicion 
    tiempo=millis();
    if (tiempo-tiempoAtras<100) {
      //Si ha pasado muy poco tiempo seguimos hacia atras pero más lentamente
      moverAtrasPWM(velocidadMinima);
      return;
    }
    movimientoAnterior=QUIETO;
    tiempoLento=millis(); tiempoAtras=0;
    moverFrenar();  //Esto debería sustituirse por movimientos aleatorios típicos de un animal
    //movimientoAleatorio();
    return;
  }
  
  //Enemigo detrás
  if (!bA&&bT) {
    //Transicion Atras->Adelante
    tiempo=millis();
    if (tiempo-tiempoAtras<300) {
      if (tiempo-tiempoAtras<200) {
        if (tiempo-tiempoAtras<100) {
          //Si ha pasado muy poco tiempo seguimos hacia atras pero más lentamente
          moverAtrasPWM(velocidadMinima);
          return;
        }
        //Despues ya frenamos 
        moverFrenar();
        return;
      }
      else {
        //Antes de movernos hacia adelante al maximo avanzamos un poco mas lento
        velocidadMaxima=velocidadMinima;
      }
    }
    //Transicion quieto->adelante
    if (millis()-tiempoLento<110) velocidadMaxima=velocidadMinima;
    movimientoAnterior=ADELANTE;
    moverAdelantePWM(velocidadMaxima);
    return;
  }
  
  //Enemigo delante
  if (bA&&!bT) {
    movimientoAnterior=ATRAS;
    tiempoAtras=millis(); tiempoLento=0;
    moverAtrasPWM(velocidadMaxima);
    return;
  }
  //Enemigo a los lados
  if (bD&&bI) {
    movimientoAnterior=ATRAS;
    moverAtrasPWM(velocidadMaxima);
    return;
  }

  //Enemigo en un lado    
  if (bI) {
    movimientoAnterior=ATRASDERECHA;
    girarDerechaAtrasFluido(velocidadMaxima);
  }
  else {
  //if (bD) {    
    movimientoAnterior=ATRASIZQUIERDA;
    girarIzquierdaAtrasFluido(velocidadMaxima);
  }
  
}

void movimientoAleatorio() {
  int i=random(4);
  if (i==0) numeroAleatorio=random(8);
  switch(numeroAleatorio) {
    case 0: girarDerechaAtrasFluido(50); break;
    case 1: girarIzquierdaAtrasFluido(50); break;
    case 2: girarDerechaFluido(50); break;
    case 3: girarIzquierdaFluido(50); break;    
    default: moverFrenar();
  }
}
