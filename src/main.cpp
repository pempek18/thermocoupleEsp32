#include "main.h"

void setup() {
  #if DEBUG_SERIAL == 1
    Serial.begin(115200);
  #endif
  pinMode(DRDY_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
  dsp.setup();
  if (!maxthermo.begin()) {
    DEBUG_PRINTLN("Could not initialize thermocouple.");
    while (1) delay(10);
  }

  maxthermo.setThermocoupleType(MAX31856_TCTYPE_K);

  DEBUG_PRINT("Thermocouple type: ");
  switch (maxthermo.getThermocoupleType() ) {
    case MAX31856_TCTYPE_B: DEBUG_PRINTLN("B Type"); break;
    case MAX31856_TCTYPE_E: DEBUG_PRINTLN("E Type"); break;
    case MAX31856_TCTYPE_J: DEBUG_PRINTLN("J Type"); break;
    case MAX31856_TCTYPE_K: DEBUG_PRINTLN("K Type"); break;
    case MAX31856_TCTYPE_N: DEBUG_PRINTLN("N Type"); break;
    case MAX31856_TCTYPE_R: DEBUG_PRINTLN("R Type"); break;
    case MAX31856_TCTYPE_S: DEBUG_PRINTLN("S Type"); break;
    case MAX31856_TCTYPE_T: DEBUG_PRINTLN("T Type"); break;
    case MAX31856_VMODE_G8: DEBUG_PRINTLN("Voltage x8 Gain mode"); break;
    case MAX31856_VMODE_G32: DEBUG_PRINTLN("Voltage x32 Gain mode"); break;
    default: DEBUG_PRINTLN("Unknown"); break;
  }

  maxthermo.setConversionMode(MAX31856_CONTINUOUS);  
  flash.setup();
  setup_wifi();
  if (WiFi.status() == WL_CONNECTED) {
    TemperatureWebsite.begin();
    dsp.wifiStatus(true);
  } else {
    dsp.wifiStatus(false);
  }
}

void loop() {
  int cnt = 0 ;
  while (digitalRead(DRDY_PIN)) {
    delay(1);
    cnt ++ ;
    if (cnt > 1000) 
      dsp.showTemperature(0.0);
  }  
  DEBUG_PRINTLN("Conversion complete");
  temperature = maxthermo.readThermocoupleTemperature();
  DEBUG_PRINT("Temperature: ");
  DEBUG_PRINTLN(temperature);
  dsp.showTemperature(temperature);
  dsp.wifiStatus(WiFi.status() == WL_CONNECTED);
  DEBUG_PRINT("Fault: ");
  DEBUG_PRINTLN(maxthermo.readFault());
  if (temperature >= MAX_TEMPERATURE && maxthermo.readFault() == 0) {
    DEBUG_PRINTLN("Temperature too high");
    digitalWrite(RELAY_PIN, LOW);
  } else {
    DEBUG_PRINTLN("Temperature low");
    digitalWrite(RELAY_PIN, HIGH);
  }

  if (WiFi.status() == WL_CONNECTED && (millis() - websiteTimestamp > 1000)) {
    websiteTimestamp = millis();
    TemperatureWebsite.prepareXML();
    TemperatureWebsite.refresh();
  }
  delay(500);
}