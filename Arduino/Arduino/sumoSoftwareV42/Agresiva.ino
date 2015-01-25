/*
En esta pestaña voy a ir introduciendo las estrategias

*/

//
//void estrategiaAgresiva() {
//  eCNY70 estado=sensoresSuelo();
//  switch (estado) {
//    case Z: determinarDireccion(); break;
//    default: maniobraEvasiva(estado);
//  }
//}
//


//Funcion sensoresSuelo
eCNY70 sensoresSuelo() {
  //Primero leemos todos los sensores y guardamos sus valores
  boolean cny70DD=digitalRead(CNY70DD);
  boolean cny70TD=digitalRead(CNY70TD);
  boolean cny70DI=digitalRead(CNY70DI);
  boolean cny70TI=digitalRead(CNY70TI);
  //Ahora comprobamos que no esté todo el lado, porque si es así y vamos para atras nos caemos
  if (cny70DD&&cny70TD) return D;
  if (cny70DI&&cny70TI) return I;
  //Ahora que no haya sensores delanteros activados
  if (cny70DD) return DD;
  if (cny70DI) return DI;
  //Luego los traseros. Se podría hacer que no siempre se leyesen con un random por ejemplo
  if (cny70TD) return TD;    //Los quito porque creo que dan problemas
  if (cny70TI) return TI;
  //Si no hay que devolver Z
  return Z;
}
//
////Funcion maniobraEvasiva
//void maniobraEvasiva(eCNY70 sensorActivado) {
//  switch (sensorActivado) {
//    //Primero los sensores delanteros
//    case DD: case DI:
//    moverAtrasPWM(255);
//    delay(tiempoSalvacion);  //Esto es porque se estaba saliendo un poco
//    while (digitalRead(CNY70DD)||digitalRead(CNY70DI)) {
//      moverAtrasPWM(255);
//    }
//    //moverFrenar();  //Esto es para evitar las sacudidas
//    if (sensorActivado==DD) {
//      movimientoAnterior=ATRASDERECHA;
//      //borrarEscribirLCD(" ATRAS "," DERECHA");
//      tiempoGirando=millis(); 
//      tiempoExtra=115;
//    }
//    else {
//      movimientoAnterior=ATRASIZQUIERDA;
//      //borrarEscribirLCD(" ATRAS "," IZQUIERDA");
//      tiempoGirando=millis(); 
//      tiempoExtra=115;
//    }
//    break;
//    //Ahora los casos en los que tenemos todo un lado en lo blanco
//    //Lo que hago es sacar la parte delantera para que pueda ir luego para alante. Volvería a entrar solo con el sensor trasero activado.
//    case D:
//    while (digitalRead(CNY70DD)) {
//      girarIzquierdaPWM(velocidadMaxima,0);
//    }
//    movimientoAnterior=ADELANTE;
//    break;
//    case I:
//    while (digitalRead(CNY70DI)) {
//      girarDerechaPWM(velocidadMaxima,0);
//    }
//    movimientoAnterior=ADELANTE;
//    break;
//    
//    //luego ya los traseros
//    case TD: case TI:
//    while (digitalRead(CNY70TD)||digitalRead(CNY70TI)) {
//      moverAdelantePWM(255);
//    }
//    movimientoAnterior=ADELANTE;
//    break;
//    default: break;
//  }
//}
//
////Esta funcion determina hacia donde se debe mover el robot
//void determinarDireccion() {
//  int umbral=500;  //Normalmente vale 200
//  //Primero comprobamos si hay algo delante
//  int lecturaDD=analogRead(sharpDD);
//  int lecturaDI=analogRead(sharpDI);
//  if (lecturaDD>umbral) contadorDD++; else contadorDD=0;
//  if (lecturaDI>umbral) contadorDI++; else contadorDI=0;
//  if ((contadorDD>4)||contadorDI>4) {
//    //Esto es un contragolpe por si estabamos girando
//    switch (movimientoAnterior) {
//      case DERECHA: case MEDIAVUELTA: case ATRASIZQUIERDA: girarIzquierdaPWM(velocidadMaxima,0); delay(delayGiroLocoD); break;
//      case IZQUIERDA: case ATRASDERECHA: girarDerechaPWM(velocidadMaxima,0); delay(delayGiroLocoI); break;
//      default: break;
//    }
//    contadorD=0;
//    contadorI=0;
//    contadorT=0;
//    movimientoAnterior=ENCARANDO;
//    borrarEscribirLCD(" ADELANTE ","  "+String(lecturaDD)+"  "+String(lecturaDI));
//    gobiernaMotores(lecturaDD,lecturaDI);
//    return; //Salimos porque ya hemos emitido la orden para los motores
//  }
//  //Ahora hay que comprobar si hay algo a los lados o atras
//  eMovimientos movimientoActual=INDETERMINADO;
//  int lecturaI=analogRead(sharpI);
//  int lecturaD=analogRead(sharpD);
//  int lecturaT=analogRead(sharpT);
//  if (lecturaD>umbral) contadorD++; else contadorD=0;
//  if (lecturaI>umbral) contadorI++; else contadorI=0;
//  if (lecturaT>umbral+100) contadorT++; else contadorT=0;
//  if (contadorI>4) movimientoActual=IZQUIERDA;
//  if (contadorD>4) movimientoActual=DERECHA;
//  if (contadorT>18) movimientoActual=MEDIAVUELTA;    //Aqui es que de la vuelta, me da igual para un lado o para otro. Poner un random sería más lento
//  switch (movimientoActual) {
//    case IZQUIERDA:     girarIzquierdaPWM(velocidadMaxima,0); movimientoAnterior=IZQUIERDA; borrarEscribirLCD(" DETECTADO "," IZQUIERDA"); tiempoGirando=millis(); tiempoExtra=0; break;
//    case DERECHA:       girarDerechaPWM(velocidadMaxima,0); movimientoAnterior=DERECHA; borrarEscribirLCD(" DETECTADO "," DERECHA");tiempoGirando=millis();tiempoExtra=0; break;
//    case MEDIAVUELTA:   girarDerechaPWM(velocidadMaxima,0); movimientoAnterior=DERECHA; borrarEscribirLCD(" DETECTADO "," ATRAS");tiempoGirando=millis();tiempoExtra=limiteGiro+random(randomGiro); break;
//    default: {
//      //Este switch es para parar de girar si llevamos mucho rato
//      switch (movimientoAnterior) {
//        case ADELANTE: break;
//        case ENCARANDO: break;
//        default:
//        if ((millis()-tiempoGirando)>limiteGiro+tiempoExtra) {
//          movimientoAnterior=ADELANTE;    //Este tiempo de 140ms es muy importante, si cambia la velocidad máxima probablemente haya que alterarlo
//          tiempoExtra=0;
//          //borrarEscribirLCD(" ADELANTE "," BASTA GIRAR");
//        }
//        break;
//      }
//      switch (movimientoAnterior) {
//        case IZQUIERDA:           girarIzquierdaPWM(velocidadMaxima,0); break;
//        case ATRASIZQUIERDA:      girarIzquierdaAtrasPWM(velocidadMaxima,0); break;
//        case DERECHA:             girarDerechaPWM(velocidadMaxima,0); break;
//        case ATRASDERECHA:        girarDerechaAtrasPWM(velocidadMaxima,0); break;
//        case ENCARANDO:           motorIAdelantePWM(motorI); motorDAdelantePWM(motorD); break;
//        //case MEDIAVUELTA:         girarDerechaPWM(velocidadMaxima,0); break;
//        case QUIETO:              moverFrenar(); break;
//        default:                  moverAdelantePWM(velocidadMaxima);
//      }
//    }                  
//  } 
//}
//



