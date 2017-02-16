#include "Runnable.hpp"
#include "actions.hpp"
#include "LedResponseParser.hpp"
#include "PreheatingAnswer.hpp"

#ifndef __PREHEATINGCOMMAND_HPP
#define __PREHEATINGCOMMAND_HPP 1

class PreheatingCommand {
  protected:
    const unsigned int LED_READ_INTERVAL = 5; // [ms]
    PressOnButton pressOnButton;
    ReleaseOnButton releaseOnButton;
    PressOffButton pressOffButton;
    ReleaseOffButton releaseOffButton;
    PreheatingAnswer Execute(RunnableSequence &sequence);
    PreheatingAnswer Execute(RunnableScheduler &scheduler);
};

PreheatingAnswer PreheatingCommand::Execute(RunnableSequence &sequence) {
  RunnableScheduler scheduler;
  sequence.AddToScheduler(scheduler);
  return Execute(scheduler);
}

PreheatingAnswer PreheatingCommand::Execute(RunnableScheduler &scheduler) {
  // add read tasks
  LedResponseParser green, red;
  ReadStatusLed readTask(green, red);
  scheduler.AddInterval(LED_READ_INTERVAL, readTask);
  // process queue
  scheduler.ProcessQueue();
  Serial.println("Red:"); red.PrintDebugOutput();
  Serial.println("Green:"); green.PrintDebugOutput();
  // build result
  return PreheatingAnswer(green.EnabledTimes(), red.EnabledTimes());
}

#endif
