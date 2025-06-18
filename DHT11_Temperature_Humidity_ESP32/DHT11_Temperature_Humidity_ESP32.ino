#define PinPWM 25     // LED 4 (PWM)
#define PinDAC 26     // LED 3 (DAC)
#define PinADCPWM 13  // Lectura PWM
#define PinADCDAC 12  // Lectura DAC

const int freq = 3500;
const int canalPWM = 0;
const int resolucion = 8;

void setup() {
  Serial.begin(115200);

  pinMode(PinDAC, OUTPUT);
  pinMode(PinPWM, OUTPUT);
  pinMode(PinADCPWM, INPUT);
  pinMode(PinADCDAC, INPUT);


  // Configurar PWM correctamente
 
  ledcAttachChannel(PinPWM, freq, resolucion, canalPWM);
}

void loop() {
 
  for (int i = 0; i < 360; i++) {
     float seno = sin(i * M_PI / 180);

   
     float valorPWM = seno * 125.4 ;
     float valorDAC = 127 * seno + 127;


    ledcWrite(PinPWM, valorPWM);  // PWM primero
    dacWrite(PinDAC, valorDAC);   // DAC después

    // Lectura
    float lecturaPWM = analogRead(PinADCPWM)*(3.3/4096.0);
    float lecturaDAC = analogRead(PinADCDAC)*(3.3/4096.0);

    Serial.print("PWM:");
    Serial.print(lecturaPWM);
    Serial.print(",DAC:");
    Serial.println(lecturaDAC);

    delayMicroseconds(4000); 
  }
}
