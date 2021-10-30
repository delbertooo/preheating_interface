#pragma once

#ifndef __LIBPREHEATINGINTERFACE_HPP
#define __LIBPREHEATINGINTERFACE_HPP 1

#include <vector>
#include <LibScheduling.hpp>


namespace LibPreheatingInterface {

  class PreheatingRemote;
  class CommandHelper;
  
  class PreheatingAnswer {
    private:
      std::vector<unsigned long> greenFlashes;
      std::vector<unsigned long> redFlashes;
      unsigned int CountProcessorFlashesWithLength(std::vector<unsigned long> &flashes, unsigned long lengthInMilliseconds);
      unsigned int CountProcessorFlashesWithLengthBetween(std::vector<unsigned long> &flashes, unsigned long minTime, unsigned long maxTime);
    public:
      PreheatingAnswer(std::vector<unsigned long> greenFlashes, std::vector<unsigned long> redFlashes);
      unsigned int CountRedFlashesWithLength(unsigned long lengthInMilliseconds);
      unsigned int CountGreenFlashesWithLength(unsigned long lengthInMilliseconds);
      unsigned int CountRedFlashesBetween(unsigned long minTime, unsigned long maxTime);
      unsigned int CountGreenFlashesBetween(unsigned long minTime, unsigned long maxTime);
  };

  class AbstractCommand {
    protected:
      PreheatingRemote &remote;
      CommandHelper &helper;
    public:
      AbstractCommand(CommandHelper&);
  };

class PowerOnResult {
  private:
    PreheatingAnswer result;

  public:
    PowerOnResult(PreheatingAnswer result);
    bool IsSuccessful();
    bool IsError();
    bool IsLowBattery();
    bool IsOutOfRange();
};

class PowerOffResult {
  private:
    PreheatingAnswer result;

  public:
    PowerOffResult(PreheatingAnswer result);
    bool IsSuccessful();
    bool IsError();
    bool IsOutOfRange();
};


class PowerOnCommand : public AbstractCommand {
public:
    PowerOnCommand(CommandHelper&);
    PowerOnResult PowerOn();
    // ???? data & logic?
    //bool IsSuccessful();
    //bool IsError();
    //bool IsLowBattery();
    //bool IsOutOfRange();
};

class PowerOffCommand : public AbstractCommand {
public:
    PowerOffCommand(CommandHelper&);
    //PowerOffCommand(CommandHelper &helper) : AbstractCommand(helper) {}
    PowerOffResult PowerOff();
};


  class PreheatingRemote {
    public:
      virtual void PressOn() = 0;
      virtual void PressOff() = 0;
      virtual void ReleaseOn() = 0;
      virtual void ReleaseOff() = 0;
      virtual bool IsGreenLedOn() = 0;
      virtual bool IsRedLedOn() = 0;
  };


  class LedResponseList {
    private:
      const int MIN_ENABLED_TIME = 10; // [ms]
      bool alreadyEnabled;
      std::vector<unsigned long> enabledTimes;
      unsigned long enabledStartMillis;
    public:
      LedResponseList();
      void AddValue(unsigned long, bool);
      std::vector<unsigned long> EnabledTimes();
  };

  class Platform {
    public:
      virtual unsigned long Millis() = 0;
  };

  class CommandHelper {
    friend AbstractCommand;
    private:
      Platform &platform;
      LibScheduling::Platform &schedulingPlatform;
      PreheatingRemote &remote;
      LibScheduling::RunnableScheduler Scheduler();
    public:
      CommandHelper(Platform &platform, LibScheduling::Platform &schedulingPlatform, PreheatingRemote &remote);
      PreheatingAnswer Run(LibScheduling::RunnableSequence &sequence);
  };

}

#endif
