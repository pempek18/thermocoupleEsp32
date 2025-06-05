#include "Display.h"

Display::Display() {
    display = new Adafruit_SH1106(OLED_RESET);
}

void Display::setup() {
  display->begin(SH1106_SWITCHCAPVCC, 0x3C, false);
  display->clearDisplay();
  display->setTextSize(2);
  display->setTextColor(WHITE);
  display->setCursor(0, 0);
  display->println("Temperatura");
  display->display();
  delay(1000);
}

void Display::showTemperature(float temp) {
  display->clearDisplay();
  display->setTextSize(2);
  display->setTextColor(WHITE);
  display->setCursor(0, 0);
  display->println("Temp:");
  display->setTextSize(2);
  display->setCursor(0, 24);
  display->setTextSize(3);
  display->printf("%.1f C", temp);
  display->display();
}