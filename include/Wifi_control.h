#pragma once
#include <WString.h>
#include <esp_wifi.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include "FlashManager.h"

#define WIFI_DEBUG_SERIAL 1
#ifndef WIFI_DEBUG_SERIAL
#define WIFI_DEBUG_SERIAL 0
#endif

#if WIFI_DEBUG_SERIAL == 1
    #include <Arduino.h>
    #define WIFI_DEBUG_PRINT(s) Serial.print(s);
    #define WIFI_DEBUG_PRINTLN(s) Serial.println(s);
    #define WIFI_DEBUG_PRINTF(...) Serial.printf(__VA_ARGS__);
#else
    #define WIFI_DEBUG_PRINT(s) ;
    #define WIFI_DEBUG_PRINTLN(s) ;
    #define WIFI_DEBUG_PRINTF(...) ;
#endif

class Wifi_control
{
private:
    IPAddress IP;
    String ssid;
    Wifi_creds readCredentialsFromFile(int line);
    FlashManager flash;
public:
    Wifi_control(/* args */);
    ~Wifi_control();
    void display_connected_devices();
    bool TestSavedWifiConfig();
    bool checkWiFiConnection();
    void createAccessPoint();
    IPAddress GetIp();    
    String GetSsid();
};