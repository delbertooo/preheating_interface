#pragma once

#include "../HardwareInterface/PreheatingRemote.hpp"

#ifndef __COMMANDS_POWEROFFCOMMAND_HPP
#define __COMMANDS_POWEROFFCOMMAND_HPP 1

namespace Commands {

class PowerOffResult {
  private:
    HardwareInterface::PreheatingAnswer result;

  public:
    PowerOffResult(HardwareInterface::PreheatingAnswer result);
    bool IsSuccessful();
    bool IsError();
    bool IsOutOfRange();
};

class PowerOffCommand {
private:
    HardwareInterface::PreheatingRemote &remote;
public:
    PowerOffCommand(HardwareInterface::PreheatingRemote &remote);
    PowerOffResult PowerOff();
};

}

#endif
