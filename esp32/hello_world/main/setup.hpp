#include <stdio.h>
#include <sys/time.h>
#include <LibPreheatingInterface.hpp>



class MyRemote : public LibPreheatingInterface::PreheatingRemote
{
private:
    const int VALUE_THRESHOLD_MIN = 200; // analogRead value [0 .. 1023]
    const int VALUE_THRESHOLD_MAX = 500; // analogRead value [0 .. 1023]
    const uint8_t PIN_ON = 11;
    const uint8_t PIN_OFF = 12;
    const uint8_t PIN_GREEN = 1;
    const uint8_t PIN_RED = 0;
    bool IsEnabled(int value)
    {
        return value < VALUE_THRESHOLD_MAX && value > VALUE_THRESHOLD_MIN;
    }

public:
    void PressOn() override {}
    void PressOff() override {}
    void ReleaseOn() override {}
    void ReleaseOff() override {}
    bool IsGreenLedOn() override { return false; }
    bool IsRedLedOn() override { return false; }
    void Boot()
    {
    }
};

class MyPlatform : public LibPreheatingInterface::Platform, public LibScheduling::Platform
{
public:
    virtual void Println(const char *text) override { printf(text); }
    virtual unsigned long Millis() override
    {
        struct timeval tp;
        gettimeofday(&tp, NULL);
        return tp.tv_sec * 1000 + tp.tv_usec / 1000;
    }
};
