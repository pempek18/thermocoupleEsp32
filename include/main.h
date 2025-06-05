#ifndef MAIN_H
#define MAIN_H

#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

// Pin definitions (adjust if needed)
#define OLED_RESET    -1  // Reset pin # (or -1 if sharing Arduino reset pin)
#define OLED_DC       -1  // Not used for SH1106 I2C
#define OLED_CS       -1  // Not used for SH1106 I2C

// Create display object (I2C address 0x3C, reset pin not used)
extern Adafruit_SH1106 display;

void setupDisplay();
void showTemperature(float temp);

#endif