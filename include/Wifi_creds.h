#include <WString.h>
#include "esp_wifi.h"

class Wifi_creds
{
public:
  Wifi_creds();
  Wifi_creds(const String ssid, const String pass);
  ~Wifi_creds();
  void set(const String ssid, const String pass);
  char *getSSID_CH()
  {
    return ssid_ch;
  }
  String getSSID_S()
  {
    return ssid;
  }
  char *getPASS_CH()
  {
    return pass_ch;
  }
  String getPASS_S()
  {
    return pass;
  }

private:
  String ssid;
  String pass;
  char *ssid_ch = nullptr;
  char *pass_ch = nullptr;
  void cleanup();
};
