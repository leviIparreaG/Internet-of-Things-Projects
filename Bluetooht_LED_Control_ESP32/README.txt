# Bluetooth LED Control with ESP32

## Description
This project implements control of multiple LEDs connected to an ESP32 microcontroller via Bluetooth commands. Users can toggle individual LEDs on or off by sending specific characters through a Bluetooth serial connection.

## Technologies
- ESP32 Dev Module
- Arduino IDE
- Bluetooth Serial Communication

## How to Run
1. Connect the LEDs to the specified GPIO pins on the ESP32.
2. Upload the Arduino sketch to the ESP32 using Arduino IDE.
3. Pair a Bluetooth-enabled device (smartphone or PC) with the ESP32.
4. Send the following commands over Bluetooth:
   - '0': Turn off all LEDs
   - '1' to '5': Toggle corresponding LED (1 to 5)

## Notes
- Ensure proper wiring of LEDs and resistors to the ESP32 pins.
- Serial communication is set at 115200 baud rate.
- Can be extended to include sensor data or more commands.
