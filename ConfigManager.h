#pragma once
#include <Arduino.h>

#define MAX_OWNER 5

struct Config {
  char wifiSSID[32];
  char wifiPassword[64];
  char macAddress[18];
  char botToken[128];

  char botOwnerIds[MAX_OWNER][24];

  char pcTargetIP[16];
  char psTargetIP[16];
};

class ConfigManager {
public:
  void begin();
  void save(const Config& cfg);
};
