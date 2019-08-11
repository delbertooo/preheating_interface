#include <Arduino.h>
#include <ArduinoSTL.h>
#include <vector>
#include "Runnable.hpp"

std::vector<RunnableScheduler::QueuedTimeout>::iterator RunnableScheduler::FindTimeoutPositionByOffset(unsigned long offset) {
  for (std::vector<RunnableScheduler::QueuedTimeout>::iterator queued_runnable = timeoutQueue.begin(); queued_runnable != timeoutQueue.end(); queued_runnable++) {
    if (queued_runnable->offset > offset) {
      return queued_runnable;
    }
  }
  return timeoutQueue.end();
}


unsigned long RunnableScheduler::LastOffset() {
  return timeoutQueue.empty() ? 0 : timeoutQueue.back().offset;
}

void RunnableScheduler::AddTimeout(unsigned long offset, Runnable &request) {
  timeoutQueue.insert(FindTimeoutPositionByOffset(offset), {offset, request});
}


void RunnableScheduler::AddInterval(unsigned long interval, Runnable &request) {
  intervals.push_back({interval, request});
}

void RunnableScheduler::ProcessQueue() {
  const unsigned long SLOW_WARNING_THRESH = 5; // [ms]
  std::vector<QueuedTimeout>::iterator next_queued_request = timeoutQueue.begin();
  unsigned long start_millis = millis();
  while (next_queued_request != timeoutQueue.end()) {
    unsigned long now = millis();
    unsigned long current_offset = now - start_millis;
    for (QueuedInterval interval : intervals) {
      if (current_offset >= interval.nextRunOffset) {
        interval.request.Run();
        interval.nextRunOffset = current_offset + interval.interval;
      }
    }
    if (current_offset >= next_queued_request->offset) {
      if (current_offset - next_queued_request->offset > SLOW_WARNING_THRESH) {
        Serial.println("Something was pretty slow, so this request comes late.");
      }
      next_queued_request->request->Run();
      next_queued_request++;
    }
  }
}

