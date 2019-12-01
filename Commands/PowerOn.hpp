#pragma once

#include "../PreheatingCommand.hpp"
#include "IPreheatingCommand.hpp"
#include "../HardwareExecutor/HardwareExecutor.hpp"

class PowerOnCommand : public IPreheatingCommand {
  private:
    IPreheatingCommandExecutor &executor;
  public:
    PowerOnCommand(IPreheatingCommandExecutor &executor) : executor(executor) { }
    IPreheatingCommandResult& Execute() override {
      PreheatingAnswer result = executor.Run();
      char* error = NULL;
      if (result.CountGreenFlashesWithLength(1000) != 1) {
        if (result.CountRedFlashesWithLength(200) > 4) {
          error = "ERROR_LOW_BATTERY";
        } else if (result.CountGreenFlashesWithLength(200) > 4) {
          error = "ERROR_OUT_OF_RANGE";
        } else {
          error = "ERROR_UNKNOWN";
        }
      }
      PreheatingCommandResult res(error);
      return res;
    }
};
