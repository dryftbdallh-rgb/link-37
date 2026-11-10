#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int btnUpdatePin = 4;
const int btnSosPin = 5;
const int buzzerPin = 18;

float latitude = 30.0444;
float longitude = 31.2357;

void setup() {
  Serial.begin(115200);
  Wire.begin(8, 9);

  pinMode(btnUpdatePin, INPUT_PULLUP);
  pinMode(btnSosPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(15, 15);
  display.println("LINK 37");
  display.setTextSize(1);
  display.setCursor(15, 42);
  display.println("System Ready...");
  display.display();
  
  tone(buzzerPin, 1000, 150);
  delay(2000);
  showNormalScreen();
}

void loop() {
  if (digitalRead(btnUpdatePin) == LOW) {
    tone(buzzerPin, 1500, 100);
    latitude += 0.0002;
    longitude += 0.0002;
    showNormalScreen();
    delay(300);
  }

  if (digitalRead(btnSosPin) == LOW) {
    triggerSOS();
  }
}

void showNormalScreen() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  display.setCursor(0, 0);
  display.println("LINK 37 - TRACKER");
  display.drawLine(0, 10, 128, 10, WHITE);

  display.setCursor(0, 18);
  display.println("GPS Status: LOCKED");

  display.setCursor(0, 32);
  display.print("Lat: ");
  display.println(latitude, 4);

  display.setCursor(0, 44);
  display.print("Lon: ");
  display.println(longitude, 4);

  display.display();
}

void triggerSOS() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(25, 15);
  display.println("! SOS !");
  display.setTextSize(1);
  display.setCursor(10, 45);
  display.println("Sending Location...");
  display.display();

  for (int i = 0; i < 3; i++) {
    tone(buzzerPin, 2000, 250);
    delay(400);
  }

  delay(1500);
  showNormalScreen();
}
