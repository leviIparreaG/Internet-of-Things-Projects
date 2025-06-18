# ESP32 Sinric Pro Relay and PWM Control

## Description
This project integrates an ESP32 microcontroller with the Sinric Pro smart home platform to control two relay switches and one dimmable LED using PWM. It connects to Wi-Fi and Sinric Pro's cloud service, enabling remote control of devices via the Sinric Pro app or voice assistants such as Alexa and Google Assistant.

Key features:
- Control of two relay outputs (digital on/off).
- PWM control of one LED for brightness adjustment.
- Wi-Fi connectivity and cloud integration with Sinric Pro.
- Event-driven callbacks for power state and brightness changes.

## Technologies and Libraries
- ESP32 Dev Module
- Arduino IDE with ESP32 Arduino Core (recommended version 2.0.2)
- `SinricPro` library for smart device integration
- Wi-Fi connectivity

## How to Run
1. Connect relays to GPIO pins 14 and 27; connect the dimmable LED to GPIO 26.
2. Install ESP32 Arduino Core version 2.0.2 in Arduino IDE.
3. Install the `SinricPro` Arduino library.
4. Configure your Sinric Pro account and create devices with matching device IDs.
5. Update Wi-Fi credentials, Sinric Pro APP_KEY, and APP_SECRET in the sketch.
6. Upload the sketch to the ESP32.
7. Use the Sinric Pro app or supported voice assistants to control the relays and LED brightness remotely.

## Notes
- PWM channel 0 is configured at 5 kHz and 8-bit resolution for LED dimming.
- Ensure your Sinric Pro devices' IDs match the IDs defined in the code.
- Sinric Pro requires account setup and device linking on their platform.
- This setup avoids MQTT usage; communication is handled via Sinric Pro's cloud APIs.

## References
- Sinric Pro Arduino Library: https://github.com/sinricpro/
- ESP32 Arduino Core: https://github.com/espressif/arduino-esp32
- Sinric Pro Documentation and Examples
