#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

#include <freertos/FreeRTOS.h>
#include "wifilistener.h"
#include "cargo_env_mon.h"
#include "measurements_storage.h"
#include "cem_globals.h"
#include <freertos/task.h>
#include <Arduino.h>
#include <HardwareSerial.h>
#include <EEPROM.h>

void cargo_env_mon_setup() {
    EEPROM.begin(MAX_MEASUREMENTS_BYTES);
    
    const Measurement first = {
            .temperature = 5.1,
            .humidity = 3.3,
            .timeShift = 20,
    };

    save_measurement(first);

    const Measurement second = {
            .temperature = 5.2,
            .humidity = 3.3,
            .timeShift = 20,
    };

    save_measurement(second);
    
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