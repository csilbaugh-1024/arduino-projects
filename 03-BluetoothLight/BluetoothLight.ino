#include <SoftwareSerial.h>

const int LED_PIN = 7;
const int HC_EN = 9;

SoftwareSerial BTSerial(10, 11); // RX, TX 
// The HC-05's TXD connects to the Arduino's RXD and vice versa. This may seem confusing at first,
// but it makes sense considering that the Arduino "receives" what the HC-05 "sends", and 
// "sends" what the HC-05 "receives".

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // set LED low by default
  pinMode(HC_EN, OUTPUT);
  digitalWrite(HC_EN, HIGH); // Keep HC-05 enabled to simplify wiring
  Serial.begin(9600); // Baud Rate
  BTSerial.begin(9600); // Baud Rate
  pinMode(10, INPUT_PULLUP); // software pull-up on RX pin
}

void loop() {
  if (BTSerial.available()) {
    char command = BTSerial.read();
    if (command == '1') {
      digitalWrite(LED_PIN, HIGH); // Illuminate LED when HIGH sent
    }
    else if (command == '0') {
      digitalWrite(LED_PIN, LOW); // LED off when LOW sent
    }
  }
}
