#include "CTBot.h"

#define pinPhoto 34
#define pinLED1 14
#define pinLED2 27

CTBot myBot;

String ssid = "Deptos piso 2";
String pass = "Casazapotecas504.";
String token = "7702450331:AAETfSigZ3z8pNSsscvyYbVenllkSbeWIMY"; 

bool alarmaActiva = false;
int umbral = 1500; // Umbral por defecto

void setup() {
  Serial.begin(115200);
  pinMode(pinPhoto, INPUT);
  pinMode(pinLED1, OUTPUT);
  pinMode(pinLED2, OUTPUT);
  digitalWrite(pinLED1, LOW);
  digitalWrite(pinLED2, LOW);

  myBot.wifiConnect(ssid, pass);
  myBot.setTelegramToken(token);
  delay(1000);

  if (myBot.testConnection())
    Serial.println("Conectado con Bot");
  else
    Serial.println("Error en la conexión");
}

void loop() {
  TBMessage msg;

  // Revisa si hay nuevos mensajes de Telegram
  if (myBot.getNewMessage(msg)) {
    if (msg.text.equalsIgnoreCase("/start")) {
      myBot.sendMessage(msg.sender.id, "¡Bienvenido al bot! Usa /dato para ver la lectura, /umbral <valor> para fijar umbral, /on y /off para activar/desactivar la alarma.");
    }
    else if (msg.text.equalsIgnoreCase("/dato")) {
      int lectura = analogRead(pinPhoto);
      float voltaje = (3.3 / 4095.0) * lectura;
      myBot.sendMessage(msg.sender.id, "Lectura actual: " + String(lectura) + " (" + String(voltaje, 2) + " V)");
    }
    else if (msg.text.startsWith("/umbral")) {
      String val = msg.text.substring(8);
      val.trim();  // Elimina espacios adicionales
      if (val.length() > 0 && val.toInt() != 0) {
        umbral = val.toInt();
        myBot.sendMessage(msg.sender.id, "Umbral actualizado a: " + String(umbral));
      } else {
        myBot.sendMessage(msg.sender.id, "Formato incorrecto. Usa /umbral <valor>. Ej: /umbral 1500");
      }
    }
    else if (msg.text.equalsIgnoreCase("/on")) {
      alarmaActiva = true;
      myBot.sendMessage(msg.sender.id, "Alarma activada.");
    }
    else if (msg.text.equalsIgnoreCase("/off")) {
      alarmaActiva = false;
      digitalWrite(pinLED1, LOW);
      digitalWrite(pinLED2, LOW);
      myBot.sendMessage(msg.sender.id, "Alarma desactivada.");
    }
    else {
      myBot.sendMessage(msg.sender.id, "Comando no válido. Usa /start para ver opciones.");
    }
  }

  // Monitoreo continuo en tiempo real
  int lectura = analogRead(pinPhoto);

  if (alarmaActiva && lectura >= umbral) {
    // Parpadeo persistente mientras se supera el umbral y alarma está activada
    digitalWrite(pinLED1, HIGH);
    digitalWrite(pinLED2, HIGH);
    delay(300);
    digitalWrite(pinLED1, LOW);
    digitalWrite(pinLED2, LOW);

  } else {
    // LEDs apagados si la alarma está activada pero no se supera el umbral
    digitalWrite(pinLED1, LOW);
    digitalWrite(pinLED2, LOW);
    delay(100);
  }
}
