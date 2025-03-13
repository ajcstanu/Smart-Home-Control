# Smart-Home-Control

# IoT-Based Home Automation System

## Overview
This project enables remote control of home appliances such as lights and fans using an ESP32 microcontroller, Firebase for real-time database storage, and MQTT for communication. The system allows users to control appliances through a web interface or via MQTT messages.

## Features
- **Remote Control**: Turn lights and fans ON/OFF via a web interface.
- **Real-Time Database**: Firebase stores device states.
- **MQTT Protocol**: Ensures low-latency communication between devices.
- **ESP32 Integration**: Handles appliance control and connects to Firebase.

## Components Used
### Hardware
- ESP32 microcontroller
- Relay module (to control AC appliances)
- Power supply
- Wi-Fi network

### Software & Technologies
- C++ (Arduino)
- Firebase Realtime Database
- MQTT (Mosquitto Broker)
- Flask (for backend API)
- HTML, CSS, JavaScript (for frontend UI)

## Installation & Setup
### 1. ESP32 Setup
- Install **Arduino IDE** and add ESP32 board support.
- Install the required libraries: `FirebaseESP32`, `PubSubClient`, and `ESP32Servo`.
- Upload `Esp32_Home_Automation.ino` to your ESP32.

### 2. Backend Setup (Python + MQTT)
- Install dependencies:
  ```bash
  pip install paho-mqtt firebase-admin
  ```
- Update `firebase-credentials.json` and configure `MQTT_BROKER`.
- Run the backend script:
  ```bash
  python backend.py
  ```

### 3. Frontend Setup (Web Interface)
- Open `index.html` in a browser.
- Ensure Firebase URL is correctly set in JavaScript.

## Usage
1. Connect ESP32 to Wi-Fi.
2. Access the web interface and control appliances.
3. Monitor real-time device status in Firebase.
4. MQTT messages can also trigger appliance control.

## Future Enhancements
- **Voice Control**: Integrate with Google Assistant or Alexa.
- **Mobile App**: Develop an Android/iOS app for easier access.
- **AI-Based Automation**: Implement AI-driven power usage optimization.

## License
This project is open-source and can be modified as needed. Contributions are welcome!

