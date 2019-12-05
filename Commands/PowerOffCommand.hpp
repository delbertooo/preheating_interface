#pragma once

#include "../PreheatingCommand.hpp"
#include "IPreheatingCommand.hpp"
#include "../HardwareExecutor/HardwareExecutor.hpp"

#ifndef __POWEROFFCOMMAND_HPP
#define __POWEROFFCOMMAND_HPP 1
class PowerOffCommand : public IPreheatingCommand {
  private:
    IPreheatingCommandExecutor &executor;
  public:
    PowerOffCommand(IPreheatingCommandExecutor &executor) : executor(executor) { }
    PreheatingCommandResult Execute() override {
      PreheatingAnswer result = executor.Run();
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

#endif
