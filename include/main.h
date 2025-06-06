#ifndef MAIN_H
#define MAIN_H
#include <Arduino.h>
#include <Adafruit_MAX31856.h>
#include "display.h"
#include "Website.h"
#include "Wifi_control.h"
#include "FlashManager.h"

#define DEBUG_SERIAL 0
#ifndef DEBUG_SERIAL
#define DEBUG_SERIAL 0
#endif
#if DEBUG_SERIAL == 1
    #define DEBUG_PRINT(s) Serial.print(s);
    #define DEBUG_PRINTLN(s) Serial.println(s);
    #define DEBUG_PRINTF(...) Serial.printf(__VA_ARGS__);
#else
    #define DEBUG_PRINT(s) ;
    #define DEBUG_PRINTLN(s) ;
    #define DEBUG_PRINTF(...) ;
#endif

#define DRDY_PIN 35
#define SCK_PIN 18
#define MOSI_PIN 23
#define MISO_PIN 19
#define CS_PIN 27

#define MAX_TEMPERATURE 200.0
#define RELAY_PIN 4

Display dsp;

float temperature = 0.0;
Adafruit_MAX31856 maxthermo = Adafruit_MAX31856(CS_PIN);

Wifi_control wifiCtrl;
FlashManager flash;
unsigned long websiteTimestamp = 0;
class MyWebsite : public Website
{
public:
  MyWebsite(int port) : Website(port) {};
  void prepareXML()
  {
    xmlHeader(1);
    xmlTemperature(999, "Temperature", temperature);
    strcat(XML, "</Data>\n");
  }
};
MyWebsite TemperatureWebsite(80);

void setup_wifi()
{
  vTaskDelay(500 / portTICK_PERIOD_MS);
  wifiCtrl.TestSavedWifiConfig();
}
#endif