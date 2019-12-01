#pragma once

#include "PreheatingAnswer.hpp"

class PreheatingCommand {
  protected:
    const unsigned int LED_READ_INTERVAL = 5; // [ms]
    const Runnable &pressOnButton;
    const Runnable &releaseOnButton;
    const Runnable &pressOffButton;
    const Runnable &releaseOffButton;
    PreheatingAnswer Execute(RunnableSequence &sequence);
    PreheatingAnswer Execute(RunnableScheduler &scheduler);
  public:
    PreheatingCommand::PreheatingCommand();
};
