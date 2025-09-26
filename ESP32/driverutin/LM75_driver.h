#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "esp_log.h"
#include "esp_err.h" 

typedef struct {
 esp_err_t (*init)(void);
 int (*read_raw)(int16_t *raw);
 float (*raw_to_celsius)(int16_t raw);
 } temp_sensor_t;
int get_raw_temperature(int16_t *raw);
float convert_raw_to_celsius(int16_t raw);
temp_sensor_t createTemperatureSensor();