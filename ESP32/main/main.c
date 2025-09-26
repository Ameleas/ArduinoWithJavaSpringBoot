#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "driver/i2c_master.h"
#include "esp_wifi.h"
#include "../driverutin/LM75_driver.h"
#include "../driverutin/wifi_driver.h"
#include "../driverutin/https_request_driver.h"
#include "../driverutin/HSS33P_driver.h"
#include "driver/adc.h"
#include "esp_crt_bundle.h"

void app_main(void) {
    // Initialize Wi-Fi
    wifi_init_sta();

    // Create temperature sensor
    temp_sensor_t sensor = createTemperatureSensor();

    // Initialize LM75
  
   //if (sensor.init() !=ESP_OK) 
   esp_err_t err=sensor.init();
  if (err != ESP_OK) {
    printf(" LM75 init failed: %s\n", esp_err_to_name(err));
   
   
} 
    // Initialize humidity sensor (e.g., ADC)
    init_humidity();

    int16_t raw_data;

    while (1) {
        // Read temperature
        float celsius_temp = 0.0f;
        int humidity = get_read_humidity();

        // Read temperature if sensor available
        int result = sensor.read_raw(&raw_data);
            if (result == ESP_OK) {
                celsius_temp = sensor.raw_to_celsius(raw_data);
            } else {
                printf("Failed to read from LM75, using 0.0°C\n");
                celsius_temp = 0.0f; // or NAN if you want to show 'null' later
            }

        printf("Humidity: %d\n", humidity);
        printf("Temperature: %.2f°C\n", celsius_temp);

        // Format JSON payload
        char new_data[200];
        snprintf(new_data, sizeof(new_data),
            "{"
             "\"id\":1,"
            "\"device_type\":\"ESP32\","
            "\"sensors\":["
                "{\"sensor_reading\":\"temperature\",\"value\":%.1f},"
                "{\"sensor_reading\":\"Humidity\",\"value\":%d}"
            "]"
            "}",
            celsius_temp, humidity);

        // Send data via HTTP
        send_data_to_postman(new_data);
      
        vTaskDelay(pdMS_TO_TICKS(20000)); // Wait 2 seconds before next read
    }
          

}
