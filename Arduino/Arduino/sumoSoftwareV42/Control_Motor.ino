/*
En esta pestaña voy a definir las funciones necesarias para controlar los motores
Las funciones creadas son
moverAdelante()
moverAtras()
moverFrenar()
girarDerecha()
girarIzquierda()

moverAdelantePWM(byte duty)
moverAtrasPWM(byte duty)
girarDerechaPWM(byte duty,int radio)
girarIzquierdaPWM(byte duty,int radio)
girarDerechaAtrasPWM(byte duty,int radio)
girarIzquierdaAtrasPWM(byte duty,int radio)

girarDerechaFluido(byte duty)
girarIzquierdaFluido(byte duty)
girarDerechaAtrasFluido(byte duty)
girarIzquierdaAtrasFluido(byte duty)


motorIAtrasPWM(duty);
motorDAtrasPWM(duty);
motorIAdelantePWM(duty);
motorDAdelantePWM(duty);

//Enable y disable han sido eliminadas porque se ha visto que es lo mismo estar frenado que estar en disable

*/

//********************************************************************************
//Las siguientes funciones mueven el robot a máxima velocidad
//********************************************************************************
void moverAdelante() {
  motorIAdelante();
  motorDAdelante();
}
void moverAtras() {
  motorIAtras();
  motorDAtras();
}
void moverFrenar() {
  motorIFrenar();
  motorDFrenar();
}
void girarDerecha(){
  motorIAdelante();
  motorDAtras();
}
void girarIzquierda(){
  motorIAtras();
  motorDAdelante();
}

//Quedan por añadir las de giro que no es sobre si mismo, pero como creo que las de PWM van a ser muy superiores no las hago de momento.

//********************************************************************************
//Las siguientes funciones mueven el robot a la velocidad deseada
//********************************************************************************
void moverAdelantePWM(byte duty) {
  motorIAdelantePWM(duty);
  motorDAdelantePWM(duty);
}
void moverAtrasPWM(byte duty) {
  motorIAtrasPWM(duty);
  motorDAtrasPWM(duty);
}
//Gira a la derecha a una velocidad determinada por el duty con el radio de giro deseado
void girarDerechaPWM(byte duty,int radio) {  //el radio se da en cm
  //duty determian la velocidad de giro de la rueda izquierda, tenemos que calcular la derecha
  int N2=duty*(2*radio-8)/(2*radio+8);  //8 son los 8 cm que hay entre rueda y rueda. (entre el centro de la rueda
  byte duty2;
  motorIAdelantePWM(duty);
  if (N2>=0){
    duty2=N2;
    motorDAdelantePWM(duty2);
  }
  else {
    duty2=-N2;
    motorDAtrasPWM(duty2);
  }
  
}

//Gira a la derecha a una velocidad determinada por el duty con el radio de giro deseado
void girarIzquierdaPWM(byte duty,int radio) {  //el radio se da en cm
  //duty determian la velocidad de giro de la rueda izquierda, tenemos que calcular la derecha
  int N2=duty*(2*radio-8)/(2*radio+8);  //8 son los 8 cm que hay entre rueda y rueda. (entre el centro de la rueda
  byte duty2;
  motorDAdelantePWM(duty);
  if (N2>=0){
    duty2=N2;
    motorIAdelantePWM(duty2);
  }
  else {
    duty2=-N2;
    motorIAtrasPWM(duty2);
  }
  
}

void girarDerechaAtrasPWM(byte duty,int radio) {  //el radio se da en cm
  //duty determian la velocidad de giro de la rueda izquierda, tenemos que calcular la derecha
  int N2=duty*(2*radio-8)/(2*radio+8);  //8 son los 8 cm que hay entre rueda y rueda. (entre el centro de la rueda
  byte duty2;
  motorIAtrasPWM(duty);
  if (N2>=0){
    duty2=N2;
    motorDAtrasPWM(duty2);
  }
  else {
    duty2=-N2;
    motorDAdelantePWM(duty2);
  }
  
}

//Gira a la derecha a una velocidad determinada por el duty con el radio de giro deseado
void girarIzquierdaAtrasPWM(byte duty,int radio) {  //el radio se da en cm
  //duty determian la velocidad de giro de la rueda izquierda, tenemos que calcular la derecha
  int N2=duty*(2*radio-8)/(2*radio+8);  //8 son los 8 cm que hay entre rueda y rueda. (entre el centro de la rueda
  byte duty2;
  motorDAtrasPWM(duty);
  if (N2>=0){
    duty2=N2;
    motorIAtrasPWM(duty2);
  }
  else {
    duty2=-N2;
    motorIAdelantePWM(duty2);
  }
  
}


