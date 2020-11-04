# stm32_uart

stm32 uart driver
  This driver also uses an interrupt and an adjustable buffer for sending and receiving.
  When receiving, it is possible to use a callback function for each character received.
  Thus, it is possible e.g. to detect the end of line character.
  Initialization will occur during the first use, so there is no uart_init function.
  
Example app:
- app_uart_test: 
    This program shows how to receive and forward text data received on a serial line
    with line-by-line processing. 

