

/* 
Sumo software v11
En este programa voy a implementar la estructura del "Sistema operativo" que va a tener el robot.
Voy a utilizar una serie de variables globales y unos case para dirigir adecuadamente el flujo del robot 
No voy a utilizar tildes
En esta distro voy a probar a usar la libreria serLCD a ver si se solucionan los problemas
http://www.arduino.cc/playground/Learning/SparkFunSerLCD
http://arduino.cc/playground/Code/SerLCD

He tenido que descargar la librería SerLCD
http://flipmu.com/files/2011/12/serLCD.zip
Ha funcionado así que lo voy a dejar asi´, botones en pines 0-2 y pantalla en 3.

V11
En esta versión voy a corregir los problemas al mostrar el valor del voltaje de la bateria por pantalla 
Además voy a añadir una opción al menú para probar los motores

V12
En esta versión reordeno los pines e introduzco un modo de supervivencia

V13
En esta versión introduzco el concepto de offset para los sensores sharp, al final lo he dejado en 60

V14
En esta versión implemento una estrategia que debe ser capaz de rastrear la posición del robot enemigo
Arreglado fallo en los pines de los CNY70

V15
En esta versión voy a tratar de refinar el mecanismo de aproximación al objeto. He visto que es muy brusco.

V16
En esta versión voy a incluir una comprobación del estado de la batería mientras estemos en el modo menú, así en cuanto se descargue me avisará
También voy a mejorar el modo de prueba de rastreo

V17
En esta versión voy a optimizar el algoritmo para que sea más rápido y haré una una forma de apuntar más brusca

V18b
En esta versión voy a experimentar con otra aproximación a la eliminación de ruidos.

V19
En esta versión voy a tratar de que apuntemos mejor al contrario

V19b
Me temo que para apuntar mejor tengo que eliminar el millis

V20
Esta versión es un intento de restaurar el millis, mantener las novedades de la 19, e implementar el contragolpe en los giros.

V21
En esta versión introduzco la respuesta a cuando el robot tiene los dos sensores de suelo sobre la línea blanca. Además renuevo la prueba huída para que funcione
con los nuevos algoritmos. También se mejora el modo coche fantástico para que  pueda llegar a ser usado en combate.

V22
En esta versión vamos a experimentar con la puesta en vertical y horizontal del robot.

V23
En esta versión voy a ajustar lo programado anteriormente al nuevo peso del robot.

V24
En esta versión voy a ver si el algoritmo de combate sigue funcionando con la nueva rampa. Luego iré incrementando la velocidad y viendo si es necesario ajustar algunos valores.
Habrá que hacer un menú para ajustar la velocidad.
Ha habido fallos que atribuyo a la memoria. Cuando compilaba ocupaba 25034 bytes y se reiniciaba constantemente
Entonces he cambiado la secuencia de inicio de ">>>" por otra mucho más ligera y ya ocupa 23802 y no parece que de fallos-

He rehecho la aplicación del radar para ver si se puede o no rastrear

V25  
En esta versión voy a realizar una nueva aproximación al problema del rastreo utilizando las gráficas obtenidas.
Primero voy a actuar sobre el radar

V26
En Esta versión adopto el software a la nueva placa base

V27
En esta versión voy a depurar el algoritmo para que ocupe menos espacio.
24338 es el comienzo
22686 conseguimos eliminando los rastreos y los enables y disables
22352 bytes despues de racionalizar lo que se escribe en los menús
19488 bytes despues de eliminar el offset
19602 bytes ajustando un poco los borrados de pantalla para que no haya parpadeo en la pantalla
Paro de momento porque la reducción ha sido bastante grande y de momento no necesitamos más.

V28
En esta versión cambio los pines de control de los motores para hacer un hueco al altavoz en el pin 10

V29 
En esta versión voy a implementar el giro loco de derechas e izquierdas

V30
En esta versión voy a comprobar que todo funciona más o menos bien después del problema con las ruedas.
Añado la estrategia vueltas al ring
Añado una opcion al menu para probar cosas. BANCOPRUEBAS
He hecho un estudio para la variable limiteGiro y lo pruebo. Lo hago subiendo el umbral a 500 y ver como se mueve en el ring.

V31
En esta versión voy a hacer que el cambio de velocidad de los motores sea mas fluido para que no se levante.
Primero usaré el banco de pruebas para ver en que ocasiones se levanta y como puedo evitarlo.
Despues implementaré las mejoras en la estrategia.

V32
Voy a tratar de mejorar la suavización de los motores

V33
Sigo con el problema del suavizado que está resultando ser más complicado de lo pensado.

V34
En esta versión voy a probar el altavoz

V35
En esta versión voy a probar que el robot apunta bien a otras velocidades y si no modificaré el algoritmo
Estamos en  24210 bytes por lo que es probable que tenga que borrar algo.
23146 bytes despues de elminar algunas estrategias
22234 bytes tras limpiar un poco el menu
22404 bytes Tras corregir fallos en la estrategia Fluido
Voy a quitar también los giros locos.

V36
Tras casi terminar el programa en la V35 voy a ver si tengo que ajustar el tiempoSalvacion para velocidades grandes. Ajustado y funciona.
Voy a poner una opción para activar/desactivar el sensorTrasero

V37
En esta voy a aumentar un poco los tiempos de transición, ya que no se va a notar casi y evitamos que se levante.

V38
Aquí se soluciona el error que se da cuando se queda dando vueltas en modo encarando
Ajustes predeterminados:
V=255
Estrategia=FLUIDO
SensorTrasero=Activado
menu=ESTRATEGIA
modo=MENU  //Es por las dificultades de encender la pantalla

V39 
Aqui voy a poner en el banco de pruebas un programa simple para que empuje. He pensado que lo más sencillo para hacer pruebas es usar 
la misma caja todo el rato e ir poniendole peso. No vamos a saber cual es la capacidad de empuje pero si vamos a poder comparar datos.

V40
En esta versión voy a añadir la estrategia wall-race. 

V41
En esta versión añado la estrategia cobarde

V42
Esta versión es un intento de crear la versión final del software. Elimina lo que no es necesario y pule algunos aspectos como la interfaz de los sharp.
*/


