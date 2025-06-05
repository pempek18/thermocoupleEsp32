#include "main.h"

void setup() {
  dsp.setup();
}

void loop() {
  float temperature = 20.00; // Replace with real sensor reading
  dsp.showTemperature(temperature);
  delay(1000);
}