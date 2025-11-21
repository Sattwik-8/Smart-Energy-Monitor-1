#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int SENSOR_PIN = 34;   // Potentiometer (simulate ACS712)
const int RELAY_PIN  = 5;
const int LED_PIN    = 2;
const int BUZZER_PIN = 15;

const float VOLTAGE = 230.0;      // Simulated mains voltage (for power calc)
float thresholdCurrent = 2.5;     // Threshold in amperes (adjust as needed)
int samples = 20;                 // smoothing samples

float adcToAmp(float adcValue) {
  return (adcValue / 4095.0) * 10.0;
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, HIGH);
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(BUZZER_PIN, LOW);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    while (true) delay(10);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  displayIntro();
}

void displayIntro() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Smart Energy Monitor");
  display.println("");
  display.println("Loading...");
  display.display();
  delay(1200);
}

float readCurrent() {
  long total = 0;
  for (int i = 0; i < samples; i++) {
    total += analogRead(SENSOR_PIN);
    delay(5);
  }
  float avg = total / (float)samples;
  return adcToAmp(avg);
}

void loop() {
  float current = readCurrent();
  float power = VOLTAGE * current;
  unsigned long t = millis();

  display.clearDisplay();
  display.setCursor(0, 0);
  display.printf("Time: %lums\n", t);
  display.println("");
  display.printf("Current: %.2f A\n", current);
  display.println("");
  display.printf("Power: %.1f W\n", power);
  display.println("");
  display.printf("Threshold: %.2f A\n", thresholdCurrent);
  display.display();

  Serial.printf("Current: %.2f A, Power: %.1f W\n", current, power);

  if (current > thresholdCurrent) {
    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(RELAY_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(800);
}
