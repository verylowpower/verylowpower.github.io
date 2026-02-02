#include <Arduino.h>
#include <ArduinoJson.h>
#include "ConfigManager.h"

ConfigManager cfgMgr;

void setup() {
  Serial.begin(115200);
  cfgMgr.begin();
  delay(500);
  Serial.println("READY_FOR_CONFIG");
}

void loop() {
  if (!Serial.available()) return;

  String line = Serial.readStringUntil('\n');

  StaticJsonDocument<768> doc;
  if (deserializeJson(doc, line)) {
    Serial.println("JSON_ERROR");
    return;
  }

  Config cfg = {};

  strlcpy(cfg.wifiSSID, doc["wifiSSID"] | "", sizeof(cfg.wifiSSID));
  strlcpy(cfg.wifiPassword, doc["wifiPassword"] | "", sizeof(cfg.wifiPassword));
  strlcpy(cfg.macAddress, doc["macAddress"] | "", sizeof(cfg.macAddress));
  strlcpy(cfg.botToken, doc["botToken"] | "", sizeof(cfg.botToken));

  JsonArray owners = doc["botOwnerIds"];
  for (int i = 0; i < MAX_OWNER; i++) {
    if (owners && i < owners.size()) {
      strlcpy(cfg.botOwnerIds[i], owners[i] | "", sizeof(cfg.botOwnerIds[i]));
    } else {
      cfg.botOwnerIds[i][0] = '\0';
    }
  }

  strlcpy(cfg.pcTargetIP, doc["PCTargetIP"] | "192.168.1.150", sizeof(cfg.pcTargetIP));
  strlcpy(cfg.psTargetIP, doc["PSTargetIP"] | "192.168.1.100", sizeof(cfg.psTargetIP));

  cfgMgr.save(cfg);

  Serial.println("CONFIG_SAVED");
  delay(500);
  ESP.restart();
}
