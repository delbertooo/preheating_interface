#include "Runnable/Runnable.hpp"
#include "actions.hpp"
#include "ResponseProcessor.hpp"

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
  ResponseProcessor green, red;
  ReadStatusLed readTask(green, red);
  unsigned long lastOffset = scheduler.LastOffset();
  for (unsigned long offset = 0; offset < lastOffset; offset += LED_READ_INTERVAL) {
    scheduler.Add(offset, readTask);
  }
  // process queue
  scheduler.ProcessQueue();
  // build result
  return PreheatingAnswer(green.getPressedTimes(), red.getPressedTimes());
}

