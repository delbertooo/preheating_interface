#include <Arduino.h>
#include <ArduinoSTL.h>
#include <LibPreheatingInterface.hpp>


class MyRemote : public LibPreheatingInterface::PreheatingRemote {
  private:
    const int VALUE_THRESHOLD_MIN = 200; // analogRead value [0 .. 1023]
    const int VALUE_THRESHOLD_MAX = 500; // analogRead value [0 .. 1023]
    const uint8_t PIN_ON = 11;
    const uint8_t PIN_OFF = 12;
    const uint8_t PIN_GREEN = 1;
    const uint8_t PIN_RED = 0;
    bool IsEnabled(int value) {
      return value < VALUE_THRESHOLD_MAX && value > VALUE_THRESHOLD_MIN;
    }
public:
      void PressOn() override { digitalWrite(PIN_ON, LOW); }
      void PressOff() override { digitalWrite(PIN_OFF, LOW);}
      void ReleaseOn() override { digitalWrite(PIN_ON, HIGH); }
      void ReleaseOff() override { digitalWrite(PIN_OFF, HIGH); }
      bool IsGreenLedOn() override { return IsEnabled(analogRead(PIN_GREEN)); }
      bool IsRedLedOn() override { return IsEnabled(analogRead(PIN_RED)); }
      void Boot() {
        pinMode(PIN_ON, OUTPUT);
        digitalWrite(PIN_ON, HIGH);
        pinMode(PIN_OFF, OUTPUT);
        digitalWrite(PIN_OFF, HIGH);
      }
} myRemote;

class MyPlatform : public LibPreheatingInterface::Platform, public LibScheduling::Platform {
  public:
    virtual void Println(const char *text) override { Serial.println(text); }
    virtual unsigned long Millis() override { return millis(); }
} myPlatform;

LibPreheatingInterface::CommandHelper commandHelper{myPlatform, myPlatform, myRemote};

void setup() {
  Serial.begin(115200);
  Serial.println("yolo");
  myRemote.Boot();
}

void loop() {
  if (Serial.available() > 0) {
    String uart_in = Serial.readStringUntil('\n');
    if (uart_in == "on") {
      Serial.println("activate");
      LibPreheatingInterface::PowerOnCommand cmd{commandHelper};
      auto result = cmd.PowerOn();
      Serial.println("was error: " + String(result.IsError()));
    } else if (uart_in == "off") {
      Serial.println("deactivate");
      LibPreheatingInterface::PowerOffCommand cmd{commandHelper};
      auto result = cmd.PowerOff();
      Serial.println("was error: " + String(result.IsError()));
    }
  }
}
