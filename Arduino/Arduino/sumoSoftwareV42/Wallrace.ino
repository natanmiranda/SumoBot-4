/*
Aquí voy a desarrollar el modo de funcionamiento de ir andando cerca de la pared, me voy a apoyar en la estrategia fluido

*/
void estrategiaWallRace() {
  cocheFantastico2(contadorFantastico);
  if (contadorFantastico==0) direccionFantastico=1;
  if (contadorFantastico==15) direccionFantastico=0;
  if (direccionFantastico) contadorFantastico++;
  else contadorFantastico--;
  
  determinarDireccionWallRace();
}


void determinarDireccionWallRace() {
  //Variables que determinan el funcionamiento del programa
  int umbral=200;  //Normalmente vale 200
  int distanciaPared=300;
  int radioMaximo=40;
  
  velocidadMaxima=velocidadAuxiliar;
  //Primero comprobamos si hay algo delante
  int lecturaDD=analogRead(sharpDD);
  int lecturaD=analogRead(sharpD);
  if (lecturaDD>umbral) contadorDD++; else contadorDD=0;
  //Si tenemos un obstaculo delante giramos a la izquierda y salimos
  if ((contadorDD>4)) {
    girarIzquierdaFluido(velocidadMaxima);
    return;
  }
  //Si no hay nada delante tratamos de mantenernos junto a la pared
  int diferencia=lecturaD-distanciaPared;  //Esto estará entre -300 y 300 aproximadamente
  diferencia=diferencia/10; //Ahora entre 30 y -30
  //Caso de que estamos en el rango querido
  if ((diferencia<5)&&(diferencia>-5)) {
    moverAdelantePWM(velocidadMaxima);
    return;
  }
  if (diferencia>0) {
    girarIzquierdaPWM(velocidadMaxima,radioMaximo-diferencia);
  }
  else {
    girarDerechaPWM(velocidadMaxima,radioMaximo+diferencia);
  }
}
