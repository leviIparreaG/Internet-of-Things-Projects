# Temperature and Humidity Monitoring with DHT11 on ESP32

## Description
This project reads temperature and humidity data from a DHT11 sensor connected to an ESP32 microcontroller. The sensor values can be requested and sent back via Bluetooth serial communication.

## Technologies
- ESP32 Dev Module
- DHT11 Temperature and Humidity Sensor
- Arduino IDE
- Bluetooth Serial Communication

## How to Run
1. Connect the DHT11 sensor data pin to the specified GPIO on the ESP32.
2. Upload the Arduino sketch using Arduino IDE.
3. Pair a Bluetooth device and connect via serial.
4. Send commands to request sensor data:
   - 'T' for temperature reading
   - 'H' for humidity reading

## Notes
- Ensure sensor is powered correctly.
- Serial baud rate is set to 115200.
- Can be integrated with other IoT components for extended functionality.
