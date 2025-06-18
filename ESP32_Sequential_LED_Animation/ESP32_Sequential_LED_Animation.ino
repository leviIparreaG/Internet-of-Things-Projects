/*
*Universidad Nacional Autónoma de México
 *Facultad de Ciencias
 *Licenciatura en Ciencias de la Computación
 *Seminario de Ciencias de la Computación A: Introducción al Internet de las Cosas
 *
 *Escrito por: Levi Iparrea Granados
 */

//Defino pines 
#define led1 14
#define led2 27
#define led3 26
#define led4 25
#define led5 33

//Defino los leds de uso en un arreglo
const int leds[5] = {led1, led2, led3, led4, led5};

  void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 5 ; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 5; i++) {
    digitalWrite(leds[i], HIGH);
    digitalWrite(leds[i-1], LOW);
    delay(150);
  }
  delay(150);

  for (int i = 4; i >= 0; i--) {
    digitalWrite(leds[i], HIGH);
    digitalWrite(leds[i+1], LOW);
    delay(200);
  }
  delay(150);
  
}
