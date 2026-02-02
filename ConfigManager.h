#pragma once
#include <EEPROM.h>
#include "Config.h"

#define EEPROM_SIZE sizeof(Config)
#define EEPROM_ADDR 0

class ConfigManager {
public:
  void begin() {
    EEPROM.begin(EEPROM_SIZE);
  }

  void save(const Config& cfg) {
    EEPROM.put(EEPROM_ADDR, cfg);
    EEPROM.commit();
  }

  Config load() {
    Config cfg;
    EEPROM.get(EEPROM_ADDR, cfg);
    return cfg;
  }
};
