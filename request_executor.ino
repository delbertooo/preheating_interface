#include <Arduino.h>
#include <StandardCplusplus.h>
#include <deque>
#include <vector>
#include "Runnable/Runnable.hpp"

class NoOperation : public Runnable {
  private:
    NoOperation() {}
  public:
    static NoOperation& Instance() {
      static NoOperation instance;
      return instance;
    }
    void Run() override { }
};

class PressOnButton : public Runnable {
  public:
    void Run() override;
};

void PressOnButton::Run() {
  digitalWrite(11, LOW);
}

class ReleaseOnButton : public Runnable {
  public:
    void Run() override;
};
void ReleaseOnButton::Run() {
  digitalWrite(11, HIGH);
}
    
class PressOffButton : public Runnable {
  public:
    void Run() override;
};

void PressOffButton::Run() {}

class ReadStatusLed : public Runnable {
  private:
    const int PIN_RED = 0;
    const int PIN_GREEN = 1;
    ResponseProcessor &green;
    ResponseProcessor &red;
  public:
    ReadStatusLed(ResponseProcessor &green, ResponseProcessor &red);
    void Run() override;
};

ReadStatusLed::ReadStatusLed(ResponseProcessor &green, ResponseProcessor &red) : green(green), red(red) {}
void ReadStatusLed::Run() {
  red.addMeasurement(analogRead(PIN_RED));
  green.addMeasurement(analogRead(PIN_GREEN));
}

class PreheatingAnswer {
  private:
    std::vector<long> greenFlashes;
    std::vector<long> redFlashes;
    unsigned int CountProcessorFlashesWithLength(std::vector<long> &flashes, unsigned int lengthInMilliseconds);
  public:
    PreheatingAnswer(std::vector<long> greenFlashes, std::vector<long> redFlashes);
    unsigned int CountRedFlashesWithLength(unsigned long lengthInMilliseconds);
    unsigned int CountGreenFlashesWithLength(unsigned long lengthInMilliseconds);
    
};

PreheatingAnswer::PreheatingAnswer(std::vector<long> greenFlashes, std::vector<long> redFlashes) : greenFlashes(greenFlashes), redFlashes(redFlashes) {
}

unsigned int PreheatingAnswer::CountProcessorFlashesWithLength(std::vector<long> &flashes, unsigned int lengthInMilliseconds) {
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
unsigned int PreheatingAnswer::CountRedFlashesWithLength(unsigned long lengthInMilliseconds) {
  return CountProcessorFlashesWithLength(redFlashes, lengthInMilliseconds);
}

unsigned int PreheatingAnswer::CountGreenFlashesWithLength(unsigned long lengthInMilliseconds) {
  return CountProcessorFlashesWithLength(greenFlashes, lengthInMilliseconds);
}

class PreheatingCommand {
  protected:
    const unsigned int LED_READ_INTERVAL = 50; // [ms]
    PreheatingAnswer Execute(RunnableSequence &sequence);
    PreheatingAnswer Execute(RunnableScheduler &scheduler);
};


PreheatingAnswer PreheatingCommand::Execute(RunnableSequence &sequence) {
  RunnableScheduler scheduler;
  sequence.AddToScheduler(scheduler);
  return Execute(scheduler);
}

PreheatingAnswer PreheatingCommand::Execute(RunnableScheduler &scheduler) {
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

class SwitchOn : public PreheatingCommand {
  public:
    void SomeTest();
};

void SwitchOn::SomeTest() {
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

void mai2n() {
  //Delay r(100);
  PressOnButton ponb;
  PressOffButton poffb;
  //r.InitialDelay();
}
