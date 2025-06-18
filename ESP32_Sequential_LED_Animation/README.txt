# ESP32 Sequential LED Animation

## Description
This project demonstrates a simple sequential LED animation using five LEDs connected to an ESP32 microcontroller. The LEDs turn on one by one from the first to the last and then back from the last to the first, creating a smooth running light effect.

The program uses basic digital output control and timing delays to achieve the animation without any external libraries or communication protocols.

## Technologies
- ESP32 Dev Module
- Arduino IDE

## How to Run
1. Connect five LEDs to GPIO pins 14, 27, 26, 25, and 33, each with appropriate current-limiting resistors.
2. Upload the sketch to the ESP32 using Arduino IDE.
3. Power on the ESP32 and observe the LEDs lighting up sequentially from first to last and back.

## Notes
- The code uses simple digitalWrite and delay functions.
- No external libraries or communication protocols are required.
- Suitable for beginners learning GPIO control and timing on ESP32.

## References
- Arduino official documentation on digital I/O.
- ESP32 GPIO pinout and usage guidelines.
