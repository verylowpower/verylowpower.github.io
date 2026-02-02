#include "ConfigManager.h"
#include <Preferences.h>

Preferences prefs;

void ConfigManager::begin() {
  prefs.begin("config", false);
}

void ConfigManager::save(const Config& cfg) {
  prefs.putString("wifiSSID", cfg.wifiSSID);
  prefs.putString("wifiPassword", cfg.wifiPassword);
  prefs.putString("mac", cfg.macAddress);
  prefs.putString("botToken", cfg.botToken);

  for (int i = 0; i < MAX_OWNER; i++) {
    prefs.putString(("owner" + String(i)).c_str(), cfg.botOwnerIds[i]);
  }

  prefs.putString("pcIP", cfg.pcTargetIP);
  prefs.putString("psIP", cfg.psTargetIP);
}
