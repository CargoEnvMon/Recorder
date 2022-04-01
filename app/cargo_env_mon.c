#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "cargo_env_mon.h"
#include "wifilistener.h"

void cargo_env_mon_setup() {
    xTaskCreatePinnedToCore(
            wifi_loop,
            "WiFiLoop",
            1024 * 3,
            NULL,
            1,
            NULL,
            ARDUINO_RUNNING_CORE);
}