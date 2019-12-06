#pragma once


#ifndef __COMMANDS_PREHEATINGCOMMANDRESULT_HPP
#define __COMMANDS_PREHEATINGCOMMANDRESULT_HPP 1

namespace Commands {

class PreheatingCommandResult {
  private:
    const char* message;
  public:
    PreheatingCommandResult(const char* message);
    bool IsError();
    const char* ErrorMessage();
};

}
#endif
