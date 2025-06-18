#include <WiFi.h>
#include "SinricPro.h"
#include "SinricProSwitch.h"
#include "SinricProDimSwitch.h"

#define WIFI_SSID         "Deptos piso 2"
#define WIFI_PASS         "Casazapotecas504."
#define APP_KEY           "f5129924-17f8-4f01-b830-355c984d3c8d"
#define APP_SECRET        "f768552a-2a00-4c0d-b250-5d90622edf42-f22d5bd2-84f6-4f8d-a33a-2403c3943c58"

#define SWITCH_ID_1       "6839e78d6868ee0e887b1bc2"
#define RELAYPIN_1        14

#define SWITCH_ID_2       "683891ff6868ee0e887a1812"
#define RELAYPIN_2        27

#define DIMSWITCH_ID_3    "68389216030990a558a26205"
#define RELAYPIN_3        26

void setupWiFi() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi conectado");
}

bool onPowerState1(const String &deviceId, bool &state) {
  digitalWrite(RELAYPIN_1, state ? HIGH : LOW);
  return true;
}

bool onPowerState2(const String &deviceId, bool &state) {
  digitalWrite(RELAYPIN_2, state ? HIGH : LOW);
  return true;
}

bool onPowerState3(const String &deviceId, bool &state) {
  if (!state) ledcWrite(0, 0); // Apaga el PWM
  return true;
}

bool onBrightness3(const String &deviceId, int &brightness) {
  int pwmValue = map(brightness, 0, 100, 0, 255);
  ledcWrite(0, pwmValue);
  return true;
}

void setupSinricPro() {
  pinMode(RELAYPIN_1, OUTPUT);
  pinMode(RELAYPIN_2, OUTPUT);

  // PWM para LED3
  ledcSetup(0, 5000, 8);
  ledcAttachPin(RELAYPIN_3, 0);

  SinricProSwitch& mySwitch1 = SinricPro[SWITCH_ID_1];
  mySwitch1.onPowerState(onPowerState1);

  SinricProSwitch& mySwitch2 = SinricPro[SWITCH_ID_2];
  mySwitch2.onPowerState(onPowerState2);

  SinricProDimSwitch& myDimSwitch3 = SinricPro[DIMSWITCH_ID_3];
  myDimSwitch3.onPowerState(onPowerState3);
  myDimSwitch3.onBrightness(onBrightness3);

  SinricPro.begin(APP_KEY, APP_SECRET);
}

void setup() {
  setupWiFi();
  setupSinricPro();
}

void loop() {
  SinricPro.handle();
}
