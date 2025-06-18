# ESP32 Web Server for LED Control and Sensor Monitoring

## Description
This project implements a web server on the ESP32 microcontroller to control LEDs and monitor sensor data remotely through a web interface. Users can toggle three LEDs with buttons and adjust the brightness of two LEDs using sliders (PWM control). Sensor readings from a potentiometer and a photoresistor are displayed and updated every second.

## Features
- Button controls for LEDs 1 to 3.
- PWM brightness adjustment for LEDs 4 and 5 via sliders.
- Live sensor data display for potentiometer and photoresistor.
- Automatic disabling of sliders when potentiometer control is active.
- Responsive and clean web interface with custom CSS styling.
- JavaScript fetch API to communicate with ESP32 REST endpoints.

## Technologies
- ESP32 microcontroller
- Arduino IDE (for ESP32)
- HTML, CSS, JavaScript (vanilla)
- Fetch API for HTTP requests

## How to Run
1. Connect LEDs, potentiometer, and photoresistor to the designated ESP32 GPIO pins.
2. Upload the Arduino sketch that runs the web server to the ESP32.
3. Connect your computer or smartphone to the ESP32's Wi-Fi network.
4. Open the web interface URL provided by the ESP32 (typically its IP address).
5. Use the web page controls to toggle LEDs and adjust brightness.
6. Sensor readings update every second on the page.

## Notes
- The web interface automatically disables the sliders when the potentiometer is in use to prevent conflicts.
- The project can be expanded to include more sensors or controls.
- CSS and JS files are modular and easy to customize.

## References
- ESP32 Web Server examples (Arduino core)
- Fetch API documentation: https://developer.mozilla.org/en-US/docs/Web/API/Fetch_API
- JavaScript DOM manipulation and event handling tutorials
