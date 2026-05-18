#include <SPI.h>
#include <MFRC522.h>
#include <ESP32Servo.h>

// RGB LED pins
const int redPin = 25;
const int greenPin = 26;
const int bluePin = 27;

// RFID module pins
#define SS_PIN 5
#define RST_PIN 21
MFRC522 rfid(SS_PIN, RST_PIN);

// Define an authorized RFID UID 
byte authorizedUID[4] = {124, 132, 138, 63};

// HC-SR04 ultrasonic sensor pins
const int trigPin = 33;
const int echoPin = 32;

// Servo motor pin
const int servoPin = 4;
Servo myServo;

void setup() {
  Serial.begin(9600); // Initialize serial communication

  // Set RGB pins as output
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Set ultrasonic pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Attach servo to the defined pin and start at 0°
  myServo.attach(servoPin);
  myServo.write(0);

  // Start SPI communication and initialize RFID module
  SPI.begin();
  rfid.PCD_Init();

  Serial.println("System initialized.");
}

void loop() {
  // Show blue color in idle state
  showColor("blue");

  // Check for a new RFID card
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    Serial.print("Card UID: ");
    for (byte i = 0; i < rfid.uid.size; i++) {
      Serial.print(rfid.uid.uidByte[i], DEC);
      Serial.print(" ");
    }
    Serial.println();

    // Check if the card is authorized
    if (isAuthorized(rfid.uid.uidByte)) {
      Serial.println("✅ Authorized card");
      showColor("green");
    } else {
      Serial.println("❌ Unauthorized card");
      showColor("red");
    }

    delay(2000);
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }

  // Measure distance using ultrasonic sensor
  float distance = getDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // If an object is detected within 20 cm
  if (distance > 0 && distance < 20) {
    // Sweep the servo from 0° to 180°
    for (int i = 0; i <= 180; i += 10) {
      myServo.write(i);
      delay(20);
    }
    // Return to 0° after the sweep
    myServo.write(0);
  } else {
    // No object detected, keep servo at 0°
    myServo.write(0);
  }

  delay(200); // Small delay for stability
}

// Function to calculate distance using HC-SR04
float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout
  float distance = duration * 0.034 / 2;

  if (duration == 0) return -1; // Measurement failed
  return distance;
}

// Compare scanned UID with the authorized UID
bool isAuthorized(byte *uid) {
  for (byte i = 0; i < 4; i++) {
    if (uid[i] != authorizedUID[i]) return false;
  }
  return true;
}

// Show color using digitalWrite (for common cathode RGB LED)
void showColor(String color) {
  digitalWrite(redPin, color == "red" ? HIGH : LOW);
  digitalWrite(greenPin, color == "green" ? HIGH : LOW);
  digitalWrite(bluePin, color == "blue" ? HIGH : LOW);
}
