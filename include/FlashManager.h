#pragma once 
#include "FS.h"
#include "SPIFFS.h"
#include <vector>
#include <Wifi_creds.h>
#include <ArduinoJson.h>

#define FLASH_DEBUG_SERIAL 1
#ifndef FLASH_DEBUG_SERIAL
#define FLASH_DEBUG_SERIAL 0
#endif
#if FLASH_DEBUG_SERIAL == 1
    #include <Arduino.h>
    #define FLASH_DEBUG_PRINT(s) Serial.print(s);
    #define FLASH_DEBUG_PRINTLN(s) Serial.println(s);
#else
    #define FLASH_DEBUG_PRINT(s) ;
    #define FLASH_DEBUG_PRINTLN(s) ;
#endif

class FlashManager
{
private:
    std::vector<std::pair<String, String>> wifiList;
public:
    FlashManager(/* args */);
    ~FlashManager();
    std::vector<std::pair<String, String>> readWifiConfFromFlash() ;
    Wifi_creds getWifiConfig(int index);
    void printWifiList() ;
    void setup();
};
