#include <Arduino.h>
#include "Runnable/Runnable.hpp"
#include "ResponseProcessor.hpp"
#include "actions.hpp"

void PressOnButton::Run() {
  digitalWrite(11, LOW);
}

void ReleaseOnButton::Run() {
  digitalWrite(11, HIGH);
}

void PressOffButton::Run() {
  digitalWrite(10, LOW);
}

void ReleaseOffButton::Run() {
  digitalWrite(10, HIGH);
}

ReadStatusLed::ReadStatusLed(ResponseProcessor &green, ResponseProcessor &red) : green(green), red(red) {}

void ReadStatusLed::Run() {
  red.addMeasurement(analogRead(PIN_RED));
  green.addMeasurement(analogRead(PIN_GREEN));
}

