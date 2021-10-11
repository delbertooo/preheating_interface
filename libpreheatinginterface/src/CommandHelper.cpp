#include "LibPreheatingInterface.hpp"

using namespace LibPreheatingInterface;


const unsigned int LED_READ_INTERVAL = 5; // [ms]

CommandHelper::CommandHelper(Platform &platform, LibScheduling::Platform &schedulingPlatform, PreheatingRemote &remote) : platform(platform), schedulingPlatform(schedulingPlatform), remote(remote) {}

LibScheduling::RunnableScheduler CommandHelper::Scheduler() {
  return {schedulingPlatform};
}


struct readLeds : public LibScheduling::Runnable
{
        LedResponseList &green, &red;
        Platform &platform;
        LibPreheatingInterface::PreheatingRemote &remote;
        readLeds(LibPreheatingInterface::PreheatingRemote &remote, Platform &platform, LedResponseList &green, LedResponseList &red) : remote(remote), platform(platform), green(green), red(red) {}
        void operator()() const override
        {
          unsigned long m = platform.Millis();
          green.AddValue(m, remote.IsGreenLedOn());
          red.AddValue(m, remote.IsRedLedOn());
        }
};

PreheatingAnswer CommandHelper::Run(LibScheduling::RunnableSequence &sequence) {
  auto scheduler = Scheduler();

  sequence.AddToScheduler(scheduler);

  // add read tasks
  LedResponseList green, red;
  // scheduler.AddInterval(LED_READ_INTERVAL, [this, &green, &red]() {
  //     unsigned long m = platform.Millis();
  //     green.AddValue(m, remote.IsGreenLedOn());
  //     red.AddValue(m, remote.IsRedLedOn());
  // });
  scheduler.AddInterval(LED_READ_INTERVAL, readLeds{remote, platform, green, red});
  // process queue
  scheduler.ProcessQueue();
  //Serial.println("Red:"); red.PrintDebugOutput();
  //Serial.println("Green:"); green.PrintDebugOutput();
  // build result
  return {green.EnabledTimes(), red.EnabledTimes()};
}