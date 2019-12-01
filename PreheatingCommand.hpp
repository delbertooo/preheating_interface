#pragma once


#ifndef __PREHEATING_COMMAND_HPP
#define __PREHEATING_COMMAND_HPP 1

#include "PreheatingAnswer.hpp"

class PreheatingCommand {
  protected:
    const unsigned int LED_READ_INTERVAL = 5; // [ms]
    //Runnable &pressOnButton;
    //Runnable &releaseOnButton;
    //Runnable &pressOffButton;
    //Runnable &releaseOffButton;
    PreheatingAnswer Execute(RunnableSequence &sequence);
    PreheatingAnswer Execute(RunnableScheduler &scheduler);
  //public:
    //PreheatingCommand::PreheatingCommand();
};

#endif
