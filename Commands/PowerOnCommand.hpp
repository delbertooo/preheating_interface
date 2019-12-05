#pragma once

#include "../PreheatingCommand.hpp"
#include "IPreheatingCommand.hpp"
#include "../HardwareExecutor/HardwareExecutor.hpp"

#ifndef __POWERONCOMMAND_HPP
#define __POWERONCOMMAND_HPP 1
class PowerOnCommand : public IPreheatingCommand {
  private:
    IPreheatingCommandExecutor &executor;
  public:
    PowerOnCommand(IPreheatingCommandExecutor &executor) : executor(executor) { }
    PreheatingCommandResult Execute() override {
      PreheatingAnswer result = executor.Run();
      const char* error = NULL;
      if (result.CountGreenFlashesBetween(1000, 2500) != 2) {
        if (result.CountRedFlashesBetween(50, 400) > 3) {
          error = "ERROR_LOW_BATTERY";
        } else if (result.CountGreenFlashesBetween(50, 400) > 3) {
          error = "ERROR_OUT_OF_RANGE";
        } else {
          error = "ERROR_UNKNOWN";
        }
      }
      return {error};
    }
};

#endif
