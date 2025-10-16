#include "port_handler.h"

using namespace DYNAMIXEL;

/** DXLPortHandler Abstrato para criação de Interfaces personalizadas */
DXLPortHandler::DXLPortHandler()
  : open_state_(false) {}

bool DXLPortHandler::getOpenState() {
  return open_state_;
}

void DXLPortHandler::setOpenState(bool state) {
  open_state_ = state;
}


/** Definições do PortHandle Personalizado */
SerialPortHandler::SerialPortHandler( uart_port_t port, int dir_pin )
: _port(port), _tx_pin(GPIO_NUM_1), _rx_pin(GPIO_NUM_3), _buffer_size(1024), 
  _baud( 1000000 ), _tx_delay_us(1000), _dir_pin( (gpio_num_t)dir_pin ) { 
  if( _dir_pin != -1 ){
    gpio_set_direction( (gpio_num_t)_dir_pin, GPIO_MODE_OUTPUT );
    gpio_set_level( (gpio_num_t)_dir_pin, false );
    while( gpio_get_level( (gpio_num_t)_dir_pin) != false  );
  }
}


void SerialPortHandler::begin( ) {
  begin( this->_baud, this->_tx_pin, this->_rx_pin, this->_buffer_size );
}

void SerialPortHandler::begin(uint32_t baudrate) {
  begin( baudrate, this->_tx_pin, this->_rx_pin, this->_buffer_size );
}

void SerialPortHandler::begin(uint32_t baudrate, gpio_num_t tx_pin, gpio_num_t rx_pin, uint32_t buf_size) {
  this->_buffer_size = buf_size;
  this->_rx_pin = rx_pin;
  this->_tx_pin = tx_pin;
  this->_baud = baudrate;
  uart_config_t uart_config;
  uart_config.baud_rate = (int)baudrate;
  uart_config.data_bits = UART_DATA_8_BITS;
  uart_config.parity = UART_PARITY_DISABLE;
  uart_config.stop_bits = UART_STOP_BITS_1;
  uart_config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
  uart_config.rx_flow_ctrl_thresh = 1;
  uart_config.source_clk = UART_SCLK_DEFAULT;
  uart_param_config( _port, &uart_config );
  uart_set_pin( _port, _tx_pin, _rx_pin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
  uart_driver_install( _port, _buffer_size, _buffer_size, 0, NULL, 0);
  uart_set_baudrate( _port, baudrate );
  this->setOpenState( true );
}

unsigned long int SerialPortHandler::getBaud( ){
  return this->_baud; 
}


int SerialPortHandler::available() {
  size_t len;
  uart_get_buffered_data_len( _port, &len );

  return static_cast<int>(len);
}

int SerialPortHandler::read() {
  uint8_t data;
  int len = uart_read_bytes( _port, &data, 1, pdMS_TO_TICKS(10));
  return len > 0 ? data : -1;
}

size_t SerialPortHandler::write( uint8_t data) {
  return uart_write_bytes( _port, (const char*)&data, 1);
}

size_t SerialPortHandler::write(const uint8_t* data, size_t len) {
  size_t ret = uart_write_bytes( _port, (const char*)data, len );
  uart_wait_tx_done( _port, pdMS_TO_TICKS(10) );
  uart_flush( _port );
  return ret;
}

void SerialPortHandler::end() {
  uart_driver_delete( _port );
  this->setOpenState( false );
}
