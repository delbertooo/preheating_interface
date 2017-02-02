#include <Arduino.h>
#include <StandardCplusplus.h>
#include <vector>
//#include <sstream>

#include "ResponseProcessor.hpp"


ResponseProcessor::ResponseProcessor() {
 
}
std::vector<long> ResponseProcessor::getPressedTimes() {
  return pressedTimes;
}

void ResponseProcessor::addMeasurement(int value) {
  //Serial.println(value);
  if (isPressed(value) && !alreadyPressed) {
    //Serial.println("on");
    alreadyPressed = true;
    l = millis();
  } else if (!isPressed(value) && alreadyPressed) {
    //Serial.println("off");
    alreadyPressed = false;
    unsigned long elapsed = millis() - l;
    if (elapsed >= MIN_PRESSED_TIME) {
      pressedTimes.push_back(elapsed);
    }
  }
}

bool ResponseProcessor::isPressed(int value) {
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

void ResponseProcessor::printDebugOutput() {
  Serial.print("{ size: " + String(pressedTimes.size()) + ", pressedTimes: [");
  //for (auto elapsed : pressedTimes) {
  for (auto it = pressedTimes.begin(); it != pressedTimes.end(); ++it) {
    if (it != pressedTimes.begin()) { Serial.print(", "); }
    Serial.print(*it);
  }
  Serial.println("] }");
}


