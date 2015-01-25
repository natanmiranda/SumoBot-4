//Defino aquí las enumeraciones porque si no no se pueden usar como funciones

//Ahora voy a definir las enumeraciones que utilizaremos como variables globales de control de flujo
enum eModo {COMBATE, MENU};  //eModo Enumeración Modo, asi puedo usar modo como variable
//Cuando se añade una nueva opción al menu hay que meterla en aplicaciones menu y tambien en la pulsacion de boton.
enum eMenu {ESTRATEGIA, SHARP, CNY70, BATERIA, LUZ, FANTASTICO,RESET,RADAR,PRUEBAMOTOR,PRUEBAHUIR,PRUEBAESTRATEGIA,
SHARP2,GIROLOCOD,GIROLOCOI,VERTICAL,HORIZONTAL,HORIZONTAL2,VELOCIDAD,BANCOPRUEBAS,SONIDO,SENSORTRASERO};
enum eNivel {FUERA, DENTRO};
enum eLuz{ENCENDIDA, APAGADA};
enum eEstrategia{ AGRESIVA,VUELTAS,FLUIDO,SUICIDA,WALLRACE,COBARDE};
enum eCNY70 {DD,DI,TD,TI,Z,D,I};
enum eMovimientos {ADELANTE,ATRAS,DERECHA,IZQUIERDA,ATRASDERECHA,ATRASIZQUIERDA,INDETERMINADO,MEDIAVUELTA,QUIETO,ENCARANDO};
