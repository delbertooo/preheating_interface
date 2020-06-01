#pragma once

#include "../HardwareInterface/PreheatingRemote.hpp"

#ifndef __COMMANDS_POWERONCOMMAND_HPP
#define __COMMANDS_POWERONCOMMAND_HPP 1

namespace Commands {

class PowerOnResult {
  private:
    HardwareInterface::PreheatingAnswer result;

  public:
    PowerOnResult(HardwareInterface::PreheatingAnswer result);
    bool IsSuccessful();
    bool IsError();
    bool IsLowBattery();
    bool IsOutOfRange();
};

class PowerOnCommand {
private:
    HardwareInterface::PreheatingRemote &remote;
public:
    PowerOnCommand(HardwareInterface::PreheatingRemote &remote);
    PowerOnResult PowerOn();
    // ???? data & logic?
    //bool IsSuccessful();
    //bool IsError();
    //bool IsLowBattery();
    //bool IsOutOfRange();
};

}

#endif
