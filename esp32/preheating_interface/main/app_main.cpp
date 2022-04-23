#define PREHEATING_INTERFACE_VERBOSITY 3

#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "setup.hpp"

extern "C" {
    void app_main(void);
}


void app_main(void)
{
    MyRemote myRemote{};
    MyPlatform myPlatform{};
    LibPreheatingInterface::CommandHelper commandHelper{myPlatform, myPlatform, myRemote};

    myRemote.Boot();
    LibPreheatingInterface::PowerOnCommand cmd{commandHelper};
    auto result = cmd.PowerOn();
    printf("result was %s\n", (result.IsError() ? "error" : "success"));
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    result = cmd.PowerOn();
    
    //LibPreheatingInterface::PowerOffCommand cmd2{commandHelper};
    //auto result2 = cmd2.PowerOff();

    printf("result was %s\n", (result.IsError() ? "error" : "success"));

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
        //printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    printf("Restarting now.\n");
    fflush(stdout);
    //esp_restart();
}
