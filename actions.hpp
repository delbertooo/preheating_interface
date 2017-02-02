#include "Runnable/Runnable.hpp"

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
    ResponseProcessor &green;
    ResponseProcessor &red;
  public:
    ReadStatusLed(ResponseProcessor &green, ResponseProcessor &red);
    void Run() override;
};

#endif
