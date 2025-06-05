#include <FlashManager.h>

FlashManager::FlashManager(/* args */)
{
}

FlashManager::~FlashManager()
{
}

std::vector<std::pair<String, String>> FlashManager::readWifiConfFromFlash()
{
  wifiList.clear();
  File file = SPIFFS.open("/networks.json", FILE_READ);
  if (!file) {
    FLASH_DEBUG_PRINTLN("Failed to open networks.json file");
    return wifiList;
  }

  // Parse JSON
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, file);
  file.close();

  if (error) {
    FLASH_DEBUG_PRINTLN("Failed to parse JSON");
    return wifiList;
  }

  // Read each network entry
  JsonArray networks = doc.as<JsonArray>();
  for (JsonObject network : networks) {
    String ssid = network["ssid"].as<String>();
    String password = network["password"].as<String>();
    wifiList.push_back(std::make_pair(ssid, password));
  }

  return wifiList;
}

Wifi_creds FlashManager::getWifiConfig(int index)
{
  Wifi_creds creds;

  if (index >= 0 && index < wifiList.size()) {
    creds.set(wifiList[index].first, wifiList[index].second);
    return creds;
  } else {
    // Return an empty pair if the index is out of bounds
    return creds;
  }
}
void FlashManager::printWifiList()
{
  for (const auto& wifi : wifiList) {
    FLASH_DEBUG_PRINT("SSID: ");
    FLASH_DEBUG_PRINT(wifi.first);
    FLASH_DEBUG_PRINT(", Password: ");
    FLASH_DEBUG_PRINTLN(wifi.second);
  }
}

void FlashManager::setup()
{
  if (!SPIFFS.begin(true)) {
    FLASH_DEBUG_PRINTLN("Failed to mount file system");
    return;
  }

}
