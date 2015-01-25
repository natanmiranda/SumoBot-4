/*
La estrategia suicida es aquella que busca echar al enemigo a toda costa. Si tenemos al enemigo delante aunque estemos en el borde seguiremos empujando
Esto no parece muy recomendable pero podría pasar qeu el adversario tuviese una rampa plana blanca para activar nuestros cny70. En ese caso sin la 
estrategia suicida sería muy dificil vencerle.
La base va a ser la agresiva y la fluida
*/

void estrategiaSuicida() {
  eCNY70 estado=sensoresSueloSuicida();
  switch (estado) {
    case Z: determinarDireccionFluido(); break;
    default: maniobraEvasivaFluido(estado);
  }
}

//Funcion sensoresSuelo
eCNY70 sensoresSueloSuicida() {
  //Primero leemos todos los sensores y guardamos sus valores
  boolean cny70DD=digitalRead(CNY70DD);
  boolean cny70TD=digitalRead(CNY70TD);
  boolean cny70DI=digitalRead(CNY70DI);
  boolean cny70TI=digitalRead(CNY70TI);
  //Ahora comprobamos que no esté todo el lado, porque si es así y vamos para atras nos caemos
  if (cny70DD&&cny70TD) return D;
  if (cny70DI&&cny70TI) return I;
  //Ahora que no haya sensores delanteros activados
  
  if (cny70DD) {
    int lecturaDD=analogRead(sharpDD);
    int lecturaDI=analogRead(sharpDI);
    if ((lecturaDD>300)||(lecturaDI>300)) return Z;
    else return DD;
  }
  if (cny70DI) { 
    int lecturaDD=analogRead(sharpDD);
    int lecturaDI=analogRead(sharpDI);
    if ((lecturaDD>300)||(lecturaDI>300)) return Z;
    else return DI;
  }
  //Luego los traseros. Se podría hacer que no siempre se leyesen con un random por ejemplo
  if (cny70TD) return TD;    //Los quito porque creo que dan problemas
  if (cny70TI) return TI;
  //Si no hay que devolver Z
  return Z;
}

