/*
Aquí voy a desarrollar una estrategia que haga movimientos más fluidos. En vez de girar con radio 0 girar con más radio. Una rueda parada y la otra a tope.
Trabajamos sobre la base de la estrategia agresiva

*/


void estrategiaFluido() {
  eCNY70 estado=sensoresSuelo();
  switch (estado) {
    case Z: determinarDireccionFluido(); break;
    default: maniobraEvasivaFluido(estado);
  }
}


//He eliminado todo lo que escribe por pantalla para que vaya más rápido el programa
void determinarDireccionFluido() {
  int umbral=200;  //Normalmente vale 200
  unsigned long tiempo;
  velocidadMaxima=velocidadAuxiliar;
  //Primero comprobamos si hay algo delante
  int lecturaDD=analogRead(sharpDD);
  int lecturaDI=analogRead(sharpDI);
  if (lecturaDD>umbral) contadorDD++; else contadorDD=0;
  if (lecturaDI>umbral) contadorDI++; else contadorDI=0;
  if ((contadorDD>4)||contadorDI>4) {
    
    //Este bloque sirve para que no se encabrite el robot al pasar de una situación con los motores 
    //girando hacia atras a otra con los motores girando hacia adelante
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
    //Ponemos los contadores a cero para que no se produzcan detecciones fantasmas 
    contadorD=0; contadorI=0; contadorT=0;
    //Por ultimo comprobamos si estamos en alguna transición y tenemos que ir más lentos
    if (millis()-tiempoLento<110) velocidadMaxima=velocidadMinima; //else velocidadMaxima=velocidadAuxiliar;  //El else sobra y creo que es lo que hacía fallar
    movimientoAnterior=ENCARANDO;
    //borrarEscribirLCD(" ADELANTE ","  "+String(lecturaDD)+"  "+String(lecturaDI));
    gobiernaMotores(lecturaDD,lecturaDI);
    return; //Salimos porque ya hemos emitido la orden para los motores, no vamos a comprar los otros sensores
  }
  //Si llegamos aquí es que no hay nada delante, hay que buscar en los otros lados
  //Ahora hay que comprobar si hay algo a los lados o atras
  eMovimientos movimientoActual=INDETERMINADO;
  int lecturaI=analogRead(sharpI);
  int lecturaD=analogRead(sharpD);
  int lecturaT=analogRead(sharpT);
  if (lecturaD>umbral) contadorD++; else contadorD=0;
  if (lecturaI>umbral) contadorI++; else contadorI=0;
  if (lecturaT>umbral+100+500*sensorTrasero) contadorT++; else contadorT=0;
  //El orden de los siguientes if hará que se comporte de una forma u otra
  if (contadorI>4) movimientoActual=IZQUIERDA;
  if (contadorD>4) movimientoActual=DERECHA;
  if (contadorT>18) movimientoActual=MEDIAVUELTA;    //Aqui es que de la vuelta, me da igual para un lado o para otro. Poner un random sería más lento
  switch (movimientoActual) {
    case IZQUIERDA:
      //Este bloque sirve para que no se encabrite el robot al pasar de una situación con los motores 
      //girando hacia atras a otra con los motores girando hacia adelante
      tiempo= millis();
      if (tiempo-tiempoAtras<300) {
        if (tiempo-tiempoAtras<200) {
          if (tiempo-tiempoAtras<100) {
            moverAtrasPWM(velocidadMinima);
            return;
          }
          moverFrenar();
          return;
        }
        else {
          velocidadMaxima=velocidadMinima;
        }
      }
      //Giramos a la izquierda e iniciamos la variable tiempoGirando    
      girarIzquierdaFluido(velocidadMaxima); movimientoAnterior=IZQUIERDA; 
      //borrarEscribirLCD(" DETECTADO "," IZQUIERDA"); 
      tiempoGirando=millis(); tiempoExtra=0; break;
    case DERECHA:
      //Este bloque sirve para que no se encabrite el robot al pasar de una situación con los motores 
      //girando hacia atras a otra con los motores girando hacia adelante    
      tiempo= millis();
      if (tiempo-tiempoAtras<300) {
        if (tiempo-tiempoAtras<200) {
          if (tiempo-tiempoAtras<100) {
            moverAtrasPWM(velocidadMinima);
            return;
          }
          moverFrenar();
          return;
        }
        else {
          velocidadMaxima=velocidadMinima;
        }
      } 
      //Giramos a la derecha e iniciamos la variable tiempoGirando
      girarDerechaFluido(velocidadMaxima); movimientoAnterior=DERECHA; 
      //borrarEscribirLCD(" DETECTADO "," DERECHA");
      tiempoGirando=millis();tiempoExtra=0; break;
    case MEDIAVUELTA:
     //Este bloque sirve para que no se encabrite el robot al pasar de una situación con los motores 
     //girando hacia atras a otra con los motores girando hacia adelante
      tiempo=millis();
      if (tiempo-tiempoAtras<300) {
        if (tiempo-tiempoAtras<200) {
          if (tiempo-tiempoAtras<100) {
            moverAtrasPWM(velocidadMinima);
            return;
          }
          moverFrenar();
          return;
        }
        else {
          velocidadMaxima=velocidadMinima;
        }
      }
       //Giramos a la derecha, aunque podríamos girar igualmente a la izquierda y calculamos el tiempo extra
      girarDerechaFluido(velocidadMaxima); movimientoAnterior=DERECHA; 
      //borrarEscribirLCD(" DETECTADO "," ATRAS");
      tiempoGirando=millis();tiempoExtra=limiteGiro+random(randomGiro); break;
    //Si llegamos aquí quiere decir que el movimientoActual es INDETERMINADO, los sensores no ven al contrario
    default: {
      //Este switch es para parar de girar si llevamos mucho rato
      switch (movimientoAnterior) {
        case ADELANTE: break;
        case ENCARANDO: break;
        //Si llegamos aquí es que estamos girando
        default:
        //La siguiente condición mira si hemos pasado el tiempo asignado para girar
        if ((millis()-tiempoGirando)>limiteGiro+tiempoExtra) {
          movimientoAnterior=ADELANTE;    
          //Esto marca el inicio del tiempo de transición de giro a adelante
          tiempoLento=millis();  
          //Esto se hace para que no se ejecute la condición de transición atras-adelante. Queremos transicion giro-adelante que es la anterior
          tiempoAtras=tiempoAtras-300;  
          //borrarEscribirLCD(" ADELANTE "," BASTA GIRAR");
        }
        break;
      }
      //Ahora continuamos con el movimiento que teníamos antes
      switch (movimientoAnterior) {
        case IZQUIERDA:           girarIzquierdaFluido(velocidadMaxima); break;
        case ATRASIZQUIERDA:
          //Para pasar de atras-adelante girando hay que hacer esta transicion   Atras-girarAtrasFluido-girarAtrasPWM-Adelante      
          if (millis()-tiempoAtras<100) girarIzquierdaAtrasFluido(velocidadMaxima); 
          else girarIzquierdaAtrasPWM(velocidadMaxima,0); break;
        case DERECHA:             girarDerechaFluido(velocidadMaxima); break;
        case ATRASDERECHA: 
          //Para pasar de atras-adelante girando hay que hacer esta transicion   Atras-girarAtrasFluido-girarAtrasPWM-Adelante         
          if (millis()-tiempoAtras<100) girarDerechaAtrasFluido(velocidadMaxima); 
          else girarDerechaAtrasPWM(velocidadMaxima,0); break;
        case ENCARANDO:   
          //El caso de ENCARANDO tiene que tener en cuenta que le ha podido llegar una situación de velocidades capadas por transición
          //Por lo tanto debe examinar si sigue estando en transición y si no lo está elevar las velocidades manteniendo el ratio  
          //Podría ser por una situación de tiempoAtras o de tiempoLento
          tiempo=millis();
          //Primero comprabamos si seguimos en tiempo de transición
          if ((tiempo-tiempoAtras<300)||(tiempo-tiempoLento<110)) {     
            motorIAdelantePWM(motorI); motorDAdelantePWM(motorD);
          }
          else {
            //Luego comprobamos si tenemos las velocidades capadas o no
            if ((motorI==velocidadAuxiliar)||(motorI==velocidadAuxiliar)){
              //Estos ifs son para evitar que se quede dando vueltas como un tonto
              if (motorI<velocidadAuxiliar) motorI++; 
              if (motorD<velocidadAuxiliar) motorD++;
              motorIAdelantePWM(motorI); motorDAdelantePWM(motorD);
            }
            else {
              if (motorI>motorD) {
                motorD=(motorD+1)*velocidadAuxiliar/motorI;  //El +1 es por si es cero
                motorI=velocidadAuxiliar;
                motorIAdelantePWM(motorI); motorDAdelantePWM(motorD);
              }
              else {
                motorI=(motorI+1)*velocidadAuxiliar/motorD;  //El +1 es por si es cero
                motorD=velocidadAuxiliar;
                motorIAdelantePWM(motorI); motorDAdelantePWM(motorD);
              }
            }
          }
           break;
        //case MEDIAVUELTA:         girarDerechaPWM(velocidadMaxima,0); break;
        case QUIETO:              moverFrenar(); break;
        default:
          //Comprobamos que no estamos en transición y nos movemos hacia adelante        
          if (millis()-tiempoLento<110) velocidadMaxima=velocidadMinima; //else velocidadMaxima=velocidadAuxiliar;     
          moverAdelantePWM(velocidadMaxima);
      }
    }                  
  } 
}


