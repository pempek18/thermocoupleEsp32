#pragma once
#include <WebServer.h>
#include <FS.h>
#include <SPIFFS.h>
#include <ESPmDNS.h>

#define WEBSITE_DEBUG_SERIAL 1
#ifndef WEBSITE_DEBUG_SERIAL
#define WEBSITE_DEBUG_SERIAL 0
#endif

#if WEBSITE_DEBUG_SERIAL == 1
    #include <Arduino.h>
    #define WEBSITE_DEBUG_PRINT(s) Serial.print(s);
    #define WEBSITE_DEBUG_PRINTLN(s) Serial.println(s);
#else
    #define WEBSITE_DEBUG_PRINT(s) ;
    #define WEBSITE_DEBUG_PRINTLN(s) ;
#endif

//covers all functionality of webserver 
class Website
{
public :
  Website(int port) : server(port) {};
  char XML[512];
  char buf[32];
  virtual void handleButtonReset(void);
  virtual void handleBtnChange(void);
  virtual void handleBtnDelete(void);
  void htmlRefresh(int iNofPlayer);
  void refresh();
  void prepareXML();
  void xmlHeader(uint16_t record);
  void xmlSensorState(String state);
  void xmlRecord(uint16_t number, String recordName, float time);
  void xmlTemperature(uint16_t number, String recordName, float value);
  void begin();
  WebServer server ;
private :
  String id = "1";
  String value = "value";
  String readHTMLTemplate();
  void SendXML(void) ;
  int _port;
};