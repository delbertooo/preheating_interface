#include <Arduino.h>
#include <StandardCplusplus.h>
#include <deque>
#include "Runnable.hpp"

std::deque<QueuedRunnable>::iterator RunnableScheduler::FindPositionByOffset(unsigned long offset) {
  // TODO: NYI
  return queue.begin();
}

unsigned long RunnableScheduler::LastOffset() {
  return queue.empty() ? 0 : queue.back().offset;
}

void RunnableScheduler::Add(unsigned long offset, Runnable &request) {
  queue.insert(FindPositionByOffset(offset), {offset, request});
}

void RunnableScheduler::ProcessQueue() {
  std::deque<QueuedRunnable>::iterator next_queued_request = queue.begin();
  unsigned long start_millis = millis();
  while (next_queued_request != queue.end()) {
    unsigned long now = millis();
    unsigned long current_offset = now - start_millis;
    if (current_offset >= next_queued_request->offset) {
      next_queued_request->request->Run();
      next_queued_request++;
    }
  }
}
