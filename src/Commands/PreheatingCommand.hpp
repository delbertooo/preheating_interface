#pragma once

#include "PreheatingCommandResult.hpp"

#ifndef __COMMANDS_PREHEATINGCOMMAND_HPP
#define __COMMANDS_PREHEATINGCOMMAND_HPP 1

namespace Commands {

class PreheatingCommand {
  public:
    virtual PreheatingCommandResult Execute() = 0;
};

}

#endif