//********************************************************************************
//   LIBRERÍAS UTILIZADAS
//********************************************************************************
#include <serLCD.h>
#include <SoftwareSerial.h>
#include "types.h"

//********************************************************************************
//  PINES DE ARDUINO
//********************************************************************************
//Botones
#define btnSiguiente 2
#define btnIntro 1
#define btnAtras 0
//Pantalla
#define pantallaLCD 3
//Sensores Sharp
#define sharpI 3      //Izquierda
#define sharpDI 2     //Delantero izquierda
#define sharpDD 1
#define sharpD 0
#define sharpT 4
//Batería
#define bateria 5
//Sensores CNY70
#define CNY70DI 4
#define CNY70DD 6
#define CNY70TD 7 
#define CNY70TI 5 
//Pines para control del motor
#define motorI1 9
#define motorI2 8
#define motorD1 11
#define motorD2 12
#define altavoz 10


//********************************************************************************
//    VARIABLES 
//********************************************************************************


//Valores predeterminados de las variables
//eModo modo=COMBATE; //Iniciamos en modo combate de forma predeterminada
eModo modo=MENU; //Iniciamos en modo menu mientras no llegue el campeonato
eMenu menu=ESTRATEGIA;  //define la posicion del menu
eNivel nivel=FUERA;  //define si estamos mirando el menu o dentro de la aplicacion del menu
eLuz luz=ENCENDIDA;  //define si la luz de la pantalla LCD esta encendida o apagada
eEstrategia estrategia=COBARDE;  //define la estrategia que adopta el robot
eEstrategia menuEstrategia=FLUIDO; //define la posicion del menu de estrategia
eMovimientos movimientoAnterior=ADELANTE; //guarda el movimiento anterior del robot

//Objeto para controlar el lcd
serLCD lcd(pantallaLCD);

//Variables de funcionamiento del programa
int delayBoton = 200;  //Esta determina cuanto esperamos tras pulsar el boton en el menu para evitar rebote
int delayCombate = 10;  //Esta determina cuanto tiempo pasa en el modo combate para comprobar que hemos pulsado el boton realmente y no es un fallo.

unsigned long tiempoGirando;    //Esta variable es para no girar indefinidamente
unsigned long tiempoLento;    //Esta variable sirve para evitar que levantemos el morro con cambios de velocidad bruscos
unsigned long tiempoAtras;    //Esta variable sirve para evitar que levantemos el morro con cambios de velocidad bruscos
int tiempoExtra=0;

int velocidadMaxima=128;    //De 0-255  Me voy a mover en 128-160-192-224-255
byte velocidadAuxiliar=velocidadMaxima;
byte velocidadMinima=80;

