#pragma once

#include "../PreheatingAnswer.hpp"

class IPreheatingCommandExecutor {
  public:
    virtual PreheatingAnswer Run() = 0;

};

