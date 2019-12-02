#pragma once


#ifndef __HS5_HPP
#define __HS5_HPP 1


class PreheatingCommandResult {
  private:
    const char* message;
  public:
    PreheatingCommandResult(const char* message);
    bool IsError();
    const char* ErrorMessage();
};

#endif
