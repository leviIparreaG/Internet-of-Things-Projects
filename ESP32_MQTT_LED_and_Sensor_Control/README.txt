# ESP32 MQTT Control for LEDs and Sensor Data Publishing

## Description
This project implements an IoT solution using an ESP32 microcontroller connected to multiple LEDs and sensors (DHT11 temperature and humidity sensor, LDR, and potentiometer). The ESP32 communicates with an MQTT broker (broker.hivemq.com) to:

- Receive commands to control individual LEDs or all LEDs simultaneously.
- Publish sensor readings (temperature, humidity, light, and potentiometer voltage) periodically and upon button presses.

The system enables real-time monitoring and remote control of actuators via MQTT topics.

## Features
- MQTT client running on ESP32 using `EspMQTTClient` library.
- Control of five LEDs individually or all at once through subscribed MQTT topics.
- Sensor data publishing every 2 seconds for DHT11 (temperature and humidity).
- On-demand publishing of LDR and potentiometer readings triggered by button presses.
- Serial debug output for monitoring communication and sensor data.

## Technologies
- ESP32 Dev Module
- Arduino IDE
- `EspMQTTClient` library for MQTT communication
- DHT11 temperature and humidity sensor
- MQTT protocol (broker.hivemq.com)

## How to Run
1. Connect LEDs to GPIO pins 14, 27, 26, 25, and 33.
2. Connect DHT11 sensor to GPIO 32, LDR to GPIO 35, potentiometer to GPIO 34.
3. Connect buttons to GPIOs 4 and 15 for LDR and potentiometer triggers.
4. Upload the Arduino sketch to the ESP32.
5. Ensure your MQTT broker (here using HiveMQ public broker) is accessible.
6. Subscribe and publish to topics:
   - Subscribe to `ClaseIoT/PulguisTeam/Actuadores/Led/{0..5}` to control LEDs.
     - `0` controls all LEDs at once.
   - Sensor data is published to topics under `ClaseIoT/PulguisTeam/Sensores/`.

## Notes
- The MQTT broker used is public (`broker.hivemq.com`), for production consider private brokers.
- Topics and client IDs should be customized for multi-device scenarios.
- Sensor readings are validated to avoid publishing invalid data.
- The delay after button presses prevents flooding the broker.

## References
- EspMQTTClient library: https://github.com/tommasodifonzo/EspMQTTClient
- HiveMQ Public MQTT Broker: https://www.hivemq.com/public-mqtt-broker/
- DHT11 sensor usage with ESP32.
