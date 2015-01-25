/*
Aquí voy a definir la estrategia que me permita dar vueltas al ring entre la parte blanca y la negra
Me voy a apoyar sobre la base de la estrategia agresiva
*/

void estrategiaVueltas() {
  //Primero vemos como están los sensores del suelo
  eCNY70 estado=sensoresSuelo();
  //Luego actuamos en consecuencia
  vueltasRing(estado);
}

void vueltasRing(eCNY70 sensorActivado) {
  //Con radios de 8 y 30 funciona bien, se queda dentro del circulo sin salir
  switch (sensorActivado) {
    //Caso 1. Solo sensor delantero activado
    case DD:
      girarIzquierdaPWM(velocidadMaxima,10);
      break;
    //Caso 2. Solo sensor trasero activado
    case TD:
      girarIzquierdaPWM(velocidadMaxima,32);
      break;
    //Caso 3. Ambos sensores activados
    case D:
      girarIzquierdaPWM(velocidadMaxima,10);
      break;
    //Caso 4. Ningún sensor activado
    default: 
      girarIzquierdaPWM(velocidadMaxima,32);    //(75-10)/2=32.5
      break;
  }
}
