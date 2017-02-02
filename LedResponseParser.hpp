#include <Arduino.h>
#include <StandardCplusplus.h>
#include <vector>
//#include <sstream>

#ifndef __LEDRESPONSEPARSER_HPP
#define __LEDRESPONSEPARSER_HPP 1

class LedResponseParser {
  private:
    const int VALUE_THRESHOLD_MIN = 200; // analogRead value [0 .. 1023]
    const int VALUE_THRESHOLD_MAX = 500; // analogRead value [0 .. 1023]
    const int MIN_ENABLED_TIME = 10; // [ms]
    bool alreadyEnabled = false;
    std::vector<unsigned long> enabledTimes;
    unsigned long enabledStartMillis;
    bool IsEnabled(int);
  public:
    LedResponseParser();
    void AddMeasurement(int);
    void PrintDebugOutput();
    //std::string ToString();
    std::vector<unsigned long> EnabledTimes();
};

LedResponseParser::LedResponseParser() { }

std::vector<unsigned long> LedResponseParser::EnabledTimes() {
  return enabledTimes;
}

void LedResponseParser::AddMeasurement(int value) {
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

bool LedResponseParser::IsEnabled(int value) {
  return value < VALUE_THRESHOLD_MAX && value > VALUE_THRESHOLD_MIN;
}

/*std::string LedResponseParser::ToString() {
  std::ostringstream stringStream;
  stringStream << "{ size: " << enabledTimes.size() << ", enabledTimes: [";
  //for (auto elapsed : enabledTimes) {
  for (auto it = enabledTimes.begin(); it != enabledTimes.end(); ++it) {
    if (it != enabledTimes.begin()) { stringStream << ", "; }
    stringStream << *it;
  }
  stringStream << "] }";
  return stringStream.str();
}

void LedResponseParser::PrintDebugOutput() {
  Serial.println(toString().c_str());
}*/

void LedResponseParser::PrintDebugOutput() {
  Serial.print("{ size: " + String(enabledTimes.size()) + ", enabledTimes: [");
  //for (auto elapsed : enabledTimes) {
  for (auto it = enabledTimes.begin(); it != enabledTimes.end(); ++it) {
    if (it != enabledTimes.begin()) { Serial.print(", "); }
    Serial.print(*it);
  }
  Serial.println("] }");
}

#endif
