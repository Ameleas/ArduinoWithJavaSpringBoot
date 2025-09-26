#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_netif.h"
#include "nvs_flash.h"
#include "freertos/event_groups.h"
#include "esp_netif.h"
#include "nvs_flash.h"
#include "esp_https_server.h"
#include "esp_http_client.h"
#include "esp_cam_ctlr_interface.h"
#include "esp_crt_bundle.h"
#include "https_request_driver.h"
static const char* TAG_HTTP ="HTTP_CLIENT";
//HTTP-----TLS/SSL------TCP  

void send_data_to_postman(const char *post_data ) {
 
    //https_request
    esp_http_client_config_t config = {
        .url = POSTMAN_SERVER_URL,
        .method = HTTP_METHOD_POST,
        .tls_version = ESP_HTTP_CLIENT_TLS_VER_TLS_1_2,
        .username = "test",
        .password = "test",      
        .crt_bundle_attach = esp_crt_bundle_attach,//Enable ESP-IDF  inside CA certification method
        .transport_type = HTTP_TRANSPORT_OVER_SSL,
        .buffer_size = 4096,
        .buffer_size_tx = 4096,
        .skip_cert_common_name_check = false,  
         .cert_pem = NULL,  //must set up this certification option null  so that the bundle can opened.
        .keep_alive_enable = true,
        .keep_alive_idle = 30,
        .keep_alive_interval = 5,
        .keep_alive_count = 3,
        .timeout_ms = 15000,
    };
    
    // 3. send data ,HTTP request segment
    //start http session, the option must be called first(start_line)
    esp_http_client_handle_t client = esp_http_client_init(&config);

   //Set post data, this function must be called before esp_http_client_perform,to tell how to format 
   // specify the data format of the request body (JSON format) 
    esp_http_client_set_header(client, "Content-Type", "application/json");
//Set http request header, this function must be called after esp_http_client_init and before any perform function
  //request body
    esp_http_client_set_post_field(client, post_data, strlen(post_data));
     //Invoke this function after esp_http_client_init and all the options calls are made, 
    //and will perform the transfer as described in the options. It must be called with the same esp_http_client_handle_t as input as the esp_http_client_init call returned.
   //include emptyline and perform request
    esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        ESP_LOGI(TAG_HTTP, "successful: %d", esp_http_client_get_status_code(client));
    } else {
        ESP_LOGE(TAG_HTTP, "send data fail: %s", esp_err_to_name(err));
    }
    
    // 5. clean and shut down network
    esp_http_client_cleanup(client);
}
