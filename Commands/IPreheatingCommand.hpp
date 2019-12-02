#pragma once

#include "PreheatingCommandResult.hpp"

#ifndef __HS1_HPP
#define __HS1_HPP 1

class IPreheatingCommand {
  public:
    virtual PreheatingCommandResult Execute() = 0;
};

#endif
