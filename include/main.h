#ifndef MAIN_H
#define MAIN_H
#include <Arduino.h>
#include "display.h"
#include <Adafruit_MAX31856.h>

#define DEBUG_SERIAL 1
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

Display dsp;
#define DRDY_PIN 35
#define SCK_PIN 18
#define MOSI_PIN 23
#define MISO_PIN 19
#define CS_PIN 27

Adafruit_MAX31856 maxthermo = Adafruit_MAX31856(CS_PIN);
#endif