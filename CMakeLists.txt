idf_component_register(
    SRCS 
        src/dynamixel2idf.cpp
        src/port_handler.cpp
        src/actuator.cpp
        src/protocol.cpp
        src/master.cpp
        src/slave.cpp
    
    INCLUDE_DIRS 
        "include"

    REQUIRES 
        esp_driver_uart 
        esp_driver_gpio
        esp_timer 
)