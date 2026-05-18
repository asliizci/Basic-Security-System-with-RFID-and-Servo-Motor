# Basic Security System with RFID and Servo Motor
Application Purpose: 
This project is designed to demonstrate an automated access control and detection system using a combination of sensors, actuators, and visual feedback components.
The system waits in idle mode with a blue RGB LED color. An RFID card is scanned using the MFRC522 module. If the card UID matches the pre-defined authorized UID, the system:
* Displays green color on the RGB LED.
* Waits for a person or object to be detected within 20 cm using the HC-SR04 ultrasonic sensor.
* Once detection occurs, the servo motor rotates to simulate a door/gate opening (sweeps from 0° to 180°).
* Returns to 0° after the detection.
* If the card is not authorized, a red LED is shown, and no further action is taken.
The system loops and resets to the idle state. This setup shows a smart entrance gate system where only authorized personnel (RFID access) can pass, and only when they are physically present (verified via ultrasonic sensor). It is useful in security-critical environments like labs, factories, or smart homes.

# Team Member and Details
* Project Team: Öykü Aleyna GÖRÜR & Aslı İZCİ
* Board: ESP32 WROOM-32S 
* Sensor: HC-SR04 Ultrasonic Distance Sensor
* Wireless Communication Module: RFID Module
* DC Motor Selected: Servo Motor
* LED Type: Common Cathode RGB LED 
* Software IDE: Arduino IDE.
* Programming Language: C/C++.
# Fritzing Circuit Diagram

<img width="1386" height="678" alt="Resim6" src="https://github.com/user-attachments/assets/7ff9e5e4-780f-4480-93d5-04eee5198c8e" />

# Simulation

<img width="605" height="289" alt="Resim7" src="https://github.com/user-attachments/assets/70321e94-6465-4f3c-b3c8-9e4a1c32333d" />

# A photo for project

<img width="605" height="454" alt="Resim8" src="https://github.com/user-attachments/assets/49a919dc-6e49-4928-8ba3-414167a6d4c1" />
