# ESP32 PWM LED and Sensor Web Control

## Description
This project implements PWM control for LEDs connected to an ESP32 microcontroller via a web server interface. It includes reading sensor values such as a potentiometer and a photoresistor, displaying sensor data on the web page in real-time. The project demonstrates seamless integration of hardware PWM control and sensor monitoring via HTTP RESTful endpoints.

## Features
- Web interface to control LED brightness using sliders.
- Real-time sensor readings displayed on the web page.
- Potentiometer controls LED brightness automatically, disabling manual sliders temporarily.
- JavaScript fetch API for asynchronous communication.
- Responsive design with CSS.

## Technologies
- ESP32 Dev Module
- Arduino IDE
- HTML, CSS, JavaScript
- PWM control and sensor interfacing on ESP32

## How to Run
1. Connect LEDs, potentiometer, and photoresistor to ESP32 GPIOs as specified in the code.
2. Upload the Arduino sketch via Arduino IDE.
3. Connect to the ESP32 Wi-Fi and open the web interface.
4. Adjust LED brightness manually via sliders or automatically with the potentiometer.
5. Monitor sensor values updated periodically on the webpage.

## Notes
- The system disables manual LED brightness control when potentiometer input is active to avoid conflicts.
- The code is modular for easy adaptation to additional devices or sensors.

## References
- ESP32 PWM tutorials.
- Arduino Web Server examples.
- Fetch API and DOM manipulation tutorials.
