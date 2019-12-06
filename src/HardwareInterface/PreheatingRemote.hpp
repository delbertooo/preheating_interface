#pragma once

#include "../Runnable.hpp"
#include "PreheatingAnswer.hpp"

#ifndef __HARDWAREINTERFACE_PREHEATINGREMOTE_HPP
#define __HARDWAREINTERFACE_PREHEATINGREMOTE_HPP 1


namespace HardwareInterface {

  class PreheatingRemote {
    private:
      const unsigned int LED_READ_INTERVAL = 5; // [ms]
      //Runnable &pressOnButton;
      //Runnable &releaseOnButton;
      //Runnable &pressOffButton;
      //Runnable &releaseOffButton;
      PreheatingAnswer Execute(RunnableScheduler &scheduler);
    //public:
      //PreheatingCommand::PreheatingCommand();
    public:
      PreheatingAnswer Execute(RunnableSequence &sequence);
  };

}

#endif
