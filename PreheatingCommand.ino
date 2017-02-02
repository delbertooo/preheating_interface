#include "Runnable/Runnable.hpp"

class PressOnButton : public Runnable { public: void Run() override; };
class ReleaseOnButton : public Runnable { public: void Run() override; };
class PressOffButton : public Runnable { public: void Run() override; };

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

class PreheatingCommand {
  protected:
    const unsigned int LED_READ_INTERVAL = 50; // [ms]
    PreheatingAnswer Execute(RunnableSequence &sequence);
    PreheatingAnswer Execute(RunnableScheduler &scheduler);
};

void PressOnButton::Run() {
  digitalWrite(11, LOW);
}

void ReleaseOnButton::Run() {
  digitalWrite(11, HIGH);
}

void PressOffButton::Run() {}

ReadStatusLed::ReadStatusLed(ResponseProcessor &green, ResponseProcessor &red) : green(green), red(red) {}

void ReadStatusLed::Run() {
  red.addMeasurement(analogRead(PIN_RED));
  green.addMeasurement(analogRead(PIN_GREEN));
}

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

