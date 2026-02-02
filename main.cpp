#include <Arduino.h>
#include <ArduinoJson.h>
#include "ConfigManager.h"

ConfigManager cfgMgr;

void setup() {
  Serial.begin(115200);
  cfgMgr.begin();
  Serial.println("READY_FOR_CONFIG");
}

void loop() {
  if (!Serial.available()) return;

  String line = Serial.readStringUntil('\n');

  StaticJsonDocument<512> doc;
  if (deserializeJson(doc, line)) {
    Serial.println("JSON_ERROR");
    return;
  }

  Config cfg = {};

  strlcpy(cfg.wifiSSID, doc["wifiSSID"] | "", sizeof(cfg.wifiSSID));
  strlcpy(cfg.wifiPassword, doc["wifiPassword"] | "", sizeof(cfg.wifiPassword));
  strlcpy(cfg.macAddress, doc["macAddress"] | "", sizeof(cfg.macAddress));
  strlcpy(cfg.botToken, doc["botToken"] | "", sizeof(cfg.botToken));

  cfg.userId = doc["userId"] | 0;

  strlcpy(cfg.pcTargetIP, doc["pcTargetIP"] | "192.168.1.150", sizeof(cfg.pcTargetIP));
  strlcpy(cfg.psTargetIP, doc["psTargetIP"] | "192.168.1.100", sizeof(cfg.psTargetIP));

  cfgMgr.save(cfg);

  Serial.println("CONFIG_SAVED");
  delay(500);
  ESP.restart();
}
