#include "Runnable/Runnable.hpp"
#include "ResponseProcessor.hpp"

#ifndef __ACTIONS_HPP
#define __ACTIONS_HPP 1

class PressOnButton : public Runnable { public: void Run() override; };
class ReleaseOnButton : public Runnable { public: void Run() override; };
class PressOffButton : public Runnable { public: void Run() override; };
class ReleaseOffButton : public Runnable { public: void Run() override; };

class ReadStatusLed : public Runnable {
  private:
    const int PIN_RED = 0;
    const int PIN_GREEN = 1;
    ResponseProcessor &green;
    ResponseProcessor &red;
  public:
    ReadStatusLed(ResponseProcessor &green, ResponseProcessor &red);
    void Run() override;
};

#include <Arduino.h>

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
  red.AddMeasurement(analogRead(PIN_RED));
  green.AddMeasurement(analogRead(PIN_GREEN));
}

#endif
