#ifndef __MAIN_H
#define __MAIN_H

#include <stm32f0xx.h>
#include <stm32f0xx_hal.h>

#define LED0_PIN    GPIO_PIN_7
#define LED1_PIN    GPIO_PIN_0

#define UART_GPIO_BANK  GPIOB
#define UART_TX_PIN     GPIO_PIN_3 //PB3
#define UART_RX_PIN     GPIO_PIN_4 //PB4
#define UART_TX_AF      GPIO_AF4_USART5 //AF4, see datasheet table 12
#define UART_RX_AF      GPIO_AF4_USART5

//ref. manual 10.3.2
#define UART_TX_DMA_CHANNEL     DMA1_Channel2
#define UART_RX_DMA_CHANNEL     DMA1_Channel3
#define UART_DMA_IRQn           DMA1_Channel2_3_IRQn
#define UART_DMA_IRQHandler     DMA1_Channel2_3_IRQHandler

#define UART_IRQn               USART3_6_IRQn
#define UART_IRQHandler         USART3_6_IRQHandler

#endif /* __MAIN_H */
