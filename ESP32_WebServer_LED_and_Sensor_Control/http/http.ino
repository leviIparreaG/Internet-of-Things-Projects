#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

//Se hizo con la version ESP32 2.0.0

const char* ssid = "Deptos piso 2";
const char* password = "Casazapotecas504.";

// Pines para LEDs
#define LED1 14
#define LED2 27
#define LED3 26
#define LED4 25
#define LED5 33

// Pines para sensores
#define POT_PIN 34
#define LDR_PIN 35

AsyncWebServer server(80);

// Variables para control automático por potenciómetro
int lastPotValue = 0;
unsigned long lastPotTime = 0;
bool potControlActive = false;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado. IP: " + WiFi.localIP().toString());

  // Configuración de pines
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  ledcSetup(0, 5000, 8); // canal 0 para LED4
  ledcAttachPin(LED4, 0);
  ledcSetup(1, 5000, 8); // canal 1 para LED5
  ledcAttachPin(LED5, 1);

  // Inicializar SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("Error al montar SPIFFS");
    return;
  }

  // Archivos estáticos
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *req) {
    req->send(SPIFFS, "/index.html", "text/html");
  });
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *req) {
    req->send(SPIFFS, "/style.css", "text/css");
  });
  server.on("/control.js", HTTP_GET, [](AsyncWebServerRequest *req) {
    req->send(SPIFFS, "/control.js", "text/javascript");
  });

  // LEDs 1-3 (encendido toggle)
  server.on("/led/1", HTTP_GET, [](AsyncWebServerRequest *req) {
    digitalWrite(LED1, !digitalRead(LED1));
    req->send(200, "text/plain", "LED1 toggled");
  });

  server.on("/led/2", HTTP_GET, [](AsyncWebServerRequest *req) {
    digitalWrite(LED2, !digitalRead(LED2));
    req->send(200, "text/plain", "LED2 toggled");
  });

  server.on("/led/3", HTTP_GET, [](AsyncWebServerRequest *req) {
    digitalWrite(LED3, !digitalRead(LED3));
    req->send(200, "text/plain", "LED3 toggled");
  });

  // PWM LEDs 4 y 5
  server.on("^/led/4/brightness/(\\d+)$", HTTP_GET, [](AsyncWebServerRequest *req){
    if (!potControlActive) {
      int value = req->pathArg(0).toInt();
      ledcWrite(0, value);
    }
    req->send(200, "text/plain", "LED4 brightness set");
  });

  server.on("^/led/5/brightness/(\\d+)$", HTTP_GET, [](AsyncWebServerRequest *req){
    if (!potControlActive) {
      int value = req->pathArg(0).toInt();
      ledcWrite(1, value);
    }
    req->send(200, "text/plain", "LED5 brightness set");
  });

  // Sensor: potenciometro y fotorresistencia
  server.on("/sensor/potenciometro", HTTP_GET, [](AsyncWebServerRequest *req){
    int valor = analogRead(LDR_PIN);
    req->send(200, "text/plain", String(valor));
  });

  server.on("/sensor/fotoresistencia", HTTP_GET, [](AsyncWebServerRequest *req){
    int valor = analogRead(POT_PIN);
    req->send(200, "text/plain", String(valor));
  });

  server.begin();
}

void loop() {
  int potValue = analogRead(LDR_PIN);
  int brillo = map(potValue, 0, 4095, 0, 255);

  // Si el valor cambia significativamente, activar control automático
  if (abs(potValue - lastPotValue) > 15) {
    potControlActive = true;
    lastPotTime = millis();

    ledcWrite(0, brillo); // LED4
    ledcWrite(1, brillo); // LED5
  }

  // Si han pasado 10 segundos sin cambios, desactivar control automático
  if (potControlActive && millis() - lastPotTime > 10000) {
    potControlActive = false;
  }

  lastPotValue = potValue;
  delay(50);
}
