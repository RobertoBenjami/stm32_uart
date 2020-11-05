#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "uart.h"

/* This program shows how to receive and forward text data received on a serial line
   with line-by-line processing.

   If you want to test another serial port, modify the functions and references named uart1 _... !
*/

/* volatile because uartx_cbrx and uartx_cbrxof run in interrupt */
volatile unsigned int rxof = 0, linescount = 0;

// ----------------------------------------------------------------------------
/* usart rx callback, count the line number */
void uart1_cbrx(char rxch)
{
  if(rxch == 10)
    linescount++;
}

// ----------------------------------------------------------------------------
/* usart rx overflow callback function if RX buffer is overflowed */
void uart1_cbrxof(void)
{
  rxof++;
}

// ----------------------------------------------------------------------------
/* main application */
void mainApp(void)
{
  unsigned int pre_rxof = 0, pre_linescount = 0;
  char ch;

  printf("\r\nUart test start\r\n");

  while(1)
  {
    /* here we simulate the time of other activities in the program loop */
    HAL_Delay(100);

    /* end of line detect */
    if(linescount > pre_linescount)
    {
      printf("lines count:%d\r\n", linescount);
      while(uart1_getchar(&ch))
      {
        uart1_sendchar(ch);
      }
      pre_linescount = linescount;
    }

    /* RX buffer overflow detect */
    if(rxof > pre_rxof)
    {
      printf("rx buffer overflowed:%d\r\n", rxof);
      pre_rxof = rxof;
    }
  }
}
