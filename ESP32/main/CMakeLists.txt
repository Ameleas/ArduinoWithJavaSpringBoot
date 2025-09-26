idf_component_register(
    SRCS 
        "main.c"
        "../driverutin/LM75_driver.c"
        "../driverutin/HSS33P_driver.c"
        "../driverutin/https_request_driver.c"
        "../driverutin/wifi_driver.c"
    INCLUDE_DIRS 
        "."
        "../driverutin"
    
)
