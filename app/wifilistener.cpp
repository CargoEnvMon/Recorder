#include "wifilistener.h"
#include "recorder_client.h"
#include "cem_globals.h"
#include <WiFi.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <WiFiType.h>
#include <Arduino.h>

bool try_connect();

void wifi_loop() {
    WiFi.mode(WIFI_STA);

    while (1) {
        if (try_connect()) {
            Serial.println("Connected");
            send_data();
            WiFi.disconnect();
        }

        //once in 30 secs
        vTaskDelay(pdMS_TO_TICKS(30 * 1000));
    }
}


bool try_connect() {
    int attempts = 0;
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.println("Trying to connect");
        if (attempts > 5) {
            WiFi.disconnect();
            return false;
        }
        vTaskDelay(1000);
        attempts++;
    }

    return WiFi.status() == WL_CONNECTED;
}