//Las dos siguientes variables establecen el tiempo de contragolpe en el giro de los motores
int delayGiroLocoI;  //(v=128->g=130) (v=192->g=150) (v=255->g=155)
int delayGiroLocoD;  //(v=128->g=160)  (v=192->g=180) (v=255->g=180)
int tiempoSalvacion=100;  //Este es el tiempo que retrocedemos al detectar que estamos en el borde
int limiteGiro;  //Esta variable sirve para que no estemos girando eternamente sino que pasado un rato vayamos recto.
int randomGiro;

//Variables contadores para eliminar el ruido
int contadorDD=0;
int contadorDI=0;
int contadorD=0;
int contadorT=0;
int contadorI=0;

//Variables motores
unsigned int motorI;
unsigned int motorD;

//Variable para activar 0/ desactivar 1 el sensor trasero. Si el enemigo tiene la capacidad de levantar nuestro
//frontal se va a activar el sensor trasero con terribles consecuencias. Quizá no tan terribles ya que si los sensores delanteros ven al contrario
//el trasero entonces no dice nada por jerarquia
boolean sensorTrasero=0; //Lo pongo activado de serie

//Variable chorra para hacer lo del coche fantastico
int contadorFantastico=7;
boolean direccionFantastico=1;
int numeroAleatorio=random(4); 
//********************************************************************************
//   SETUP
//********************************************************************************
//En setup incluimos aquello que queremos que haga solo al principio del programa, por ejemplo la configuración de los pines
void setup () {
  //Configuramos los pines de sensores y botones como input
  pinMode(btnSiguiente,INPUT);
  pinMode(btnIntro,INPUT);
  pinMode(btnAtras,INPUT);
  pinMode(CNY70DI,INPUT);
  pinMode(CNY70DD,INPUT);
  pinMode(CNY70TI,INPUT);
  pinMode(CNY70TD,INPUT);
  //Configuramos los pines de control del motor como salidas
  pinMode(motorI1,OUTPUT);
  pinMode(motorI2,OUTPUT);
  pinMode(motorD1,OUTPUT);
  pinMode(motorD2,OUTPUT);
  // Conectamos las resistencias internas a los botones, de esta manera no usamos resistencias. Conectamos el boton al pin y a GND
  digitalWrite(btnSiguiente, HIGH);
  digitalWrite(btnIntro, HIGH);
  digitalWrite(btnAtras, HIGH);
  //Iniciamos la variable aleatoria leyendo la batería.
  randomSeed(analogRead(5));
  //Ajustamos los motores
  moverFrenar();
    switch (velocidadMaxima) {
    case 128: delayGiroLocoI=130; delayGiroLocoD=160; limiteGiro=170-velocidadMaxima*2/5; randomGiro=limiteGiro; tiempoSalvacion=100; break;
    case 160: delayGiroLocoI=140; delayGiroLocoD=170; limiteGiro=170-velocidadMaxima*2/5; randomGiro=limiteGiro; tiempoSalvacion=100; break;
    case 192: delayGiroLocoI=150; delayGiroLocoD=180; limiteGiro=170-velocidadMaxima*2/5; randomGiro=limiteGiro; tiempoSalvacion=125; break;
    case 224: delayGiroLocoI=152; delayGiroLocoD=180; limiteGiro=170-velocidadMaxima*2/5; randomGiro=limiteGiro; tiempoSalvacion=200; break;
    case 255: delayGiroLocoI=155; delayGiroLocoD=180; limiteGiro=170-velocidadMaxima*2/5; randomGiro=limiteGiro; tiempoSalvacion=275; break;  //Con 200 se mantiene pero..
  }
  //Enviamos un saludo
  mensajeInicio4();
} 

//********************************************************************************
//   LOOP
//********************************************************************************
void loop () {
  switch (modo) {
    case COMBATE:
    switch (estrategia) {
      //case AGRESIVA:     estrategiaAgresiva() ; break;
      case VUELTAS:      estrategiaVueltas(); break; 
      case FLUIDO:       estrategiaFluido(); break; 
      case SUICIDA:      estrategiaSuicida(); break;
      case WALLRACE:     estrategiaWallRace(); break;
      case COBARDE:      estrategiaCobarde(); break;
      default: borrarEscribirLCD(" FALLO EN "," ESTRATEGIA"); delay(500); lcd.clear(); break;
    }
    pulsacionBoton();
    break;
    
    case MENU:
    switch (nivel) {
      case FUERA: mostrarMenu(); break;
      case DENTRO: ejecutarAplicacion(); break;
      default: borrarEscribirLCD(" FALLO EN "," NIVEL"); delay(500); 
    }
    comprobarBateria();
    pulsacionBoton();
    break;
    
    default: borrarEscribirLCD(" FALLO EN "," MODO"); delay(500);
  }
  //delay(50);
}

