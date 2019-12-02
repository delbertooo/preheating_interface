#include <Arduino.h>
#include <vector>
//#include <sstream>

#ifndef __LEDRESPONSEPARSER_HPP
#define __LEDRESPONSEPARSER_HPP 1

class LedResponseParser {
  private:
    const int VALUE_THRESHOLD_MIN = 200; // analogRead value [0 .. 1023]
    const int VALUE_THRESHOLD_MAX = 500; // analogRead value [0 .. 1023]
    const int MIN_ENABLED_TIME = 10; // [ms]
    bool alreadyEnabled;
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

#endif
