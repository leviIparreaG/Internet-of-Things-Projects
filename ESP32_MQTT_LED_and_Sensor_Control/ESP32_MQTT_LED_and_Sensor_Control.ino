#include "EspMQTTClient.h"
#include "DHT.h"

// Pines para LEDs y sensores
#define LED1 14
#define LED2 27
#define LED3 26
#define LED4 25
#define LED5 33
#define BOTON_LDR 4
#define BOTON_POT 15
#define POT_PIN 34
#define LDR_PIN 35
#define DHTPIN 32
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// MQTT Config
const char* ssid = "Deptos piso 2";
const char* password = "Casazapotecas504.";
const char* broker = "broker.hivemq.com";
const char* nameClient = "ESP32_Levi";
const int port = 1883;

// Declarar el tópico
  String T_USER = "ClaseIoT/Equipo";
  
EspMQTTClient client(ssid, password, broker, nameClient, port);

unsigned long lastDHTTime = 0;

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(BOTON_LDR, INPUT_PULLUP);
  pinMode(BOTON_POT, INPUT_PULLUP);

  Serial.println("ESP32 listo!");

      
}

void onConnectionEstablished() {
  // Suscripción a LEDs individuales y todos
  for (int i = 0; i <= 5; i++) {
    String topic = "ClaseIoT/PulguisTeam/Actuadores/Led/" + String(i);
    client.subscribe(topic, [i](const String &payload) {
      if (payload == "1" || payload == "0") {
        int state = payload.toInt();
        if (i == 0) {
          digitalWrite(LED1, state);
          digitalWrite(LED2, state);
          digitalWrite(LED3, state);
          digitalWrite(LED4, state);
          digitalWrite(LED5, state);
          Serial.println("Todos los LEDs " + String(state ? "encendidos" : "apagados"));
        } else {
          int pin;
          switch (i) {
            case 1: pin = LED1; break;
            case 2: pin = LED2; break;
            case 3: pin = LED3; break;
            case 4: pin = LED4; break;
            case 5: pin = LED5; break;
          }
          digitalWrite(pin, state);
          Serial.println("LED" + String(i) + (state ? " encendido" : " apagado"));
        }
      }
    });
  }
}

void loop() {
  client.loop();
  
  
  // Preparar el valor
  String equipo = "PulguisTeam";

  // Publicar cada 5 seg: temperatura y humedad
  if (millis() - lastDHTTime >= 2000) {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (!isnan(h) && !isnan(t)) {
      client.publish("ClaseIoT/Equipo", "PulguisTeam");
      client.publish("ClaseIoT/PulguisTeam/Sensores/DHT/Humedad", String(h));
      client.publish("ClaseIoT/PulguisTeam/Sensores/DHT/Temperatura", String(t));
      client.publish("ClaseIoT/Equipo", "PulguisTeam");
      Serial.println("DHT -> H: " + String(h) + "  T: " + String(t));
      //Serial.println("ClaseIoT/PulguisTeam");
    }
    lastDHTTime = millis();
  }

  // Botón para LDR
  if (digitalRead(BOTON_LDR) == LOW) {
    float ldr = (3.3 / 4096.0) * analogRead(LDR_PIN);
    client.publish("ClaseIoT/PulguisTeam/Sensores/LDR", String(ldr));
    Serial.println("POT -> " + String(ldr) + " V");
    delay(300);
  }

  // Botón para POT
  if (digitalRead(BOTON_POT) == HIGH) {
    float pot = (3.3 / 4096.0) * analogRead(POT_PIN);
    client.publish("ClaseIoT/PulguisTeam/Sensores/Pot", String(pot));
    Serial.println("LDR -> " + String(pot) + " V");
    delay(300);
  }
}
