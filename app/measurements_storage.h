#ifndef APP_MEASUREMENTS_STORAGE_H
#define APP_MEASUREMENTS_STORAGE_H

struct measurement {
    float temperature;
    float humidity;
    unsigned char timeShift;
};

typedef struct measurement Measurement ;

void save_measurement(Measurement);

Measurement* get_measurements(int* length);

#endif //APP_MEASUREMENTS_STORAGE_H
