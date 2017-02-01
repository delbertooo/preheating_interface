#include <Arduino.h>
#include <StandardCplusplus.h>
#include <deque>
#include <vector>


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
    unsigned long LastOffset() {
      return queue.empty() ? 0 : queue.back().offset;
    }
    void Add(unsigned long offset, Runnable &request) {
      queue.insert(FindPositionByOffset(offset), {offset, request});
    }

    void ProcessQueue() {
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
  protected:
    std::deque<QueuedRunnable> queue;
  private:
    std::deque<QueuedRunnable>::iterator FindPositionByOffset(unsigned long offset) {
      // TODO: NYI
      return queue.begin();
    }
};


class NoOperation : public Runnable {
  private:
    NoOperation() {}
  public:
    static NoOperation& Instance() {
      static NoOperation instance;
      return instance;
    }
    void Run() { }
};

class RunnableSequence {
  private:
    unsigned long actualDelay = 0;
    std::vector<QueuedRunnable> queue;
  public:
    RunnableSequence &Run(Runnable &request) {
      queue.push_back({actualDelay, request});
      return *this;
    }

    RunnableSequence &Wait(unsigned long delayInMilliseconds) {
      actualDelay += delayInMilliseconds;
      return *this;
    }

    RunnableSequence &AddToScheduler(RunnableScheduler &scheduler) {
      for (QueuedRunnable &element : queue) {
        scheduler.Add(element.offset, *element.request);
      }
      // add noop to the end if required
      unsigned long lastOffset = queue.empty() ? 0 : queue.back().offset;
      if (actualDelay > lastOffset) {
        scheduler.Add(actualDelay, NoOperation::Instance());
      }
      return *this;
    }

};

class PressOnButton : public Runnable {
  public:
    void Run() {
      digitalWrite(11, LOW);
    }
};

class ReleaseOnButton : public Runnable {
  public:
    void Run() {
      digitalWrite(11, HIGH);
    }
};

class PressOffButton : public Runnable {
  public:
    void Run() {}
};

class ReadStatusLed : public Runnable {
  private:
    const int PIN_RED = 0;
    const int PIN_GREEN = 1;
    ResponseProcessor &green;
    ResponseProcessor &red;
  public:
    ReadStatusLed(ResponseProcessor &green, ResponseProcessor &red) : green(green), red(red) {}
    void Run() {
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
    
    PreheatingAnswer Execute(RunnableSequence &sequence) {
      RunnableScheduler scheduler;
      sequence.AddToScheduler(scheduler);
      return Execute(scheduler);
    }
    
    PreheatingAnswer Execute(RunnableScheduler &scheduler) {
      // add read tasks
      ResponseProcessor green, red;
      ReadStatusLed readTask(green, red);
      unsigned long lastOffset = scheduler.LastOffset();
      for (unsigned int offset = 0; offset < lastOffset; offset += LED_READ_INTERVAL) {
        scheduler.Add((unsigned long) offset, readTask);
      }
      // process queue
      scheduler.ProcessQueue();
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

      PreheatingAnswer a_step3 = Execute(RunnableSequence().Run(pressOnButton).Wait(3000));

      RunnableScheduler dry_step3;
      dry_step3.Add(0, pressOnButton);
      dry_step3.Add(3000, NoOperation::Instance());
      
      PreheatingAnswer a_dry_step3 = Execute(dry_step3);

      if (a_step3.CountRedFlashesWithLength(500) != 1) {
        // "expected one flash of the red led";
        return;
      }

      RunnableSequence sendPowerOn(RunnableSequence().Run(pressOnButton).Wait(3000));
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
