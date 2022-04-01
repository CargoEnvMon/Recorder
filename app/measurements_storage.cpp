#include "measurements_storage.h"
#include "cem_globals.h"

Measurement measurements[MAX_MEASUREMENTS] = {};
int index = 0;

void save_measurement(Measurement measurement) {
    measurements[index] = measurement;
    index++;
}

Measurement* get_measurements(int* length) {
    *length = index;
    return measurements;
}