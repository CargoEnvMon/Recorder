#include <WiFiClient.h>
#include "recorder_client.h"
#include "cem_globals.h"
#include "measurements_storage.h"
#include <Arduino.h>

void send_data() {
    int length;
    const auto items = get_measurements(&length);

    if (length <= 0) {
        return;
    }
    
    WiFiClient client;
    if (!client.connect(RECORDER_IP, RECORDER_PORT)) {
        return;
    }
    String header = CARGO_ID"|1648410051380|3";
    client.println(header);

    for (int index = 0; index < length; ++index) {
        const auto item = items[0];
        String line = "";
        line.concat(item.timeShift);
        line.concat("|");
        line.concat(item.temperature);
        line.concat("|");
        line.concat(item.humidity);
        
        client.println(line);
    }
    
    client.print("<EOF>");
}