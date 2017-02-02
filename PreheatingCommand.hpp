#include "Runnable.hpp"
#include "actions.hpp"
#include "LedResponseParser.hpp"
#include "PreheatingAnswer.hpp"

#ifndef __PREHEATINGCOMMAND_HPP
#define __PREHEATINGCOMMAND_HPP 1

class PreheatingCommand {
  protected:
    const unsigned int LED_READ_INTERVAL = 50; // [ms]
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
  unsigned long lastOffset = scheduler.LastOffset();
  for (unsigned long offset = 0; offset < lastOffset; offset += LED_READ_INTERVAL) {
    scheduler.Add(offset, readTask);
  }
  // process queue
  scheduler.ProcessQueue();
  // build result
  return PreheatingAnswer(green.EnabledTimes(), red.EnabledTimes());
}

#endif
