const int analogPin = A0;

void setup() {
  Serial.begin(115200);

  // CSV header
  Serial.println("Time_us,Voltage");
}

void loop() {
  unsigned long t = micros();

  int adc = analogRead(analogPin);

  float voltage = adc * (5.0 / 1023.0);

  Serial.print(t);
  Serial.print(",");
  Serial.println(voltage, 4);

  delayMicroseconds(500);
}