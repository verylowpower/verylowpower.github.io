#pragma once
#include <Arduino.h>

struct Config {
  char wifiSSID[32];
  char wifiPassword[32];
  char macAddress[18];      // "AA:BB:CC:DD:EE:FF"
  char botToken[64];
  uint64_t userId;          // Discord / Telegram user id
  char pcTargetIP[16];
  char psTargetIP[16];
};
