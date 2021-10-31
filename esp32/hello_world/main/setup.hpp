#include <stdio.h>
#include <sys/time.h>
#include <LibPreheatingInterface.hpp>
#include "driver/gpio.h"

#define HIGH 1
#define LOW 0
#define PIN_ON GPIO_NUM_12
#define PIN_OFF GPIO_NUM_14
#define GPIO_OUTPUT_PIN_SEL ((1ULL << PIN_ON) | (1ULL << PIN_OFF))

class MyRemote : public LibPreheatingInterface::PreheatingRemote
{
private:
    const int VALUE_THRESHOLD_MIN = 200; // analogRead value [0 .. 1023]
    const int VALUE_THRESHOLD_MAX = 500; // analogRead value [0 .. 1023]
    const uint8_t PIN_GREEN = 1;
    const uint8_t PIN_RED = 0;
    bool IsEnabled(int value)
    {
        return value < VALUE_THRESHOLD_MAX && value > VALUE_THRESHOLD_MIN;
    }

public:
    void PressOn() override { gpio_set_level(PIN_ON, LOW); }
    void PressOff() override { gpio_set_level(PIN_OFF, LOW); }
    void ReleaseOn() override { gpio_set_level(PIN_ON, HIGH); }
    void ReleaseOff() override { gpio_set_level(PIN_OFF, HIGH); }
    bool IsGreenLedOn() override { return false; }
    bool IsRedLedOn() override { return false; }
    void Boot()
    {
        //zero-initialize the config structure.
        gpio_config_t io_conf = {};
        //disable interrupt
        io_conf.intr_type = GPIO_INTR_DISABLE;
        //set as output mode
        io_conf.mode = GPIO_MODE_OUTPUT;
        //bit mask of the pins that you want to set,e.g.GPIO18/19
        io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
        //disable pull-down mode
        io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
        //disable pull-up mode
        io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
        //configure GPIO with the given settings
        gpio_config(&io_conf);
    }
};

class MyPlatform : public LibPreheatingInterface::Platform, public LibScheduling::Platform
{
public:
    virtual void Println(const char *text) override { printf("%s\n", text); }
    virtual unsigned long Millis() override
    {
        struct timeval tp;
        gettimeofday(&tp, NULL);
        return tp.tv_sec * 1000 + tp.tv_usec / 1000;
    }
};
