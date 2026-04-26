// Establish LED and buttons pin numbers
const int LED_PIN = 2;
const int BUTTON1_PIN = 3;
const int BUTTON2_PIN = 4;

// Build blink function
void blink() {
  digitalWrite(LED_PIN, HIGH);
  delay(750);
  digitalWrite(LED_PIN, LOW);
  delay(750);
}

// Setup button logic
void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
}

void loop() {
  // Establish button states
  int BUTTON1_STATE = digitalRead(BUTTON1_PIN);
  int BUTTON2_STATE = digitalRead(BUTTON2_PIN);

  // AND function
  if (BUTTON1_STATE == LOW && BUTTON2_STATE == LOW) {
    blink();
  }
}

