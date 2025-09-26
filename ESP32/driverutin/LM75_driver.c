#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "esp_log.h"
#include "esp_err.h"
#include <math.h>
#include "hal/i2c_types.h"
#include "driver/i2c_master.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdbool.h>
#include <driver/i2c.h>
#include "LM75_driver.h"
#include "esp_mac.h"

#define I2_SDA_GPIO GPIO_NUM_8
#define I2_SCL_GPIO GPIO_NUM_9
#define I2C_MASTER_FREQ_HZ 100000
#define LM75_ADDRESS 0x48

static const char *TAG = "LM75";

i2c_master_dev_handle_t dev_handle;
i2c_master_bus_handle_t bus_handle;

esp_err_t init_sensor() {
    i2c_master_bus_config_t i2c_mst_config = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = I2C_NUM_0,
        .sda_io_num = I2_SDA_GPIO,
        .scl_io_num = I2_SCL_GPIO,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };

    esp_err_t err = i2c_new_master_bus(&i2c_mst_config, &bus_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to create I2C bus: %s", esp_err_to_name(err));
        return err;
    }

    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = LM75_ADDRESS,
        .scl_speed_hz = I2C_MASTER_FREQ_HZ,
    };

    err = i2c_master_bus_add_device(bus_handle, &dev_cfg, &dev_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to add I2C device: %s", esp_err_to_name(err));
        i2c_del_master_bus(bus_handle);
        return err;
    }

    // Optional: I2C scan (only for development)
    for (uint8_t addr = 0x03; addr <= 0x77; addr++) {
        esp_err_t err = i2c_master_probe(bus_handle, addr, 1000 / portTICK_PERIOD_MS);
        if (err == ESP_OK) {
            ESP_LOGI(TAG, "Found device at address 0x%02X", addr);
        } 
        else  { ESP_LOGI(TAG, " Device not be found"); 
                 return err; }
                 
    }

    ESP_LOGI(TAG, "Scan complete");
    return ESP_OK;
}

int get_raw_temperature(int16_t *raw) {
    uint8_t reg = 0x00;
    uint8_t data[2] = {0};

    esp_err_t err = i2c_master_transmit_receive(dev_handle, &reg, 1, data, 2, -1);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "I2C read failed: %s", esp_err_to_name(err));
        return err;
    }

    ESP_LOGI(TAG, "Raw I2C read: %02X %02X", data[0], data[1]);

    int16_t raw_temp = (data[0] << 1) | (data[1] >> 7);
    if (raw_temp & 0x100) {
        raw_temp |= 0xFE00; // sign extend for negative temps
    }

    *raw = raw_temp;
    return ESP_OK;
}

float convert_raw_to_celsius(int16_t raw) {
    return raw * 0.5f;
}

temp_sensor_t createTemperatureSensor() {
    temp_sensor_t sensor;
    sensor.init = &init_sensor;
    sensor.read_raw = &get_raw_temperature;
    sensor.raw_to_celsius = &convert_raw_to_celsius;
    return sensor;
}
