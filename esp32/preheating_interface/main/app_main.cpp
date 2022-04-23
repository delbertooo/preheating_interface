#define PREHEATING_INTERFACE_VERBOSITY 3

#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

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

    LibPreheatingInterface::PowerOnCommand cmdOn{commandHelper};
    auto resultOn = cmdOn.PowerOn();
    printf("\npower on result was %s\n", (resultOn.IsError() ? "error" : "success"));

    printf("waiting 5s...\n");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    
    LibPreheatingInterface::PowerOffCommand cmdOff{commandHelper};
    auto resultOff = cmdOff.PowerOff();

    printf("\npower off result was %s\n", (resultOff.IsError() ? "error" : "success"));

    fflush(stdout);
    //esp_restart();
}
