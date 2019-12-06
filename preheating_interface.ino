#include <ArduinoSTL.h>
#include <vector>
#include "HardwareInterface/LedResponseParser.hpp"
#include "Commands/PowerOnCommand.hpp"
#include "Commands/PowerOnCommandHardwareExecutor.hpp"

const byte RED_PIN = 2;
const byte GREEN_PIN = 3;
const byte INTERRUPT_PIN = GREEN_PIN;

void setup() {
  Serial.begin(115200);
  Serial.println("yolo");
  //pinMode(INTERRUPT_PIN, INPUT_PULLUP);
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
  //attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), pressed, CHANGE);
}
bool pigSolution = false;
void loop() {
  HardwareInterface::PreheatingRemote remote;
  if (Serial.available() > 0) {
    String uart_in = Serial.readStringUntil('\n');
    if (uart_in == "on") {
      Serial.println("activate");
      //SwitchOnCommand cmd;
      Commands::PowerOnCommandHardwareExecutor executor{remote};
      Commands::PowerOnCommand cmd{executor};
      Commands::PreheatingCommandResult result = cmd.Execute();
      Serial.println("was error: " + String(result.IsError()));
    } else if (uart_in == "off") {
      Serial.println("deactivate");
      //SwitchOffCommand cmd;
      Serial.println("is not implemented :(");
    }
  }
}

void read_shit() {
  Serial.println("reading shit...");
  unsigned long now, start = millis();
  HardwareInterface::LedResponseParser green;
  HardwareInterface::LedResponseParser red;
  //RequestExecutor re(12000, green, red);
  //re.AddRequestSequence(...)
  //re.ProcessQueue();
  
  
  digitalWrite(11, LOW);
  do {
    now = millis();
    if (now - start > 1000) { digitalWrite(11, HIGH); }
    red.AddMeasurement(analogRead(0));
    green.AddMeasurement(analogRead(1));
    //Serial.print(analogRead(0));
    //Serial.print("\t");
    //Serial.println(analogRead(1));
  } while (now - start < 4000);
  Serial.println("green: ");
  green.PrintDebugOutput();
  Serial.println("red: ");
  red.PrintDebugOutput();
}

void pressed() {
  Serial.println("interrupt!");
  pigSolution = !pigSolution;
  //Serial.print("green:");
  //Serial.println(digitalRead(INTERRUPT_PIN) == HIGH ? " irgendein wort" : " -");
}
