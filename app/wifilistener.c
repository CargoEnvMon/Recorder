#include "wifilistener.h"
#include "recorder_client.h"
#include <WiFi.h>
#include <WiFiType.h>
#include <freertos/task.h>

const char *ssid = "cem_recorder";
const char *password = "123456";

bool try_connect();

void wifi_loop() {
    WiFi.mode(WIFI_STA);

    while (1) {
        if (try_connect()) {
            send_data();
            WiFi.disconnect();
        }

        //once in 30 secs
        vTaskDelay(pdMS_TO_TICKS(30 * 1000));
    }
}


bool try_connect() {
    int attempts = 0;
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        if (attempts > 5) {
            WiFi.disconnect();
            return false;
        }
        vTaskDelay(1000);
        attempts++;
    }

    return WiFi.status() != WL_CONNECTED;
}
