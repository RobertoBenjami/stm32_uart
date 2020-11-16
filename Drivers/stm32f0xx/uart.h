#ifndef __UARTX_H__
#define __UARTX_H__

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------------
/* Uart RX and TX driver for stm32f0xx
     author  : Roberto Benjami
     version : 2020.11.13

   This driver also uses an interrupt and an adjustable buffer for sending and receiving.
   When receiving, it is possible to use a callback function for each character received.
   Thus, it is possible e.g. to detect the end of line character.
   Initialization will occur during the first use, so there is no uart_init function.

   For settings note:
   - UART_PRIORITY: UART RX and TX interrupt priority (0..15)
       note: 0 = the highest priority, 15 = the lowest priority

   - UART_1_6_CLK: USART1 and USART6 source frequency
       note: default (SystemCoreClock >> 1)

   - UART_2_3_4_5_7_8_CLK: USART2,3,4,5,7,8 source frequency
       note: default (SystemCoreClock >> 2)

   - UARTx_BAUDRATE: Baud rate (bit/sec)
       note: if Baud Rate = 0 -> this uart not used

   - UARTx_RX, UARTx_TX: port name, pin number, AF number (if not used -> X, 0, 0)
       note: this possible port name, pin number, AF number
       - UART1_RX: (A,10, 1) (B, 7, 0)
       - UART1_TX: (A, 9, 1) (B, 6, 0)
       - UART2_RX: (A, 3, 1) (A,15, 1) (D, 6, 0)
       - UART2_TX: (A, 2, 1) (A,14, 1) (D, 5, 0)
       - UART3_RX: (B,11, 4) (C, 5, 1) (C,11, 1) (D, 9, 0)
       - UART3_TX: (B,10, 4) (C, 4, 1) (C,10, 1) (D, 8, 0)
       - UART4_RX: (A, 1, 4) (C,11, 0) (E, 9, 1)
       - UART4_TX: (A, 0, 4) (C,10, 0) (E, 8, 1)
       - UART5_RX: (B, 4, 4) (D, 2, 2) (E,11, 1)
       - UART5_TX: (B, 3, 4) (C,12, 2) (E,10, 1)
       - UART6_RX: (A, 5, 5) (C, 1, 2) (F,10, 1)
       - UART6_TX: (A, 4, 5) (C, 0, 2) (F, 9, 1)
       - UART7_RX: (C, 7, 1) (F, 3, 1)
       - UART7_TX: (C, 6, 1) (F, 2, 1)
       - UART8_RX: (C, 9, 1) (D,14, 0)
       - UART8_TX: (C, 8, 1) (D,13, 0)

   - TXBUFx_SIZE, RXBUFx_SIZE: buffer size (4,8,16,32,64,128,256,512,1024,2048,...)
       note: the buffer size should be (2 ^ n) !

   - UARTx_PRINTF (printf redirect): 0 -> printf to uart disabled, 1 -> printf to uart eanbled
       note: can only be active on one usart

   - uartx_sendchar: send one character to usart
       note: if the TX buffer is full, it will wait until there is free space in it

   - uartx_getchar: receiving a character on uart rx
       note: if return = 0 -> no characters received (not block the program from running)
             if return = 1 -> &c = received character

   - uartx_cbrx: if you want to know that a character has arrived, do a function with that name
       note: attention, it will be operated from an interruption!

   - uartx_cbrxof: if you want to know that an RX buffer is overflowed, do a function with that name
       note: if this function is enabled, RX data loss has occurred
             attention, it will be operated from an interruption!
*/

//----------------------------------------------------------------------------
#define  UART_PRIORITY   15

#define  UART_1_CLK                SystemCoreClock >> 1
#define  UART_2_CLK                SystemCoreClock >> 1
#define  UART_3_CLK                SystemCoreClock >> 1
#define  UART_4_5_6_7_8_CLK        SystemCoreClock >> 1

  //----------------------------------------------------------------------------
#define  UART1_BAUDRATE   0
#define  UART1_RX   A,10, 1
#define  UART1_TX   A, 9, 1
#define  RXBUF1_SIZE  64
#define  TXBUF1_SIZE  64
#define  UART1_PRINTF  0

char     uart1_sendchar(char c);
char     uart1_getchar(char * c);
__weak void uart1_cbrx(char rxch);
__weak void uart1_cbrxof(void);

//----------------------------------------------------------------------------
#define  UART2_BAUDRATE   0
#define  UART2_RX   A, 3, 1
#define  UART2_TX   A, 2, 1
#define  RXBUF2_SIZE  64
#define  TXBUF2_SIZE  64
#define  UART2_PRINTF  0

char     uart2_sendchar(char c);
char     uart2_getchar(char * c);
__weak void uart2_cbrx(char rxch);
__weak void uart2_cbrxof(void);

//----------------------------------------------------------------------------
#define  UART3_BAUDRATE   0
#define  UART3_RX   B,11, 4
#define  UART3_TX   B,10, 4
#define  RXBUF3_SIZE  64
#define  TXBUF3_SIZE  64
#define  UART3_PRINTF  0

char     uart3_sendchar(char c);
char     uart3_getchar(char * c);
__weak void uart3_cbrx(char rxch);
__weak void uart3_cbrxof(void);

//----------------------------------------------------------------------------
#define  UART4_BAUDRATE   0
#define  UART4_RX   A, 1, 4
#define  UART4_TX   A, 0, 4
#define  RXBUF4_SIZE  64
#define  TXBUF4_SIZE  64
#define  UART4_PRINTF  0

char     uart4_sendchar(char c);
char     uart4_getchar(char * c);
__weak void uart4_cbrx(char rxch);
__weak void uart4_cbrxof(void);

//----------------------------------------------------------------------------
#define  UART5_BAUDRATE   0
#define  UART5_RX   B, 4, 4
#define  UART5_TX   B, 3, 4
#define  RXBUF5_SIZE  64
#define  TXBUF5_SIZE  64
#define  UART5_PRINTF  0

char     uart5_sendchar(char c);
char     uart5_getchar(char * c);
__weak void uart5_cbrx(char rxch);
__weak void uart5_cbrxof(void);

//----------------------------------------------------------------------------
#define  UART6_BAUDRATE   0
#define  UART6_RX   A, 5, 5
#define  UART6_TX   A, 4, 5
#define  RXBUF6_SIZE  64
#define  TXBUF6_SIZE  64
#define  UART6_PRINTF  0

char     uart6_sendchar(char c);
char     uart6_getchar(char * c);
__weak void uart6_cbrx(char rxch);
__weak void uart6_cbrxof(void);

//----------------------------------------------------------------------------
#define  UART7_BAUDRATE   0
#define  UART7_RX   C, 7, 1
#define  UART7_TX   C, 6, 1
#define  RXBUF7_SIZE  64
#define  TXBUF7_SIZE  64
#define  UART7_PRINTF  0

char     uart7_sendchar(char c);
char     uart7_getchar(char * c);
__weak void uart7_cbrx(char rxch);
__weak void uart7_cbrxof(void);

//----------------------------------------------------------------------------
#define  UART8_BAUDRATE   0
#define  UART8_RX   C, 9, 1
#define  UART8_TX   C, 8, 1
#define  RXBUF8_SIZE  64
#define  TXBUF8_SIZE  64
#define  UART8_PRINTF  0

char     uart8_sendchar(char c);
char     uart8_getchar(char * c);
__weak void uart8_cbrx(char rxch);
__weak void uart8_cbrxof(void);

#ifdef __cplusplus
}
#endif

#endif  /* __UARTX_H__ */
