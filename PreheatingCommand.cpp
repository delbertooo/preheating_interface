#include "Runnable.hpp"
#include "actions.hpp"
#include "LedResponseParser.hpp"
#include "PreheatingCommand.hpp"

/*PreheatingCommand::PreheatingCommand() : 
  pressOnButton(PressOnButton()),
  pressOffButton(PressOffButton()),
  releaseOnButton(ReleaseOnButton()),
  releaseOffButton(ReleaseOffButton()) { }
*/
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
