#include <Arduino.h>
#include "LedResponseParser.hpp"
//#include <sstream>


HardwareInterface::LedResponseParser::LedResponseParser() : alreadyEnabled(false) { }

std::vector<unsigned long> HardwareInterface::LedResponseParser::EnabledTimes() {
  return enabledTimes;
}

void HardwareInterface::LedResponseParser::AddMeasurement(int value) {
  if (IsEnabled(value) && !alreadyEnabled) {
    //Serial.println("on");
    alreadyEnabled = true;
    enabledStartMillis = millis();
  } else if (!IsEnabled(value) && alreadyEnabled) {
    //Serial.println("off");
    alreadyEnabled = false;
    unsigned long elapsed = millis() - enabledStartMillis;
    if (elapsed >= MIN_ENABLED_TIME) {
      enabledTimes.push_back(elapsed);
    }
  }
}

bool HardwareInterface::LedResponseParser::IsEnabled(int value) {
  return value < VALUE_THRESHOLD_MAX && value > VALUE_THRESHOLD_MIN;
}

void HardwareInterface::LedResponseParser::PrintDebugOutput() {
  Serial.print("{ size: " + String(enabledTimes.size()) + ", enabledTimes: [");
  //for (auto elapsed : enabledTimes) {
  for (auto it = enabledTimes.begin(); it != enabledTimes.end(); ++it) {
    if (it != enabledTimes.begin()) { Serial.print(", "); }
    Serial.print(*it);
  }
  Serial.println("] }");
}
