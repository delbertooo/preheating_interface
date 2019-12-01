#pragma once

#include "../PreheatingAnswer.hpp"

#ifndef __HS3_HPP
#define __HS3_HPP 1
class IPreheatingCommandExecutor {
  public:
    virtual PreheatingAnswer Run() = 0;

};

#endif

