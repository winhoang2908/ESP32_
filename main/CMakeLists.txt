idf_component_register(SRCS "app_main.c"
                       INCLUDE_DIRS "."
                       REQUIRES input_iot
                       PRIV_REQUIRES esp_driver_gpio)
