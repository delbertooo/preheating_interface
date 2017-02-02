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
