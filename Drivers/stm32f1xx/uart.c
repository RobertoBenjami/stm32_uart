/* Uart RX and TX driver for stm32f1xx
     author  : Roberto Benjami
     version : 2020.11.04
*/

#include <stdio.h>
#include "main.h"
#include "uart.h"

//----------------------------------------------------------------------------
// portláb módok (PP: push-pull, OD: open drain, FF: input floating)
#define MODE_ANALOG_INPUT     0x0
#define MODE_PP_OUT_10MHZ     0x1
#define MODE_PP_OUT_2MHZ      0x2
#define MODE_PP_OUT_50MHZ     0x3
#define MODE_FF_DIGITAL_INPUT 0x4
#define MODE_OD_OUT_10MHZ     0x5
#define MODE_OD_OUT_2MHZ      0x6
#define MODE_OD_OUT_50MHZ     0x7
#define MODE_PU_DIGITAL_INPUT 0x8
#define MODE_PP_ALTER_10MHZ   0x9
#define MODE_PP_ALTER_2MHZ    0xA
#define MODE_PP_ALTER_50MHZ   0xB
#define MODE_RESERVED         0xC
#define MODE_OD_ALTER_10MHZ   0xD
#define MODE_OD_ALTER_2MHZ    0xE
#define MODE_OD_ALTER_50MHZ   0xF

#define GPIOX_(a, b)          GPIO ## a
#define GPIOX(a)              GPIOX_(a)

#define GPIOX_PIN_(a, b)      b
#define GPIOX_PIN(a)          GPIOX_PIN_(a)

#define GPIOX_MODE_(a,b,c)    ((GPIO_TypeDef*)(((c & 8) >> 1) + GPIO ## b ## _BASE))->CRL = (((GPIO_TypeDef*)(((c & 8) >> 1) + GPIO ## b ## _BASE))->CRL & ~(0xF << ((c & 7) << 2))) | (a << ((c & 7) << 2))
#define GPIOX_MODE(a, b)      GPIOX_MODE_(a, b)

#define GPIOX_ODR_(a, b)      BITBAND_ACCESS(GPIO ## a ->ODR, b)
#define GPIOX_ODR(a)          GPIOX_ODR_(a)

#define GPIOX_IDR_(a, b)      BITBAND_ACCESS(GPIO ## a ->IDR, b)
#define GPIOX_IDR(a)          GPIOX_IDR_(a)

#define GPIOX_LINE_(a, b)     EXTI_Line ## b
#define GPIOX_LINE(a)         GPIOX_LINE_(a)

#define GPIOX_PORTSRC_(a, b)  GPIO_PortSourceGPIO ## a
#define GPIOX_PORTSRC(a)      GPIOX_PORTSRC_(a)

#define GPIOX_PINSRC_(a, b)   GPIO_PinSource ## b
#define GPIOX_PINSRC(a)       GPIOX_PINSRC_(a)

#define GPIOX_CLOCK_(a, b)    RCC_APB2ENR_IOP ## a ## EN
#define GPIOX_CLOCK(a)        GPIOX_CLOCK_(a)

#define GPIOX_PORTNUM_A       1
#define GPIOX_PORTNUM_B       2
#define GPIOX_PORTNUM_C       3
#define GPIOX_PORTNUM_D       4
#define GPIOX_PORTNUM_E       5
#define GPIOX_PORTNUM_F       6
#define GPIOX_PORTNUM_G       7
#define GPIOX_PORTNUM_H       8
#define GPIOX_PORTNUM_I       9
#define GPIOX_PORTNUM_J       10
#define GPIOX_PORTNUM_K       11
#define GPIOX_PORTNUM_(a, b)  GPIOX_PORTNUM_ ## a
#define GPIOX_PORTNUM(a)      GPIOX_PORTNUM_(a)

#define GPIOX_PORTNAME_(a, b) a
#define GPIOX_PORTNAME(a)     GPIOX_PORTNAME_(a)

//----------------------------------------------------------------------------
const uint8_t rcc_dividetable[] = {0, 0, 0, 0, 1, 2, 3, 4};

