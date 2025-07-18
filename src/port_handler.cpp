#include "include/port_handler.h"


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
IDFPortHandler::IDFPortHandler( uart_port_t port )
: _port(port), _txPin(-1), _rxPin(-1), _buffer_size(1024), 
  baud_( 1000000 ), tx_delay_us_(1000) { }

void IDFPortHandler::begin(uint32_t baudrate) {
  _txPin = GPIO_NUM_1;  // UART0 TX padrão
  _rxPin = GPIO_NUM_3;  // UART0 RX padrão
  begin( baudrate, _txPin, _rxPin, this->_buffer_size );
}

void IDFPortHandler::begin(uint32_t baudrate, int txPin, int rxPin) {
  begin(baudrate, txPin, rxPin, this->_buffer_size);
}

void IDFPortHandler::begin(uint32_t baudrate, int txPin, int rxPin, int buf_size) {
  this->_buffer_size = buf_size;
  this->_rxPin = rxPin;
  this->_txPin = txPin;
  uart_config_t config = {
      .baud_rate = baudrate,
      .data_bits = UART_DATA_8_BITS,
      .parity = UART_PARITY_DISABLE,
      .stop_bits = UART_STOP_BITS_1,
      .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
      .source_clk = UART_SCLK_APB,
  };
  uart_param_config( _port, &config );
  uart_set_pin( _port, _txPin, _rxPin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
  uart_driver_install( _port, _buffer_size, 0, 0, NULL, 0);
  this->setOpenState( true );
}

int IDFPortHandler::available() {
  size_t len;
  uart_get_buffered_data_len( _port, &len );
  return static_cast<int>(len);
}

int IDFPortHandler::read() {
  uint8_t data;
  int len = uart_read_bytes( _port, &data, 1, pdMS_TO_TICKS(10));
  return len > 0 ? data : -1;
}

size_t IDFPortHandler::write( uint8_t data) {
  return uart_write_bytes( _port, reinterpret_cast<const char*>(&data), 1);
}

size_t IDFPortHandler::write(const uint8_t* data, size_t len) {
  return uart_write_bytes( _port, reinterpret_cast<const char*>(data), len );
}

void IDFPortHandler::end() {
  uart_driver_delete( _port );
  this->setOpenState( false );
}
