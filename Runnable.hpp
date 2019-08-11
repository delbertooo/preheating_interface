#include <ArduinoSTL.h>
#include <vector>

#ifndef __HEADER_RUNNABLE_RUNNABLE
#define __HEADER_RUNNABLE_RUNNABLE 1

class Runnable {
  public:
    virtual void Run() = 0;
};

struct QueuedRunnable {
  unsigned long offset;
  Runnable* request;
  QueuedRunnable(unsigned long offset, Runnable& request) : offset(offset), request(&request) {}
};

class RunnableScheduler {
  public:
    unsigned long LastOffset();
    void AddTimeout(unsigned long offset, Runnable &request);
    void AddInterval(unsigned long interval, Runnable &request);
    void ProcessQueue();
  private:
    struct QueuedTimeout {
      unsigned int offset;
      Runnable* request;
      QueuedTimeout(unsigned long offset, Runnable& request) : offset(offset), request(&request) {}
    };
    struct QueuedInterval {
      unsigned long nextRunOffset = 0;
      unsigned long interval;
      Runnable& request;
      QueuedInterval(unsigned long interval, Runnable& request) : interval(interval), request(request) {}
    };
    std::vector<QueuedTimeout> timeoutQueue;
    std::vector<QueuedInterval> intervals;
    std::vector<QueuedTimeout>::iterator FindTimeoutPositionByOffset(unsigned long offset);
};


class RunnableSequence {
  private:
    class : public Runnable { public: inline void Run() override {} } noop;
    unsigned long actualDelay = 0;
    std::vector<QueuedRunnable> queue;
  public:
    RunnableSequence &Run(Runnable &request);
    RunnableSequence &Wait(unsigned long delayInMilliseconds);
    RunnableSequence &AddToScheduler(RunnableScheduler &scheduler);
};

#endif