//Es igual que la otra solo que añadiendo la contabilizción de tiempo atras
void maniobraEvasivaFluido(eCNY70 sensorActivado) {
  switch (sensorActivado) {
    //Primero los sensores delanteros
    case DD: case DI:
    moverAtrasPWM(255);
    delay(tiempoSalvacion);  //Esto es porque se estaba saliendo un poco
    while (digitalRead(CNY70DD)||digitalRead(CNY70DI)) {
      moverAtrasPWM(255);
    }
    //moverFrenar();  //Esto es para evitar las sacudidas
    if (sensorActivado==DD) {
      movimientoAnterior=ATRASDERECHA;
      //borrarEscribirLCD(" ATRAS "," DERECHA");
      tiempoGirando=millis(); 
      tiempoExtra=115;
    }
    else {
      movimientoAnterior=ATRASIZQUIERDA;
      //borrarEscribirLCD(" ATRAS "," IZQUIERDA");
      tiempoGirando=millis(); 
      tiempoExtra=115;
    }
    tiempoAtras=millis();  //Hacemos esto para que no se levante al girar
    break;
    //Ahora los casos en los que tenemos todo un lado en lo blanco
    //Lo que hago es sacar la parte delantera para que pueda ir luego para alante. Volvería a entrar solo con el sensor trasero activado.
    case D:
    while (digitalRead(CNY70DD)) {
      girarIzquierdaFluido(velocidadAuxiliar);
    }
    movimientoAnterior=ADELANTE;
    break;
    case I:
    while (digitalRead(CNY70DI)) {
      girarDerechaFluido(velocidadAuxiliar);
    }
    movimientoAnterior=ADELANTE;
    break;
    
    //luego ya los traseros
    case TD: case TI:
    while (digitalRead(CNY70TD)||digitalRead(CNY70TI)) {
      moverAdelantePWM(velocidadAuxiliar);
    }
    movimientoAnterior=ADELANTE;
    break;
    default: break;
  }
}




