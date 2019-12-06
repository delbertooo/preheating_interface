#pragma once

#include "PreheatingAnswer.hpp"

#ifndef __HARDWAREEXECUTOR_HPP
#define __HARDWAREEXECUTOR_HPP 1

namespace HardwareInterface {

  class HardwareExecutor {
    public:
      virtual PreheatingAnswer Run() = 0;

  };
}

#endif

