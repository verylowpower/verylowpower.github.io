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
  delay(1000);

  cfgMgr.begin();

  Serial.println("================================");
  Serial.println("ESP READY_FOR_CONFIG");
  Serial.println("Waiting JSON over Serial...");
  Serial.println("================================");
}

void loop() {
  if (!Serial.available()) return;

  String line = Serial.readStringUntil('\n');
  Serial.println("RX: " + line);

  StaticJsonDocument<768> doc;
  if (deserializeJson(doc, line)) {
    Serial.println("ERROR: JSON PARSE FAILED");
    return;
  }

  Config cfg = {};

  strlcpy(cfg.wifiSSID, doc["wifiSSID"] | "", sizeof(cfg.wifiSSID));
  strlcpy(cfg.wifiPassword, doc["wifiPassword"] | "", sizeof(cfg.wifiPassword));
  strlcpy(cfg.botToken, doc["botToken"] | "", sizeof(cfg.botToken));
  strlcpy(cfg.pcTargetIP, doc["PCTargetIP"] | "192.168.1.150", sizeof(cfg.pcTargetIP));
  strlcpy(cfg.psTargetIP, doc["PSTargetIP"] | "192.168.1.100", sizeof(cfg.psTargetIP));

  const char* macStr = doc["macAddress"] | "";
  if (!parseMac(macStr, cfg.macAddress)) {
    Serial.println("ERROR: INVALID MAC FORMAT");
    return;
  }

  JsonArray owners = doc["botOwnerIds"];
  for (int i = 0; i < owners.size() && i < 3; i++) {
    strlcpy(cfg.botOwnerIds[i], owners[i], sizeof(cfg.botOwnerIds[i]));
  }

  cfgMgr.save(cfg);

  Serial.println("CONFIG_SAVED_OK");
  Serial.println("REBOOTING...");
  delay(1000);
  ESP.restart();
}
