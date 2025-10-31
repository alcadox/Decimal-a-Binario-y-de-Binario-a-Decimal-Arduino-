// Definimos los pines que usaremos
int pinInterruptor = 13;  // Interruptor que elige el modo de juego
int ledAmarillo = 12;     // LED amarillo para mostrar número aleatorio (modo 1)
int ledBlanca = 4;        // Botón o sensor para contar (modo 2)

// Arrays para los tres pulsadores y los tres LEDs binarios
int pulsadores[] = {10, 8, 2};   // Pulsadores que representan los bits (1,2,4)
int ledsBinarias[] = {5, 6, 7};  // LEDs que muestran el número binario
int pulsadorEnter = 3;           // Botón para confirmar (ENTER)

void setup() {
  // Inicializamos el generador de números aleatorios
  randomSeed(analogRead(A0));  // Usa una lectura analógica para hacer el número aleatorio más impredecible

  // Configuramos los pines de los pulsadores y LEDs binarios
  for (int i = 0; i < 3; i++) {
    pinMode(pulsadores[i], INPUT);     // Los pulsadores se leen como entrada
    pinMode(ledsBinarias[i], OUTPUT);  // Los LEDs se usan como salida
  }

  // Configuramos el resto de pines
  pinMode(ledBlanca, INPUT);       // Entrada del botón blanco (modo 2)
  pinMode(pulsadorEnter, INPUT);   // Entrada del botón ENTER
  pinMode(pinInterruptor, INPUT);  // Entrada del interruptor que cambia de modo
  pinMode(ledAmarillo, OUTPUT);    // LED amarillo como salida
}

void loop() {
  // Variables para guardar el estado de los LEDs binarios
  int led0 = 0;
  int led1 = 0;
  int led2 = 0;
  int numeroRandom = 0;  // Aquí se guardará el número aleatorio generado
  
  delay(5000); // Espera de 5 segundos antes de empezar (para elegir el modo)

  // Si el interruptor está activado, entra al primer juego
  if (digitalRead(pinInterruptor) == HIGH) {
    numeroRandom = random(1, 8);  // Genera un número aleatorio entre 1 y 7

    // El LED amarillo parpadea tantas veces como el número generado
    for (int i = 0; i < numeroRandom; i++) {
      digitalWrite(ledAmarillo, HIGH);
      delay(300);
      digitalWrite(ledAmarillo, LOW);
      delay(300);
    }

    // Aquí el jugador tiene que intentar adivinar el número en binario
    while (true) {
      if (digitalRead(pulsadorEnter) == HIGH) {
        // Si se pulsa ENTER, se sale del bucle
        break;
      } else {
        // Cada pulsador cambia el estado de su LED correspondiente
        if (digitalRead(pulsadores[0]) == HIGH) {
          led0 = !led0;  // Cambia entre encendido y apagado
          digitalWrite(ledsBinarias[0], led0 ? HIGH : LOW);
          delay(300); // Pequeña pausa para evitar rebotes
        }

        if (digitalRead(pulsadores[1]) == HIGH) {
          led1 = !led1;
          digitalWrite(ledsBinarias[1], led1 ? HIGH : LOW);
          delay(300);
        }

        if (digitalRead(pulsadores[2]) == HIGH) {
          led2 = !led2;
          digitalWrite(ledsBinarias[2], led2 ? HIGH : LOW);
          delay(300);
        }
      }
    }

    // Convierte el valor binario de los LEDs a número decimal
    int numeroIntroducido = led2 * 4 + led1 * 2 + led0 * 1;

    // Compara el número introducido con el número aleatorio
    if (numeroIntroducido == numeroRandom) {
      // Si acierta, los LEDs parpadean rápidamente 3 veces
      for (int i = 0; i < 3; i++) {
        digitalWrite(ledsBinarias[0], HIGH);
        digitalWrite(ledsBinarias[1], HIGH);
        digitalWrite(ledsBinarias[2], HIGH);
        delay(300);
        digitalWrite(ledsBinarias[0], LOW);
        digitalWrite(ledsBinarias[1], LOW);
        digitalWrite(ledsBinarias[2], LOW);
        delay(300);
      }
    } else {
      // Si falla, los LEDs parpadean de forma más lenta
      for (int i = 0; i < 3; i++) {
        digitalWrite(ledsBinarias[0], HIGH);
        delay(200);
        digitalWrite(ledsBinarias[1], HIGH);
        delay(200);
        digitalWrite(ledsBinarias[2], HIGH);
        delay(200);
        digitalWrite(ledsBinarias[0], LOW);
        delay(200);
        digitalWrite(ledsBinarias[1], LOW);
        delay(200);
        digitalWrite(ledsBinarias[2], LOW);
        delay(200);
      }
    }
  } 
  // Si el interruptor NO está activado, entra al segundo juego
  else {
    int numeroRandom = random(1, 8);  // Genera un número entre 1 y 7

    // Convierte el número a binario para mostrarlo con los LEDs
    int led0 = numeroRandom & 1;
    int led1 = (numeroRandom >> 1) & 1;
    int led2 = (numeroRandom >> 2) & 1;

    // Enciende los LEDs según el número generado
    if (led0 == 1){
      digitalWrite(ledsBinarias[0], HIGH);
    }
    if (led1 == 1){
      digitalWrite(ledsBinarias[1], HIGH);
    }
    if (led2 == 1){
      digitalWrite(ledsBinarias[2], HIGH);
    }

    int contador = 0;  // Contará las veces que se pulsa el botón blanco

    // El jugador debe pulsar el botón blanco el mismo número de veces que el número mostrado
    while(true){
      if (digitalRead(ledBlanca) == HIGH){
        // Espera a que se suelte el botón para contar solo una vez por pulsación
        while (true){
          if (digitalRead(ledBlanca) == LOW){
            contador++;  // Suma uno al contador
            break;
          }
        }
      }
      
      if (digitalRead(pulsadorEnter) == HIGH) {
        // Si se pulsa ENTER, se termina el juego
        break;
      }
    }
    
    // Comprueba si el número de pulsaciones es correcto
    if (contador == numeroRandom) {
      // Si acierta, los LEDs parpadean rápidamente 3 veces
      for (int i = 0; i < 3; i++) {
        digitalWrite(ledsBinarias[0], HIGH);
        digitalWrite(ledsBinarias[1], HIGH);
        digitalWrite(ledsBinarias[2], HIGH);
        delay(300);
        digitalWrite(ledsBinarias[0], LOW);
        digitalWrite(ledsBinarias[1], LOW);
        digitalWrite(ledsBinarias[2], LOW);
        delay(300);
      }
    } else {
      // Si se equivoca, los LEDs parpadean más despacio
      for (int i = 0; i < 3; i++) {
        digitalWrite(ledsBinarias[0], HIGH);
        delay(200);
        digitalWrite(ledsBinarias[1], HIGH);
        delay(200);
        digitalWrite(ledsBinarias[2], HIGH);
        delay(200);
        digitalWrite(ledsBinarias[0], LOW);
        delay(200);
        digitalWrite(ledsBinarias[1], LOW);
        delay(200);
        digitalWrite(ledsBinarias[2], LOW);
        delay(200);
      }
    }
  }

  delay(2000); // Espera 2 segundos antes de volver a empezar
}
