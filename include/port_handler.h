/*******************************************************************************
* Copyright 2016 ROBOTIS CO., LTD.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#ifndef DYNAMIXEL_PORT_HANDLER_HPP_
#define DYNAMIXEL_PORT_HANDLER_HPP_


#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/timers.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "driver/uart.h"
#include "driver/gpio.h"

#include "string.h"
#include "stdint.h"
#include "stdio.h"


/** @details Classe Abstrata para usar a interface de comunicação 
 *  compatível com o Dynamixel2Arduino.
 *  @note Para usar com outras interfaces de comunicalçao, é 
 *  necessário criar um DXLPortHandler personalizado para cada 
 *  interface. 
 **/
class DXLPortHandler{
  public:
    DXLPortHandler();
    
    virtual void begin() = 0;
    virtual void end() = 0;
    virtual int available(void) = 0;
    virtual int read() = 0;
    virtual size_t write(uint8_t) = 0;
    virtual size_t write( const uint8_t *buf, size_t len) = 0;
    bool getOpenState();
    void setOpenState(bool);

  private:
    bool open_state_;
};


namespace DYNAMIXEL{

class SerialPortHandler : public DXLPortHandler {
  private:
    uart_port_t _port;
    gpio_num_t _tx_pin;
    gpio_num_t _rx_pin;
    uint32_t _buffer_size;
    uint32_t _baud;
    uint32_t _tx_delay_us;
    gpio_num_t _dir_pin;

  public:
    SerialPortHandler( uart_port_t port, int dir_pin = -1 );

    virtual void begin() override;
    void begin( uint32_t baud, gpio_num_t tx_pin, gpio_num_t rx_pin, uint32_t buff_size = 2048 );
    void begin( uint32_t baud );
    
    unsigned long int getBaud( );

    virtual int available(void) override;
    
    virtual size_t write(uint8_t) override;
    virtual size_t write( const uint8_t *buf, size_t len) override;
    virtual int read() override;
    
    virtual void end() override;
};

}


#endif /* DYNAMIXEL_PORT_HANDLER_HPP_ */