#include "LibScheduling.hpp"


using namespace LibScheduling;

RunnableSequence &RunnableSequence::Run(Runnable const &request) {
  queue.push_back({actualDelay, request});
  return *this;
}

RunnableSequence &RunnableSequence::Wait(unsigned long delayInMilliseconds) {
  actualDelay += delayInMilliseconds;
  return *this;
}

RunnableSequence &RunnableSequence::AddToScheduler(RunnableScheduler &scheduler) {
  for (QueuedRunnable &element : queue) {
    scheduler.AddTimeout(element.offset, element.request);
  }
  // add noop to the end if required
  unsigned long lastOffset = queue.empty() ? 0 : queue.back().offset;
  if (actualDelay > lastOffset) {
    scheduler.AddTimeout(actualDelay, &noop);
  }
  return *this;
}

