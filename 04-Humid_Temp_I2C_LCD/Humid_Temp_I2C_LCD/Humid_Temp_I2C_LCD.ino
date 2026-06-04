// Include libraries
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// Define constants

// DHT config
const int DHT_PIN   = 4;
#define DHT_TYPE  DHT11

// LED indicator
const int LED_PIN = 8;

// Sensor thresholds
const float TEMP_THRESHOLD = 24.0;  // Celsius
const float HUM_THRESHOLD  = 70.0;  // Percent

// Initialize DHT and LCD
DHT dht(DHT_PIN, DHT_TYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Vars
float hum;
float temp;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Initialize DHT11
  dht.begin();

  // Begin LCD & I2C system
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("booting up...");
  delay(1500);
}

void loop() {
  // Read DHT
  hum   = dht.readHumidity();
  temp  = dht.readTemperature();

  // Error provision
  if (isnan(hum) || isnan(temp)) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sensor error!");
  delay(5000);
  return;
  }

  // Display readings on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp, 1);
  lcd.print(" ");
  lcd.print((char)223); // Degrees symbol
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Hum:  ");
  lcd.print(hum, 1);
  lcd.print(" %");

  // Alarm logic
  if (temp >= TEMP_THRESHOLD && hum >= HUM_THRESHOLD) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  // 2 second interval between LCD updates
  delay(3000);
}