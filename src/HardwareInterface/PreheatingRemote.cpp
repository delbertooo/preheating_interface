#include <Arduino.h>
#include "actions.hpp"
#include "LedResponseParser.hpp"
#include "PreheatingRemote.hpp"

/*PreheatingCommand::PreheatingCommand() : 
  pressOnButton(PressOnButton()),
  pressOffButton(PressOffButton()),
  releaseOnButton(ReleaseOnButton()),
  releaseOffButton(ReleaseOffButton()) { }
*/
HardwareInterface::PreheatingAnswer HardwareInterface::PreheatingRemote::Execute(RunnableSequence &sequence) {
  RunnableScheduler scheduler;
  sequence.AddToScheduler(scheduler);
  return Execute(scheduler);
}

HardwareInterface::PreheatingAnswer HardwareInterface::PreheatingRemote::Execute(RunnableScheduler &scheduler) {
  // add read tasks
  LedResponseParser green, red;
  ReadStatusLed readTask(green, red);
  scheduler.AddInterval(LED_READ_INTERVAL, readTask);
  // process queue
  scheduler.ProcessQueue();
  Serial.println("Red:"); red.PrintDebugOutput();
  Serial.println("Green:"); green.PrintDebugOutput();
  // build result
  return {green.EnabledTimes(), red.EnabledTimes()};
}
