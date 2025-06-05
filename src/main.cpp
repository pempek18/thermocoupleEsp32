#include <Arduino.h>
#include "main.h"

// Create the display object
Adafruit_SH1106 display(OLED_RESET);

void setupDisplay() {
  display.begin(SH1106_SWITCHCAPVCC, 0x3C, false);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Temperatura");
  display.display();
  delay(1000);
}

void showTemperature(float temp) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Temperatura");
  display.setTextSize(2);
  display.setCursor(0, 24);
  display.printf("%.2f C", temp);
  display.display();
}

void setup() {
  setupDisplay();
}

void loop() {
  float temperature = 20.00; // Replace with real sensor reading
  showTemperature(temperature);
  delay(1000);
}