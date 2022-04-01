#include <WiFi.h>
#include <WiFiMulti.h>
#include "cargo_env_mon.h"

WiFiMulti WiFiMulti;

void setup()
{
    Serial.begin(115200);
    cargo_env_mon_setup();
}
