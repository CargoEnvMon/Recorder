#include "measurements_storage.h"
#include <EEPROM.h>

const size_t size = sizeof (Measurement);

unsigned char get_length() {
    return EEPROM.readUChar(0);
}

void save_measurement(Measurement measurement) {
    auto length = get_length();
    length = length == 0 ? 1 : length;
    EEPROM.writeBytes(length, &measurement, size);
    length += size;
    EEPROM.writeUChar(0, length);
    EEPROM.commit();
    delay(100);
}

Measurement *get_measurements(int *length) {
    *length = get_length() / size;
    auto measurements = new Measurement[*length];
    int mem_address = 1;
    for (int index = 0; index < *length; index++) {
        EEPROM.readBytes(mem_address, &measurements[index], size);
        mem_address += size; 
    }
    
    return measurements;
}