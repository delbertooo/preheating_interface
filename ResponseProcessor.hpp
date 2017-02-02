#include <Arduino.h>
#include <StandardCplusplus.h>
#include <vector>
//#include <sstream>

#ifndef __RESPONSEPROCESSOR_HPP
#define __RESPONSEPROCESSOR_HPP 1

class ResponseProcessor {
  private:
    const int THRESHOLD_MIN = 200; // analogRead value [0 .. 1023]
    const int THRESHOLD_MAX = 500; // analogRead value [0 .. 1023]
    const int MIN_PRESSED_TIME = 10; // [ms]
    bool alreadyPressed = false;
    std::vector<unsigned long> pressedTimes;
    unsigned long startedPressingMillis;
    bool IsPressed(int);
  public:
    ResponseProcessor();
    void AddMeasurement(int);
    void PrintDebugOutput();
    //std::string toString();
    std::vector<unsigned long> PressedTimes();
};

ResponseProcessor::ResponseProcessor() {
 
}
std::vector<unsigned long> ResponseProcessor::PressedTimes() {
  return pressedTimes;
}

void ResponseProcessor::AddMeasurement(int value) {
  //Serial.println(value);
  if (IsPressed(value) && !alreadyPressed) {
    //Serial.println("on");
    alreadyPressed = true;
    startedPressingMillis = millis();
  } else if (!IsPressed(value) && alreadyPressed) {
    //Serial.println("off");
    alreadyPressed = false;
    unsigned long elapsed = millis() - startedPressingMillis;
    if (elapsed >= MIN_PRESSED_TIME) {
      pressedTimes.push_back(elapsed);
    }
  }
}

bool ResponseProcessor::IsPressed(int value) {
  return value < THRESHOLD_MAX && value > THRESHOLD_MIN;
}

/*std::string ResponseProcessor::toString() {
  std::ostringstream stringStream;
  stringStream << "{ size: " << pressedTimes.size() << ", pressedTimes: [";
  //for (auto elapsed : pressedTimes) {
  for (auto it = pressedTimes.begin(); it != pressedTimes.end(); ++it) {
    if (it != pressedTimes.begin()) { stringStream << ", "; }
    stringStream << *it;
  }
  stringStream << "] }";
  return stringStream.str();
}

void ResponseProcessor::printDebugOutput() {
  Serial.println(toString().c_str());
}*/

void ResponseProcessor::PrintDebugOutput() {
  Serial.print("{ size: " + String(pressedTimes.size()) + ", pressedTimes: [");
  //for (auto elapsed : pressedTimes) {
  for (auto it = pressedTimes.begin(); it != pressedTimes.end(); ++it) {
    if (it != pressedTimes.begin()) { Serial.print(", "); }
    Serial.print(*it);
  }
  Serial.println("] }");
}

#endif
