#include <Arduino.h>
#include <ArduinoJson.h>
#include "ConfigManager.h"

ConfigManager cfgMgr;

bool parseMac(const char* str, uint8_t* mac) {
  return sscanf(
    str,
    "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
    &mac[0], &mac[1], &mac[2],
    &mac[3], &mac[4], &mac[5]
  ) == 6;
}

void setup() {
  Serial.begin(115200);
  cfgMgr.begin();
  Serial.println("READY_FOR_CONFIG");
}

void loop() {
  if (!Serial.available()) return;

  String line = Serial.readStringUntil('\n');

  StaticJsonDocument<512> doc;
  if (deserializeJson(doc, line)) return;

  Config cfg = {};

  strlcpy(cfg.wifiSSID, doc["wifiSSID"] | "", sizeof(cfg.wifiSSID));
  strlcpy(cfg.wifiPassword, doc["wifiPassword"] | "", sizeof(cfg.wifiPassword));
  strlcpy(cfg.botToken, doc["botToken"] | "", sizeof(cfg.botToken));
  strlcpy(cfg.pcTargetIP, doc["pcTargetIP"] | "192.168.1.150", sizeof(cfg.pcTargetIP));
  strlcpy(cfg.psTargetIP, doc["psTargetIP"] | "192.168.1.100", sizeof(cfg.psTargetIP));

  const char* macStr = doc["macAddress"] | "";
  if (!parseMac(macStr, cfg.macAddress)) {
    Serial.println("INVALID_MAC");
    return;
  }

  cfgMgr.save(cfg);

  Serial.println("CONFIG_SAVED");
  delay(500);
  ESP.restart();
}
