#include <deque>
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
    void Add(unsigned long offset, Runnable &request);
    void ProcessQueue();
  protected:
    std::deque<QueuedRunnable> queue;
  private:
    std::deque<QueuedRunnable>::iterator FindPositionByOffset(unsigned long offset);
};


class RunnableSequence {
  private:
    static class : public Runnable { public: void Run() override {} } noop;
    unsigned long actualDelay = 0;
    std::vector<QueuedRunnable> queue;
  public:
    RunnableSequence &Run(Runnable &request);
    RunnableSequence &Wait(unsigned long delayInMilliseconds);
    RunnableSequence &AddToScheduler(RunnableScheduler &scheduler);
};

#endif
