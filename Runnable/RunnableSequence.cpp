#include <StandardCplusplus.h>
#include "runnable.hpp"

RunnableSequence &RunnableSequence::Run(Runnable &request) {
  queue.push_back({actualDelay, request});
  return *this;
}

RunnableSequence &RunnableSequence::Wait(unsigned long delayInMilliseconds) {
  actualDelay += delayInMilliseconds;
  return *this;
}

RunnableSequence &RunnableSequence::AddToScheduler(RunnableScheduler &scheduler) {
  for (QueuedRunnable &element : queue) {
    scheduler.Add(element.offset, *element.request);
  }
  // add noop to the end if required
  unsigned long lastOffset = queue.empty() ? 0 : queue.back().offset;
  if (actualDelay > lastOffset) {
    scheduler.Add(actualDelay, noop);
  }
  return *this;
}

