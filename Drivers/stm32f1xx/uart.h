#ifndef __UARTX_H__
#define __UARTX_H__


#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------------
/* Uart RX and TX driver for stm32f1xx
     author  : Roberto Benjami
     version : 2020.11.13

   This driver also uses an interrupt and an adjustable buffer for sending and receiving.
   When receiving, it is possible to use a callback function for each character received.
   Thus, it is possible e.g. to detect the end of line character.
   Initialization will occur during the first use, so there is no uart_init function.

   For settings note:
   - UART_PRIORITY: UART RX and TX interrupt priority (0..15)
       note: 0 = the highest priority, 15 = the lowest priority

   - UART_1_CLK: USART1 source frequency
       note: default (SystemCoreClock)

   - UART_2_3_4_5_CLK: USART2,3,4,5 source frequency
       note: default (SystemCoreClock >> 1)

   - UARTx_BAUDRATE: Baud rate
       note: if Baud Rate = 0 -> this Uart not used

   - UARTx_RX, UARTx_TX: port name, pin number (if not used -> X, 0)
       note: see the data sheet which pin can be adjusted
             it is possible to use only the transmission or only the reception on its own

   - UARTx_REMAP: The location of the uart pins can be changed (see in the datasheet)
       UART1_REMAP 0 -> (TX=A9, RX=A10),  UART1_REMAP 1 -> (TX=B6, RX=B7)
       UART2_REMAP 0 -> (TX=A2, RX=A3),   UART2_REMAP 1 -> (TX=D5, RX=D6)
       UART3_REMAP 0 -> (TX=B10, RX=B11), UART3_REMAP 1 -> (TX=C10, RX=C11), UART3_REMAP 3 -> (TX=D8, RX=D9)
       note: UART4 (TX=C10, RX=C11) and UART5 (TX=C12, RX=D2) remap not possible

   - TXBUFx_SIZE, RXBUFx_SIZE: buffer size (4,8,16,32,64,128,256,512,1024,2048,...)
       note: if 0 -> RX or TX function will not be available
             the buffer size should be (2 ^ n) !

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

#define  UART_1_CLK                SystemCoreClock
#define  UART_2_3_4_5_CLK          SystemCoreClock >> 1

//----------------------------------------------------------------------------
#define  UART1_BAUDRATE  0
#define  UART1_RX  A, 10
#define  UART1_TX  A,  9
#define  UART1_REMAP   0
#define  TXBUF1_SIZE  64
#define  RXBUF1_SIZE  64
#define  UART1_PRINTF  0

char     uart1_sendchar(char c);
char     uart1_getchar(char * c);
__weak void uart1_cbrx(char rxch);
__weak void uart1_cbrxof(void);

//----------------------------------------------------------------------------
#define  UART2_BAUDRATE  0
#define  UART2_RX   A, 3
#define  UART2_TX   A, 2
#define  UART2_REMAP   0
#define  RXBUF2_SIZE  64
#define  TXBUF2_SIZE  64
#define  UART2_PRINTF  0

char     uart2_sendchar(char c);
char     uart2_getchar(char * c);
__weak void uart2_cbrx(char rxch);
__weak void uart2_cbrxof(void);

//----------------------------------------------------------------------------
#define  UART3_BAUDRATE  0
#define  UART3_RX  B, 10
#define  UART3_TX  B, 11
#define  UART3_REMAP   0
#define  RXBUF3_SIZE  64
#define  TXBUF3_SIZE  64
#define  UART3_PRINTF  0

char     uart3_sendchar(char c);
char     uart3_getchar(char * c);
__weak void uart3_cbrx(char rxch);
__weak void uart3_cbrxof(void);

//----------------------------------------------------------------------------
#define  UART4_BAUDRATE  0
#define  UART4_RX  C, 11
#define  UART4_TX  C, 10
#define  RXBUF4_SIZE  64
#define  TXBUF4_SIZE  64
#define  UART4_PRINTF  0

char     uart4_sendchar(char c);
char     uart4_getchar(char * c);
__weak void uart4_cbrx(char rxch);
__weak void uart4_cbrxof(void);

//----------------------------------------------------------------------------
#define  UART5_BAUDRATE  0
#define  UART5_RX  D,  2
#define  UART5_TX  C, 12
#define  RXBUF5_SIZE  64
#define  TXBUF5_SIZE  64
#define  UART5_PRINTF  0

char     uart5_sendchar(char c);
char     uart5_getchar(char * c);
__weak void uart5_cbrx(char rxch);
__weak void uart5_cbrxof(void);

#ifdef __cplusplus
}
#endif

#endif  /* __UARTX_H__ */
