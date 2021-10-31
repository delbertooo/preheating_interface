/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"


#include <sys/time.h>
#include <LibPreheatingInterface.hpp>


extern "C" {
	void app_main(void);
}


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
} myRemote;

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
} myPlatform;

LibPreheatingInterface::CommandHelper commandHelper{myPlatform, myPlatform, myRemote};

void app_main(void)
{
    myRemote.Boot();
    LibPreheatingInterface::PowerOnCommand cmd{commandHelper};
    auto result = cmd.PowerOn();
    printf("Hello world!\n");

    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is %s chip with %d CPU core(s), WiFi%s%s, ",
            CONFIG_IDF_TARGET,
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    printf("Minimum free heap size: %d bytes\n", esp_get_minimum_free_heap_size());

    for (int i = 10; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    printf("Restarting now.\n");
    fflush(stdout);
    esp_restart();
}
