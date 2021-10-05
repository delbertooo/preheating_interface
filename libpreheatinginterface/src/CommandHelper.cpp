#include "LibPreheatingInterface.hpp"

using namespace LibPreheatingInterface;


const unsigned int LED_READ_INTERVAL = 5; // [ms]

CommandHelper::CommandHelper(Platform &platform, LibScheduling::Platform &schedulingPlatform, PreheatingRemote &remote) : platform(platform), schedulingPlatform(schedulingPlatform), remote(remote) {}

LibScheduling::RunnableScheduler CommandHelper::Scheduler() {
  return {schedulingPlatform};
}

PreheatingAnswer CommandHelper::Run(LibScheduling::RunnableSequence &sequence) {
  auto scheduler = Scheduler();

  sequence.AddToScheduler(scheduler);

  // add read tasks
  LedResponseList green, red;
  auto read = [this, &green, &red]() {
      unsigned long m = platform.Millis();
      green.AddValue(m, remote.IsGreenLedOn());
      red.AddValue(m, remote.IsRedLedOn());
  };
  scheduler.AddInterval2(LED_READ_INTERVAL, read);
  // process queue
  scheduler.ProcessQueue();
  //Serial.println("Red:"); red.PrintDebugOutput();
  //Serial.println("Green:"); green.PrintDebugOutput();
  // build result
  return {green.EnabledTimes(), red.EnabledTimes()};
}