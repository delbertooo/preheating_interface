#include <stdio.h>
#include <sys/time.h>
#include <LibPreheatingInterface.hpp>
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "soc/adc_channel.h"

#define HIGH 1
#define LOW 0
#define PIN_ON GPIO_NUM_12
#define PIN_OFF GPIO_NUM_14
#define GPIO_OUTPUT_PIN_SEL ((1ULL << PIN_ON) | (1ULL << PIN_OFF))

#define DEFAULT_VREF 1100 //Use adc2_vref_to_gpio() to obtain a better estimate
#define NO_OF_SAMPLES 64  //Multisampling

#define CHANNEL_RED ADC2_GPIO27_CHANNEL
#define CHANNEL_GREEN ADC2_GPIO26_CHANNEL
#define ATTEN ADC_ATTEN_DB_0
#define WIDTH ADC_WIDTH_BIT_12

int readChannel(adc2_channel_t channel)
{
    uint32_t adc_reading = 0;
    for (int i = 0; i < NO_OF_SAMPLES; i++)
    {
        int raw;
        adc2_get_raw((adc2_channel_t)channel, WIDTH, &raw);
        adc_reading += raw;
    }
    adc_reading /= NO_OF_SAMPLES;
    return adc_reading;
}

class MyRemote : public LibPreheatingInterface::PreheatingRemote
{
private:
    const int VALUE_THRESHOLD_MIN = 800;  // readChannel value [0 .. 4095]
    const int VALUE_THRESHOLD_MAX = 2000; // readChannel value [0 .. 4095]
    bool IsEnabled(int value)
    {
        return value < VALUE_THRESHOLD_MAX && value > VALUE_THRESHOLD_MIN;
    }
    esp_adc_cal_characteristics_t adc_chars;
    void CharacterizeAdc()
    {
        esp_adc_cal_value_t val_type = esp_adc_cal_characterize(ADC_UNIT_2, ATTEN, WIDTH, DEFAULT_VREF, &adc_chars);
        if (val_type == ESP_ADC_CAL_VAL_EFUSE_TP)
            printf("Characterized using Two Point Value\n");
        else if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF)
            printf("Characterized using eFuse Vref\n");
        else
            printf("Characterized using Default Vref\n");
    }
    void CheckEfuse()
    {
        //Check if TP is burned into eFuse
        if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_TP) == ESP_OK)
            printf("eFuse Two Point: Supported\n");
        else
            printf("eFuse Two Point: NOT supported\n");
        //Check Vref is burned into eFuse
        if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_VREF) == ESP_OK)
            printf("eFuse Vref: Supported\n");
        else
            printf("eFuse Vref: NOT supported\n");
    }

public:
    void PressOn() override { gpio_set_level(PIN_ON, LOW); }
    void PressOff() override { gpio_set_level(PIN_OFF, LOW); }
    void ReleaseOn() override { gpio_set_level(PIN_ON, HIGH); }
    void ReleaseOff() override { gpio_set_level(PIN_OFF, HIGH); }
    //bool IsGreenLedOn() override { return IsEnabled(readChannel(CHANNEL_GREEN)); }
    //bool IsRedLedOn() override { return IsEnabled(readChannel(CHANNEL_RED)); }
    bool IsGreenLedOn() override
    {
        auto x = readChannel(CHANNEL_GREEN);
        printf("green: %d\n", x);
        return IsEnabled(x);
    }
    bool IsRedLedOn() override
    {
        auto x = readChannel(CHANNEL_RED);
        printf("red: %d\n", x);
        return IsEnabled(x);
    }
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

        CheckEfuse();
        adc2_config_channel_atten((adc2_channel_t)CHANNEL_RED, ATTEN);
        adc2_config_channel_atten((adc2_channel_t)CHANNEL_GREEN, ATTEN);
        CharacterizeAdc();
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
