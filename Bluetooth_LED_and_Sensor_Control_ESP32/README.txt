# Bluetooth LED and Sensor Control with ESP32

## Description
This project demonstrates controlling multiple LEDs connected to an ESP32 microcontroller via Bluetooth commands, as well as reading temperature and humidity data from a DHT11 sensor. Commands allow toggling LEDs and querying sensor readings remotely.

The system integrates Bluetooth serial communication, sensor data acquisition, and LED control logic in a compact and efficient Arduino sketch.

## Technologies
- ESP32 Dev Module
- Arduino IDE
- Bluetooth Serial Communication
- DHT11 Temperature and Humidity Sensor

## How to Run
1. Connect LEDs and DHT11 sensor to the specified GPIO pins on the ESP32.
2. Upload the Arduino sketch using Arduino IDE.
3. Pair and connect a Bluetooth-enabled device to the ESP32.
4. Send commands via Bluetooth:
   - '0' to turn off all LEDs
   - '1' to '5' to toggle individual LEDs
   - 'T' to request temperature
   - 'H' to request humidity

## Notes
- Ensure wiring matches the GPIO pin assignments in the code.
- Bluetooth baud rate is set at 115200.
- Code can be extended for additional sensors or more complex controls.