//Esta función va a asignar un duty a cada motor en función de las lecturas de los sensores
//Hay que tener en cuenta que para entrar aquí ya han pasado la criba del umbral
void gobiernaMotores (int xDD, int xDI) {

  //Ahora tengo que distinguir los casos de izquierda o derecha
  if (xDD>xDI) {
    //Tenemos tres franjas, una en la que lecturaDI es muy pequeña, otra en la que va creciendo y una última en la que son muy parecidos.
    //Esta podría ser la condición de muy derecha
    //Hacemos que gire a la derecha
    if (xDI<10) {  //En la derecha los valoresDI bajan muy rápido, no es necesario un umbral
      motorIAdelantePWM(velocidadMaxima); motorI=velocidadMaxima;
      motorDAdelantePWM(0); motorD=0;
    }
    else {
      motorD=96-96*(xDD-xDI)/(xDD+xDI);
      //Esto sería cuando lo tengamos delante o a la izquierda
      //Hacemos que gire ligeramente a la izquierda
      if (motorD>90) {
        motorDAdelantePWM(velocidadMaxima); motorD=velocidadMaxima;
        motorI=velocidadMaxima*90/96;
        motorIAdelantePWM(motorI);
      }
      //Esto es cuando lo tenemos a la derecha
      //HAcemos que gire a la derecha
      else {
        motorIAdelantePWM(velocidadMaxima); motorI=velocidadMaxima;
        motorD=velocidadMaxima*motorD/96;
        motorDAdelantePWM(motorD);
      }
    }
  }
  else {
    //Primero ponemos el motor derecho a tope
    motorDAdelantePWM(velocidadMaxima); motorD=velocidadMaxima;
    //Esto es muy a la izquierda
    if (xDD<60) {  //Cuando tenemos algo muy a la izquierda del sensor oscila mucho, por eso el umbral lo ponemos mucho más alto aquí
      motorIAdelantePWM(0); motorI=0;
    }
    //Esto es entre muy a la izquierda y a la izquierda
    else {
      motorI=96-96*(xDI-xDD)/(xDD+xDI);
      //Esta condición la pongo como giro mínimo, concuerda con lo programado antes
      if (motorI>90) {
        motorI=velocidadMaxima*90/96;
        motorIAdelantePWM(motorI);
      }
      else {
        motorI=velocidadMaxima*motorI/96;
        motorIAdelantePWM(motorI);
      }
    }
  }
  
}
