#pragma once
#include <Arduino.h>

struct Config {
  char wifiSSID[32];
  char wifiPassword[32];
  char botToken[64];
  char pcTargetIP[16];
  char psTargetIP[16];
};