//----------------------------------------------------------------------------
// Itt lehet meghatározni melyik uart-ot akarjuk használni
#if UART1_BAUDRATE > 0 && (GPIOX_PORTNUM(UART1_RX) >= GPIOX_PORTNUM_A || GPIOX_PORTNUM(UART1_TX) >= GPIOX_PORTNUM_A)
#define UARTX                 USART1
#define UARTX_IRQHandler      USART1_IRQHandler
#define UARTX_IRQn            USART1_IRQn
#define UARTX_CLOCLK_ON       RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
#define UARTX_BRR_CALC        (SystemCoreClock >> rcc_dividetable[(RCC->CFGR & RCC_CFGR_PPRE2_Msk) >> RCC_CFGR_PPRE2_Pos]) / UART1_BAUDRATE
#define UARTX_RX              UART1_RX
#define UARTX_TX              UART1_TX
#define UARTX_REMAP           UART1_REMAP
#define UARTX_MAPR            AFIO_MAPR_USART1_REMAP_Pos
#define TXBUFX_SIZE           TXBUF1_SIZE
#define RXBUFX_SIZE           RXBUF1_SIZE
#define UARTX_PRINTF          UART1_PRINTF
#define uartx_inited          uart1_inited
#define txx_restart           tx1_restart
#define bufx_r                buf1_r
#define bufx_t                buf1_t
#define rbufx                 rbuf1
#define tbufx                 tbuf1
#define uartx_init            uart1_init
#define uartx_sendchar        uart1_sendchar
#define uartx_getchar         uart1_getchar
#define uartx_cbrx            uart1_cbrx
#define uartx_cbrxof          uart1_cbrxof
#include "uartx.h"
#endif

#if UART2_BAUDRATE > 0 && (GPIOX_PORTNUM(UART2_RX) >= GPIOX_PORTNUM_A || GPIOX_PORTNUM(UART2_TX) >= GPIOX_PORTNUM_A)
#define UARTX                 USART2
#define UARTX_IRQHandler      USART2_IRQHandler
#define UARTX_IRQn            USART2_IRQn
#define UARTX_CLOCLK_ON       RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
#define UARTX_BRR_CALC        (SystemCoreClock >> rcc_dividetable[(RCC->CFGR & RCC_CFGR_PPRE1_Msk) >> RCC_CFGR_PPRE1_Pos]) / UART2_BAUDRATE
#define UARTX_RX              UART2_RX
#define UARTX_TX              UART2_TX
#define UARTX_REMAP           UART2_REMAP
#define UARTX_MAPR            AFIO_MAPR_USART2_REMAP_Pos
#define TXBUFX_SIZE           TXBUF2_SIZE
#define RXBUFX_SIZE           RXBUF2_SIZE
#define UARTX_PRINTF          UART2_PRINTF
#define uartx_inited          uart2_inited
#define txx_restart           tx2_restart
#define bufx_r                buf2_r
#define bufx_t                buf2_t
#define rbufx                 rbuf2
#define tbufx                 tbuf2
#define uartx_init            uart2_init
#define uartx_sendchar        uart2_sendchar
#define uartx_getchar         uart2_getchar
#define uartx_cbrx            uart2_cbrx
#define uartx_cbrxof          uart2_cbrxof
#include "uartx.h"
#endif

