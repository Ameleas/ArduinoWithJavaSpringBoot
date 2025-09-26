#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "adc_cali_interface.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_err.h"
#include "../esp_adc_cal_internal_legacy.h"
#include "hal/adc_types.h"
#include "adc1_private.h"
#include "driver/gpio.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_continuous.h"
#include "HSS33P_driver.h"
#define ADC_CHANNEL ADC_CHANNEL_3  


adc_oneshot_unit_handle_t adc1_handle;
int init_humidity(){
    adc_oneshot_unit_init_cfg_t init_config1 = {
    .unit_id = ADC_UNIT_1,
    .ulp_mode = ADC_ULP_MODE_DISABLE,
};
ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1, &adc1_handle));

 adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_12,  // wider voltage range: up to ~3.3V
 };
ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL, &config));

return 0;

}

int get_read_humidity(){
    int adc_raw=0;
    ESP_ERROR_CHECK(adc_oneshot_read(adc1_handle, ADC_CHANNEL, &adc_raw));

    return adc_raw;
}