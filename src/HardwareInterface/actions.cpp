
#include <Arduino.h>
#include "actions.hpp"

void HardwareInterface::PressOnButton::Run() {
  digitalWrite(11, LOW);
}

void HardwareInterface::ReleaseOnButton::Run() {
  digitalWrite(11, HIGH);
}

void HardwareInterface::PressOffButton::Run() {
  digitalWrite(12, LOW);
}

void HardwareInterface::ReleaseOffButton::Run() {
  digitalWrite(12, HIGH);
}

HardwareInterface::ReadStatusLed::ReadStatusLed(HardwareInterface::LedResponseParser &green, HardwareInterface::LedResponseParser &red) : green(green), red(red) {}

void HardwareInterface::ReadStatusLed::Run() {
  red.AddMeasurement(analogRead(PIN_RED));
  green.AddMeasurement(analogRead(PIN_GREEN));
}
