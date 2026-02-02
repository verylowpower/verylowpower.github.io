#pragma once
#include <Arduino.h>

struct Config {
  char wifiSSID[32];
  char wifiPassword[32];
  uint8_t macAddress[6];
  char botToken[64];
  char botOwnerIds[3][32];   // tối đa 3 user
  char pcTargetIP[16];
  char psTargetIP[16];
};
