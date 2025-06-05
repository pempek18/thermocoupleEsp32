#include <Wifi_control.h>

Wifi_control::Wifi_control(/* args */)
{
}

Wifi_control::~Wifi_control()
{
}
// https://www.upesy.com/blogs/tutorials/how-create-a-wifi-acces-point-with-esp32
void Wifi_control::display_connected_devices()
{
  wifi_sta_list_t wifi_sta_list;
  tcpip_adapter_sta_list_t adapter_sta_list;
  esp_wifi_ap_get_sta_list(&wifi_sta_list);
  tcpip_adapter_get_sta_list(&wifi_sta_list, &adapter_sta_list);

  if (adapter_sta_list.num > 0)
    WIFI_DEBUG_PRINTLN("-----------");
  for (uint8_t i = 0; i < adapter_sta_list.num; i++)
  {
    tcpip_adapter_sta_info_t station = adapter_sta_list.sta[i];
    WIFI_DEBUG_PRINT((String) "[+] Device " + i + " | MAC : ");
    WIFI_DEBUG_PRINTF("%02X:%02X:%02X:%02X:%02X:%02X", station.mac[0], station.mac[1], station.mac[2], station.mac[3], station.mac[4], station.mac[5]);
    WIFI_DEBUG_PRINT((String) " | IP: ");
    WIFI_DEBUG_PRINTLN(station.ip.addr);
  }
}

bool Wifi_control::TestSavedWifiConfig()
{
  flash.readWifiConfFromFlash();
  flash.printWifiList();

  // Set WiFi to station mode
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  for (uint8_t i = 0; i < 255; i++)
  {
    Wifi_creds creds = flash.getWifiConfig(i);
    ssid = creds.getSSID_S();
    if (creds.getSSID_S() != "" && creds.getPASS_S() != "")
    {
      WIFI_DEBUG_PRINT("Attempting to connect to: ");
      WIFI_DEBUG_PRINTLN(creds.getSSID_S());
      
      WiFi.begin(creds.getSSID_CH(), creds.getPASS_CH());
      
      // Try to connect for up to 20 seconds
      for (int j = 0; j < 20; j++)
      {
        if (WiFi.status() == WL_CONNECTED)
        {
          IP = WiFi.localIP();
          WIFI_DEBUG_PRINT("Connected! IP address: ");
          WIFI_DEBUG_PRINTLN(IP.toString());
          return true;
        }
        WIFI_DEBUG_PRINT(".");
        delay(1000);
      }
      WIFI_DEBUG_PRINTLN("Connection failed");
      WiFi.disconnect();
      delay(100);
    }
    else
    {
      WIFI_DEBUG_PRINTLN("No more SSIDs saved");
      return false;
    }
  }
  return false;
}

IPAddress Wifi_control::GetIp()
{
  return IP;
}
String Wifi_control::GetSsid()
{
  return ssid;
}
bool Wifi_control::checkWiFiConnection()
{
  return WiFi.status() == WL_CONNECTED;
}
void Wifi_control::createAccessPoint()
{
  IPAddress local_ip(192, 168, 0, 1);
  IPAddress mask(255, 255, 255, 0);
  WiFi.softAPConfig(local_ip, local_ip, mask);
  const char *ssid = "TEMPERATURE";
  const char *password = "Temperature123!";
  WiFi.softAPsetHostname(ssid);
  WiFi.softAP(ssid, password);
  delay(1000);
  // To initiate the Soft AP, pause the program if the initialization process encounters an error.
  for (int i = 0; i < 5; i++)
  {
    if (!WiFi.softAP(ssid, password))
    {
      delay(1000);
      WIFI_DEBUG_PRINTLN("Soft AP creation failed.");
    }
    else
    {
      IP = WiFi.softAPIP();
      WIFI_DEBUG_PRINTLN(IP);
      break;
    }
  }
}
