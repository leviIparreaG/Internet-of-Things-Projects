//Defino pines 
#define led1 14
#define led2 27
#define led3 26
#define led4 25
#define led5 33

//Defino los leds de uso en un arreglo
const int leds[5] = {led1, led2, led3, led4, led5};

// Defino los botones
#define PinBotton_SW1 4  // Botón para avanzar en la secuencia
#define PinBotton_SW2 15 // Botón para reiniciar

int contador = 0; 


// Variables para control por tiempo (tipo debounce)
long timeCounterSW1 = 0;
long timeCounterSW2 = 0;
const int timeThreshold = 150; // Tiempo mínimo entre pulsos (en milisegundos)

int lastStateSW1 = HIGH;
int lastStateSW2 = HIGH;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // Configurar LEDs como salida
  for (int i = 0; i < 5; i++) {
    pinMode(leds[i], OUTPUT);
  }

  // Configurar botones como entrada con resistencia interna pull-up
  pinMode(PinBotton_SW1, INPUT_PULLUP);
  pinMode(PinBotton_SW2, INPUT_PULLUP);

}

void loop() {
  // put your main code here, to run repeatedly:
  int estado1 = digitalRead(PinBotton_SW1);
  int estado2 = digitalRead(PinBotton_SW2);
  long tiempoActual = millis();

 // Detectar flanco de bajada en boton1
  if (estado1 == LOW && lastStateSW1 == HIGH && (tiempoActual - timeCounterSW1 > timeThreshold)) {
    contador++;
    if (contador > 5) {
      contador = 1;
      }
    

          for (int i = 0; i < 5; i++) {
        if (i < contador) {
          digitalWrite(leds[i], HIGH);
        } else {
          digitalWrite(leds[i], LOW);
        }
      }

    Serial.println(contador);
    timeCounterSW1 = tiempoActual;
  }

  // Detectar flanco de bajada en boton2 (reinicio)
  if (estado2 == LOW && lastStateSW2 == HIGH && (tiempoActual - timeCounterSW2 > timeThreshold)) {
    contador = 0;

    for (int i = 0; i < 5; i++) {
      digitalWrite(leds[i], LOW);
    }

    Serial.println("Reset");
    timeCounterSW2 = tiempoActual;
  }

  // Guardar los estados anteriores
  lastStateSW1 = estado1;
  lastStateSW2 = estado2;

}
