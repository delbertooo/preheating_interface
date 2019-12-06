#pragma once

#include "PreheatingCommand.hpp"
#include "../HardwareInterface/HardwareExecutor.hpp"

#ifndef __COMMANDS_POWEROFFCOMMAND_HPP
#define __COMMANDS_POWEROFFCOMMAND_HPP 1

namespace Commands {

class PowerOffCommand : public PreheatingCommand {
  private:
    HardwareInterface::HardwareExecutor &executor;
  public:
    PowerOffCommand(HardwareInterface::HardwareExecutor &executor) : executor(executor) { }
    PreheatingCommandResult Execute() override {
      HardwareInterface::PreheatingAnswer result = executor.Run();
      const char* error = NULL;
      if (result.CountRedFlashesBetween(1000, 2500) != 2) {
        if (result.CountRedFlashesBetween(50, 400) > 3) {
          error = "ERROR_OUT_OF_RANGE";
        } else {
          error = "ERROR_UNKNOWN";
        }
      }
      return {error};
    }
};

}

#endif
