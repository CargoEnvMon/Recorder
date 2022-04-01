#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

#include <freertos/FreeRTOS.h>
#include "wifilistener.h"
#include "cargo_env_mon.h"
#include "measurements_storage.h"
#include <freertos/task.h>

void cargo_env_mon_setup() {
    const Measurement first = {
            .temperature = 5.1,
            .humidity = 3.3,
            .timeShift = 20,
    };
    save_measurement(first);

    const Measurement second = {
            .temperature = 8.1,
            .humidity = 7.3,
            .timeShift = 21,
    };
    save_measurement(second);

    const Measurement third = {
            .temperature = 15.1,
            .humidity = 5.3,
            .timeShift = 19,
    };
    save_measurement(third);

    xTaskCreatePinnedToCore(
            [](void *) {
                wifi_loop();
            },
            "WiFiLoop",
            1024 * 3,
            NULL,
            1,
            NULL,
            ARDUINO_RUNNING_CORE);
}