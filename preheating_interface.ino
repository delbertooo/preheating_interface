#include <StandardCplusplus.h>
#include <vector>
#include "LedResponseParser.hpp"
#include "SomeTest.hpp"

const byte RED_PIN = 2;
const byte GREEN_PIN = 3;
const byte INTERRUPT_PIN = GREEN_PIN;

void setup() {
  Serial.begin(115200);
  Serial.println("yolo");
  //pinMode(INTERRUPT_PIN, INPUT_PULLUP);
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);
  //attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), pressed, CHANGE);
}
bool pigSolution = false;
void loop() {
  SomeTest st;
  st.Test();
  Serial.println("reading shit in 3"); delay(1000);
  Serial.println("reading shit in 2"); delay(1000);
  Serial.println("reading shit in 1"); delay(1000);
  
  read_shit();
  
  delay(5L * 1000L);
}

void read_shit() {
  Serial.println("reading shit...");
  unsigned long now, start = millis();
  LedResponseParser green;
  LedResponseParser red;
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

