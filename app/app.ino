#include "cargo_env_mon.h"

void setup()
{
    Serial.begin(9600);
    delay(5000);
    cargo_env_mon_setup();
}

void loop(){
    
}
