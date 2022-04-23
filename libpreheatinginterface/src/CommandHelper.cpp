#include "LibPreheatingInterface.hpp"
#include <cstdio>
using namespace LibPreheatingInterface;


const unsigned int LED_READ_INTERVAL = 5; // [ms]

CommandHelper::CommandHelper(Platform &platform, LibScheduling::Platform &schedulingPlatform, PreheatingRemote &remote) : platform(platform), schedulingPlatform(schedulingPlatform), remote(remote) {}

LibScheduling::RunnableScheduler CommandHelper::Scheduler() {
  return {schedulingPlatform};
}


struct readLeds : public LibScheduling::Runnable
{
        LibPreheatingInterface::PreheatingRemote &remote;
        Platform &platform;
        LedResponseList &green, &red;
        readLeds(LibPreheatingInterface::PreheatingRemote &remote, Platform &platform, LedResponseList &green, LedResponseList &red) : remote(remote), platform(platform), green(green), red(red) {}
        void operator()() const override
        {
          unsigned long m = platform.Millis();
          green.AddValue(m, remote.IsGreenLedOn());
          red.AddValue(m, remote.IsRedLedOn());
        }
};

void printList(LedResponseList &list) {
  printf("[ ");
  bool first = true;
  for (auto x : list.EnabledTimes()) {
    if (first) first = false; else printf(",  ");
    printf("%lu ms", x);

  }
  printf(" ]\n");
}

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
  printf("\nLED response:\ngreen ");
  printList(green);
  printf("red   ");
  printList(red);
  // build result
  return {green.EnabledTimes(), red.EnabledTimes()};
}
