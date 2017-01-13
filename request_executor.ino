#include <Arduino.h>
#include <StandardCplusplus.h>
#include <deque>
#include <vector>


class Request {
  public:
    virtual unsigned long InitialDelay() {
      return 0L;
    }
    virtual void Execute() = 0;
};

struct QueuedRequest {
  unsigned long offset;
  Request* request;
  QueuedRequest(unsigned long offset, Request* request) : offset(offset), request(request) {}
};

class RequestExecutor {
  public:
    void AddRequestSequence(std::vector<Request*> requests) {
      unsigned long offset = 0;
      for (Request* request : requests) {
        offset += request->InitialDelay();
        QueuedRequest queuedRequest(offset, request);
        queue.insert(FindPositionByOffset(offset), queuedRequest);
      }
    }
    void ProcessQueue() {
      std::deque<QueuedRequest>::iterator next_queued_request = queue.begin();
      long start_millis = millis();
      while (next_queued_request != queue.end()) {
        long now = millis();
        long current_offset = now - start_millis;
        if (current_offset >= next_queued_request->offset) {
          next_queued_request->request->Execute();
          next_queued_request++;
        }
      }
    }
  private:
    std::deque<QueuedRequest> queue;
    std::deque<QueuedRequest>::iterator FindPositionByOffset(unsigned long offset) {
      // TODO: NYI
      return queue.begin();
    }
};

class Delay : public Request {
  private:
    unsigned long initialDelay;
  public:
    Delay(unsigned long initialDelay) : initialDelay(initialDelay) { }
    unsigned long InitialDelay() {
      return initialDelay;
    }
    void Execute() {
      
    }
};

class PressOnButton : public Request {
  public:
    void Execute() {digitalWrite(11, LOW);}
};

class ReleaseOnButton : public Request {
  public:
    void Execute() {digitalWrite(11, HIGH);}
};

class PressOffButton : public Request {
  public:
    void Execute() {}
};

class ReadStatusLed : public Request {
  public:
    
    void Execute() {}
};

void mai2n() {
  Delay r(100);
  PressOnButton ponb;
  PressOffButton poffb;
  r.InitialDelay();
}
