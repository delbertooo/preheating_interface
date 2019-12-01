#include "Runnable.hpp"
#include "LedResponseParser.hpp"

#ifndef __ACTIONS_HPP
#define __ACTIONS_HPP 1

class PressOnButton : public Runnable { public: void Run() override; };
class ReleaseOnButton : public Runnable { public: void Run() override; };
class PressOffButton : public Runnable { public: void Run() override; };
class ReleaseOffButton : public Runnable { public: void Run() override; };

class ReadStatusLed : public Runnable {
  private:
    const int PIN_RED = 0;
    const int PIN_GREEN = 1;
    LedResponseParser &green;
    LedResponseParser &red;
  public:
    ReadStatusLed(LedResponseParser &green, LedResponseParser &red);
    void Run() override;
};

#endif
