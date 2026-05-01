#define ENABLE 5
#define DIRA 3
#define DIRB 4

#define SPEED_1 125
#define SPEED_2 165
#define SPEED_3 255

//establish LEDs and buttons
const int LED0_PIN = 11;
const int LED1_PIN = 10;
const int LED2_PIN = 9;
const int BUTTON0_PIN = 8;
const int BUTTON1_PIN = 12;

void setup() {
  //set up LEDs and buttons
  pinMode(LED0_PIN, OUTPUT);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(BUTTON0_PIN, INPUT_PULLUP);
  pinMode(BUTTON1_PIN, INPUT_PULLUP);

  //set up motor characteristics
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);
  digitalWrite(DIRA, HIGH);
  digitalWrite(DIRB, LOW);
}

void loop() {
  int b0 = digitalRead(BUTTON0_PIN);
  int b1 = digitalRead(BUTTON1_PIN);
  delay(50); //debounce

  //setup if-else statements
  if (b0 == HIGH && b1 == HIGH) {
    //off
    analogWrite(ENABLE, 0);
    digitalWrite(LED0_PIN, LOW);
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);
  } else if (b0 == LOW && b1 == HIGH) {
    //speed 1
    analogWrite(ENABLE, SPEED_1);
    digitalWrite(LED0_PIN, HIGH);
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);
  } else if (b0 == HIGH && b1 == LOW) {
    //speed 2
    analogWrite(ENABLE, SPEED_2);
    digitalWrite(LED0_PIN, HIGH);
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED2_PIN, LOW);
  } else {
    //speed 3
    analogWrite(ENABLE, SPEED_3);
    digitalWrite(LED0_PIN, HIGH);
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED2_PIN, HIGH);
  }
}

