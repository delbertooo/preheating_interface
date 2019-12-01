
#include "actions.hpp"

void PressOnButton::Run() {
  digitalWrite(11, LOW);
}

void ReleaseOnButton::Run() {
  digitalWrite(11, HIGH);
}

void PressOffButton::Run() {
  digitalWrite(12, LOW);
}

void ReleaseOffButton::Run() {
  digitalWrite(12, HIGH);
}

ReadStatusLed::ReadStatusLed(LedResponseParser &green, LedResponseParser &red) : green(green), red(red) {}

void ReadStatusLed::Run() {
  red.AddMeasurement(analogRead(PIN_RED));
  green.AddMeasurement(analogRead(PIN_GREEN));
}