//********************************************************************************
//Las siguientes funciones mueven los motores a máxima velocidad  (Son usadas por las anteriores funciones)
//********************************************************************************
//Hace girar el motor izquierdo a toda velocidad hacia delante
void motorIAdelante() {
  digitalWrite(motorI1,HIGH);
  digitalWrite(motorI2,LOW);
}
//Hace girar el motor derecho a toda velocidad hacia delante
void motorDAdelante() {
  digitalWrite(motorD1,HIGH);
  digitalWrite(motorD2,LOW);
}
//Hace girar el motor izquierdo a máxima velocidad hacia atras
void motorIAtras() {
  digitalWrite(motorI1,LOW);
  digitalWrite(motorI2,HIGH);
}
//Hace girar el motor derecho a máxima velocidad hacia atras
void motorDAtras() {
  digitalWrite(motorD1,LOW);
  digitalWrite(motorD2,HIGH);
}
//Frena el motor izquierdo
void motorIFrenar() {
  digitalWrite(motorI1,LOW);
  digitalWrite(motorI2,LOW);
}
//Frena el motor izquierdo
void motorDFrenar() {
  digitalWrite(motorD1,LOW);
  digitalWrite(motorD2,LOW);
}



//********************************************************************************
//Las siguientes funciones mueven los motores utilizando PWM (Son usadas por las anteriores funciones)
//********************************************************************************
//Hace girar el motor izquierdo hacia adelante a una velocidad proporcional al duty. Si duty=0 esta parado, si es 255 va a tope.
void motorIAdelantePWM(byte duty) {
  analogWrite(motorI1,duty);
  digitalWrite(motorI2,LOW);
}
//Hace girar el motor derecho hacia adelante a una velocidad proporcional al duty. Si duty=0 esta parado, si es 255 va a tope.
void motorDAdelantePWM(byte duty) {
  analogWrite(motorD1,duty);
  digitalWrite(motorD2,LOW);
}
//Hace girar el motor izquierdo hacia atras a una velocidad proporcional al duty. Si duty=0 esta quieto, si 255 va a tope.
void motorIAtrasPWM(byte duty) {
  duty=255-duty;  //Restamos para que cuando duty de entrada sea 255, este el I1 a 0.
  analogWrite(motorI1,duty);
  digitalWrite(motorI2,HIGH);
}
//Hace girar el motor derecho a máxima velocidad hacia atras
void motorDAtrasPWM(byte duty) {
  duty=255-duty;
  analogWrite(motorD1,duty);
  digitalWrite(motorD2,HIGH);
}

//********************************************************************************
//Las siguientes funciones sirven para suavizar el cambio de velocidad de los motores y evitar que se levante el morro
//********************************************************************************

void arrancadoMotor1(byte n) {
  byte paso=velocidadMaxima/n;
  for (byte i=1;i<=n;i++) {
    moverAdelantePWM(paso*n);
    delay(1);
  }
}

void arrancadoMotor2(byte n) {
  byte velocidadUmbral=80;
  byte paso=(velocidadMaxima-velocidadUmbral)/n;
  for (byte i=1;i<=n;i++) {
    moverAdelantePWM(velocidadUmbral+paso*n);
    delay(1);
  }
}

void arrancadoMotor3(byte n, byte d) {
  byte velocidadUmbral=90;
  moverAdelantePWM(velocidadUmbral); delay(d);
  byte paso=(velocidadMaxima-velocidadUmbral)/n;
  for (byte i=1;i<=n;i++) {
    moverAdelantePWM(velocidadUmbral+paso*n);
    delay(1);
  }
}


//********************************************************************************
//Las siguientes funciones mueven el robot con movimientos fluidos
//********************************************************************************

//Gira a la derecha a una con el motor derecho parado
void girarDerechaFluido(byte duty) { 
  motorIAdelantePWM(duty);
  motorDFrenar();
}

void girarIzquierdaFluido(byte duty) {  
  motorDAdelantePWM(duty);
  motorIFrenar(); 
}

void girarDerechaAtrasFluido(byte duty) {
  motorIAtrasPWM(duty);
  motorDFrenar();
}

void girarIzquierdaAtrasFluido(byte duty) {
  motorDAtrasPWM(duty);
  motorIFrenar();
}