#if UART3_BAUDRATE > 0 && (GPIOX_PORTNUM(UART3_RX) >= GPIOX_PORTNUM_A || GPIOX_PORTNUM(UART3_TX) >= GPIOX_PORTNUM_A)
#define UARTX                 USART3
#define UARTX_IRQHandler      USART3_IRQHandler
#define UARTX_IRQn            USART3_IRQn
#define UARTX_CLOCLK_ON       RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
#define UARTX_BRR_CALC        (SystemCoreClock >> rcc_dividetable[(RCC->CFGR & RCC_CFGR_PPRE1_Msk) >> RCC_CFGR_PPRE1_Pos]) / UART3_BAUDRATE
#define UARTX_RX              UART3_RX
#define UARTX_TX              UART3_TX
#define UARTX_REMAP           UART3_REMAP
#define UARTX_MAPR            AFIO_MAPR_USART3_REMAP_Pos
#define TXBUFX_SIZE           TXBUF3_SIZE
#define RXBUFX_SIZE           RXBUF3_SIZE
#define UARTX_PRINTF          UART3_PRINTF
#define uartx_inited          uart3_inited
#define txx_restart           tx3_restart
#define bufx_r                buf3_r
#define bufx_t                buf3_t
#define rbufx                 rbuf3
#define tbufx                 tbuf3
#define uartx_init            uart3_init
#define uartx_sendchar        uart3_sendchar
#define uartx_getchar         uart3_getchar
#define uartx_cbrx            uart3_cbrx
#define uartx_cbrxof          uart3_cbrxof
#include "uartx.h"
#endif

#if UART4_BAUDRATE > 0 && (GPIOX_PORTNUM(UART4_RX) >= GPIOX_PORTNUM_A || GPIOX_PORTNUM(UART4_TX) >= GPIOX_PORTNUM_A)
#define UARTX                 UART4
#define UARTX_IRQHandler      UART4_IRQHandler
#define UARTX_IRQn            UART4_IRQn
#define UARTX_CLOCLK_ON       RCC->APB1ENR |= RCC_APB1ENR_UART4EN;
#define UARTX_BRR_CALC        (SystemCoreClock >> rcc_dividetable[(RCC->CFGR & RCC_CFGR_PPRE1_Msk) >> RCC_CFGR_PPRE1_Pos]) / UART4_BAUDRATE
#define UARTX_RX              UART4_RX
#define UARTX_TX              UART4_TX
#define UARTX_REMAP           0
#define UARTX_MAPR
#define TXBUFX_SIZE           TXBUF4_SIZE
#define RXBUFX_SIZE           RXBUF4_SIZE
#define UARTX_PRINTF          UART4_PRINTF
#define uartx_inited          uart4_inited
#define txx_restart           tx4_restart
#define bufx_r                buf4_r
#define bufx_t                buf4_t
#define rbufx                 rbuf4
#define tbufx                 tbuf4
#define uartx_init            uart4_init
#define uartx_sendchar        uart4_sendchar
#define uartx_getchar         uart4_getchar
#define uartx_cbrx            uart4_cbrx
#define uartx_cbrxof          uart4_cbrxof
#include "uartx.h"
#endif

#if UART5_BAUDRATE > 0 && (GPIOX_PORTNUM(UART5_RX) >= GPIOX_PORTNUM_A || GPIOX_PORTNUM(UART5_TX) >= GPIOX_PORTNUM_A)
#define UARTX                 UART5
#define UARTX_IRQHandler      UART5_IRQHandler
#define UARTX_IRQn            UART5_IRQn
#define UARTX_CLOCLK_ON       RCC->APB1ENR |= RCC_APB1ENR_UART5EN;
#define UARTX_BRR_CALC        (SystemCoreClock >> rcc_dividetable[(RCC->CFGR & RCC_CFGR_PPRE1_Msk) >> RCC_CFGR_PPRE1_Pos]) / UART5_BAUDRATE
#define UARTX_RX              UART5_RX
#define UARTX_TX              UART5_TX
#define UARTX_REMAP           0
#define UARTX_MAPR
#define TXBUFX_SIZE           TXBUF5_SIZE
#define RXBUFX_SIZE           RXBUF5_SIZE
#define UARTX_PRINTF          UART5_PRINTF
#define uartx_inited          uart5_inited
#define txx_restart           tx5_restart
#define bufx_r                buf5_r
#define bufx_t                buf5_t
#define rbufx                 rbuf5
#define tbufx                 tbuf5
#define uartx_init            uart5_init
#define uartx_sendchar        uart5_sendchar
#define uartx_getchar         uart5_getchar
#define uartx_cbrx            uart5_cbrx
#define uartx_cbrxof          uart5_cbrxof
#include "uartx.h"
#endif
