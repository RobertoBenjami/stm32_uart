# Stm32_uart driver

Stm32 uart driver
  This driver also uses an interrupt and an adjustable buffer for sending and receiving.
  When receiving, it is possible to use a callback function for each character received.
  Thus, it is possible e.g. to detect the end of line character.
  Initialization will occur during the first use, so there is no uart_init function.

Can be used in microcontroller families:
- stm32f0xx
- stm32f1xx
- stm32f2xx
- stm32f3xx
- stm32f4xx
- stm32f7xx
- stm32h7xx
  
Example app:
- app_uart_test: 
    This program shows how to receive and forward text data received on a serial line
    with line-by-line processing. 

Uart functions:
- uartx_sendchar(char c): send one character to usart
  note: if the TX buffer is full, it will wait until there is free space in it

- uartx_getchar(char * c); receiving a character on uart rx
  note: if return = 0 -> no characters received (not block the program from running)
        if return = 1 -> &c = received character

- uartx_cbrx(char rxch): if you want to know that a character has arrived, do a function with that name (optional)
  note: attention, it will be operated from an interruption!

- uartx_cbrxof: if you want to know that an RX buffer is overflowed, do a function with that name (optional)
  note: if this function is enabled, RX data loss has occurred
        attention, it will be operated from an interruption!

Uart settings in uart.h (see the comments in this header):
f0, f2, f3, f4, f7, h7 family:  
- UARTx_RX, UARTx_TX: port name, pin number, AF number (if not used -> X, 0, 0)

f1 family:
- UARTx_RX, UARTx_TX: port name, pin number (if not used -> X, 0)
  note: see the data sheet which pin can be adjusted
  it is possible to use only the transmission or only the reception on its own
- UARTx_REMAP: The location of the uart pins can be changed (see in the datasheet)

all family:
- UARTx_BAUDRATE: Baud rate (bit/sec)
  note: if Baud Rate = 0 -> this uart not used

- TXBUFx_SIZE, RXBUFx_SIZE: buffer size (4,8,16,32,64,128,256,512,1024,2048,...)
  note: the buffer size should be (2 ^ n) !

- UARTx_PRINTF (printf redirect): 0 -> printf to uart disabled, 1 -> printf to uart eanbled
  note: can only be active on one usart

- UART_X_CLK: USART source frequency (see the comment in the header file)

- UART_PRIORITY: UART RX and TX interrupt priority (0..15)
  note: 0 = the highest priority, 15 = the lowest priority
