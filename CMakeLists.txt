idf_component_register(
    SRCS 
        src/Dynamixel2Espidf.cpp
        src/port_handler.cpp
        src/actuator.cpp
        src/protocol.cpp
        src/master.cpp
        src/slave.cpp
    
    INCLUDE_DIRS 
        "../../controllers/"
        "include"

    REQUIRES 
        esp_timer 

    PRIV_REQUIRES 
        esp_driver_uart 
        esp_driver_gpio
)
