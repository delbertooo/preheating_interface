#include <Arduino.h>
#include <StandardCplusplus.h>
#include <deque>
#include <vector>


class Request {
  public:
    virtual void Execute() = 0;
};


struct QueuedRequest {
  unsigned long offset;
  Request* request;
  QueuedRequest(unsigned long offset, Request& request) : offset(offset), request(&request) {}
};

class RequestExecutor {
  public:
    unsigned long LastOffset() {
      return queue.empty() ? 0 : queue.back().offset;
    }
    void AddRequest(unsigned long offset, Request &request) {
      queue.insert(FindPositionByOffset(offset), {offset, request});
    }

    void ProcessQueue() {
      std::deque<QueuedRequest>::iterator next_queued_request = queue.begin();
      unsigned long start_millis = millis();
      while (next_queued_request != queue.end()) {
        unsigned long now = millis();
        unsigned long current_offset = now - start_millis;
        if (current_offset >= next_queued_request->offset) {
          next_queued_request->request->Execute();
          next_queued_request++;
        }
      }
    }
  protected:
    std::deque<QueuedRequest> queue;
  private:
    std::deque<QueuedRequest>::iterator FindPositionByOffset(unsigned long offset) {
      // TODO: NYI
      return queue.begin();
    }
};


class NoOperation : public Request {
  public:
    static NoOperation& Instance() {
      static NoOperation instance;
      return instance;
    }
    void Execute() { }
};

class RequestSequenceBuilder {
  private:
    unsigned long actualDelay = 0;
    std::vector<QueuedRequest> queue;
  public:
    RequestSequenceBuilder &Run(Request &request) {
      queue.push_back({actualDelay, request});
      return *this;
    }

    RequestSequenceBuilder &Wait(unsigned long delayInMilliseconds) {
      actualDelay += delayInMilliseconds;
      return *this;
    }

    RequestSequenceBuilder &AddToExecutor(RequestExecutor &executor) {
      for (QueuedRequest &element : queue) {
        executor.AddRequest(element.offset, *element.request);
      }
      // add noop to the end if required
      unsigned long lastOffset = queue.empty() ? 0 : queue.back().offset;
      if (actualDelay > lastOffset) {
        executor.AddRequest(actualDelay, NoOperation::Instance());
      }
      return *this;
    }

};

class PressOnButton : public Request {
  public:
    void Execute() {
      digitalWrite(11, LOW);
    }
};

class ReleaseOnButton : public Request {
  public:
    void Execute() {
      digitalWrite(11, HIGH);
    }
};

class PressOffButton : public Request {
  public:
    void Execute() {}
};

class ReadStatusLed : public Request {
  private:
    const int PIN_RED = 0;
    const int PIN_GREEN = 1;
    ResponseProcessor &green;
    ResponseProcessor &red;
  public:
    ReadStatusLed(ResponseProcessor &green, ResponseProcessor &red) : green(green), red(red) {}
    void Execute() {
      red.addMeasurement(analogRead(PIN_RED));
      green.addMeasurement(analogRead(PIN_GREEN));
    }
};

class PreheatingAnswer {
  private:
    std::vector<long> greenFlashes;
    std::vector<long> redFlashes;
    
    unsigned int CountProcessorFlashesWithLength(std::vector<long> &flashes, unsigned int lengthInMilliseconds) {
      unsigned int thresh = lengthInMilliseconds * .9;
      unsigned int minTime = lengthInMilliseconds - thresh;
      unsigned int maxTime = lengthInMilliseconds + thresh;
      unsigned int num = 0;
      for (long &t : flashes) {
        if (t >= minTime && t <= maxTime) {
          ++num;
        }
      }
      return num;
    }
  public:
    PreheatingAnswer(std::vector<long> greenFlashes, std::vector<long> redFlashes) : greenFlashes(greenFlashes), redFlashes(redFlashes) {}

    unsigned int CountRedFlashesWithLength(unsigned long lengthInMilliseconds) {
      return CountProcessorFlashesWithLength(redFlashes, lengthInMilliseconds);
    }
    
    unsigned int CountGreenFlashesWithLength(unsigned long lengthInMilliseconds) {
      return CountProcessorFlashesWithLength(greenFlashes, lengthInMilliseconds);
    }
    
};

class PreheatingCommand {
  protected:
    const unsigned int LED_READ_INTERVAL = 50; // [ms]
    
    PreheatingAnswer Execute(RequestSequenceBuilder &builder) {
      RequestExecutor re;
      builder.AddToExecutor(re);
      return Execute(re);
    }
    
    PreheatingAnswer Execute(RequestExecutor &re) {
      // add read tasks
      ResponseProcessor green, red;
      ReadStatusLed readTask(green, red);
      unsigned long lastOffset = re.LastOffset();
      for (unsigned int offset = 0; offset < lastOffset; offset += LED_READ_INTERVAL) {
        re.AddRequest((unsigned long) offset, readTask);
      }
      // process queue
      re.ProcessQueue();
      // build result
      return PreheatingAnswer(green.getPressedTimes(), red.getPressedTimes());
      //return *this;
    }
};

class SwitchOn : public PreheatingCommand {
  public:

    void SomeTest() {
      const int toMinutes = 10;
      PressOnButton pressOnButton;

      PreheatingAnswer a_step3 = Execute(RequestSequenceBuilder().Run(pressOnButton).Wait(3000));

      RequestExecutor dry_step3;
      dry_step3.AddRequest(0, pressOnButton);
      dry_step3.AddRequest(3000, NoOperation::Instance());
      
      PreheatingAnswer a_dry_step3 = Execute(dry_step3);

      if (a_step3.CountRedFlashesWithLength(500) != 1) {
        // "expected one flash of the red led";
        return;
      }

      RequestSequenceBuilder sendPowerOn(RequestSequenceBuilder().Run(pressOnButton).Wait(3000));
      if (Execute(sendPowerOn).CountRedFlashesWithLength(500) != 1) {
        // "expected one flash of the red led";
        return;
      }
      int flashes = a_step3.CountRedFlashesWithLength(500);

      for (int i = toMinutes; i < flashes; ++i) {

      }
    }
};

void mai2n() {
  //Delay r(100);
  PressOnButton ponb;
  PressOffButton poffb;
  //r.InitialDelay();
}
