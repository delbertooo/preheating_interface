#pragma once

#ifndef __LIBSCHEDULING_HPP
#define __LIBSCHEDULING_HPP 1

#include <vector>

namespace LibScheduling {
class Runnable {
  public:
    virtual void operator() () const = 0;
};

class Platform {
  public:
    virtual void Println(const char *) {};
    virtual unsigned long Millis() = 0;
};

struct QueuedRunnable {
  unsigned long offset;
  const Runnable* request;
  QueuedRunnable(unsigned long offset, const Runnable& request) : offset(offset), request(&request) {}
};

class RunnableScheduler {
  public:
    unsigned long LastOffset();
    void AddTimeout(unsigned long offset, Runnable const *request);
    void AddInterval(unsigned long interval, Runnable const *request);
    void AddTimeout(unsigned long offset, Runnable const &request);
    void AddInterval(unsigned long interval, Runnable const &request);
    void ProcessQueue();
    RunnableScheduler(Platform &platform);
  private:
    struct QueuedTimeout {
      unsigned int offset;
      const Runnable* request;
      QueuedTimeout(unsigned long offset, const Runnable *request) : offset(offset), request(request) {}
    };
    struct QueuedInterval {
      unsigned long nextRunOffset = 0;
      unsigned long interval;
      const Runnable* request;
      QueuedInterval(unsigned long interval, const Runnable *request) : interval(interval), request(request) {}
    };
    std::vector<QueuedTimeout> timeoutQueue;
    std::vector<QueuedInterval> intervals;
    Platform &platform;
    std::vector<QueuedTimeout>::iterator FindTimeoutPositionByOffset(unsigned long offset);
};


class RunnableSequence {
  private:
    class : public Runnable { public: inline void operator() () const override {} } noop;
    unsigned long actualDelay = 0;
    std::vector<QueuedRunnable> queue;
  public:
    RunnableSequence &Run(Runnable const &request);
    RunnableSequence &Wait(unsigned long delayInMilliseconds);
    RunnableSequence &AddToScheduler(RunnableScheduler &scheduler);
};

}
#endif

