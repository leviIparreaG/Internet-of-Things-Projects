
/*
 * Práctica 000: Bluetooth
 * Universidad Nacional Autónoma de México
 * Facultad de Ciencias
 * Seminario de Ciencias de la Computación A: IoT
 * Requiere: Módulo ESP32, sensor DHT11, LEDs conectados a pines GPIO.
*/

#include "BluetoothSerial.h"
#include "DHT.h"


//Condición para habilitar el bluetooth
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Configuración DHT11
#define DHTPIN 32
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Configuración de pines para LEDs
const int leds[] = {14, 27, 26, 25, 33};
bool estadosLED[5] = {false, false, false, false, false};

// Pines de botones
#define BOTON_TEMP 4  // Pull-up
#define BOTON_HUM 15  // Pull-down

// Objeto Bluetooth
BluetoothSerial BT;

// Control de debounce para botones
unsigned long lastPressTemp = 0;
unsigned long lastPressHum = 0;
const unsigned long debounceDelay = 300;

void setup() {
  Serial.begin(115200);
  dht.begin();
  BT.begin("ESP32_CONTROLADOR");
  Serial.println("Bluetooth iniciado como 'ESP32_CONTROLADOR'");

  for (int i = 0; i < 5; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }
  pinMode(BOTON_TEMP, INPUT);
  pinMode(BOTON_HUM, INPUT);
}

void loop() {
  // Control por Bluetooth
  if (BT.available()) {
    char dato = BT.read();
    Serial.print("Recibido: ");
    Serial.println(dato);

    if (dato >= '1' && dato <= '5') {
      int idx = dato - '1';
      estadosLED[idx] = !estadosLED[idx];
      digitalWrite(leds[idx], estadosLED[idx]);
    } else if (dato == '0') {
      for (int i = 0; i < 5; i++) {
        digitalWrite(leds[i], LOW);
        estadosLED[i] = false;
      }
    } else {
      BT.println("Error: comando no válido");
    }
  }

  // Botón de temperatura
  if (digitalRead(BOTON_TEMP) == LOW && millis() - lastPressTemp > debounceDelay) {
    float t = dht.readTemperature();
    if (!isnan(t)) {
      BT.print("Temperatura: ");
      BT.print(t);
      BT.println(" C");
    } else {
      BT.println("Error al leer temperatura");
    }
    lastPressTemp = millis();
  }

  // Botón de humedad
  if (digitalRead(BOTON_HUM) == HIGH && millis() - lastPressHum > debounceDelay) {
    float h = dht.readHumidity();
    if (!isnan(h)) {
      BT.print("Humedad: ");
      BT.print(h);
      BT.println(" %");
    } else {
      BT.println("Error al leer humedad");
    }
    lastPressHum = millis();
  }
}
