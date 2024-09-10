/**
  ******************************************************************************
  * @file    Templates/Src/stm32f0xx_hal_msp.c
  * @author  MCD Application Team
  * @brief   HAL MSP module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup HAL_MSP_Private_Functions
  * @{
  */

/**
  * @brief  Initializes the Global MSP.
  * @param  None
  * @retval None
  */
void HAL_MspInit(void)
{
 
}

/**
  * @brief  DeInitializes the Global MSP.
  * @param  None  
  * @retval None
  */
void HAL_MspDeInit(void)
{

}

/**
  * @brief  Initializes the PPP MSP.
  * @param  None
  * @retval None
  */
//void HAL_PPP_MspInit(void)
//{
 
//}

/**
  * @brief  DeInitializes the PPP MSP.
  * @param  None  
  * @retval None
  */
//void HAL_PPP_MspDeInit(void)
//{

//}

void HAL_UART_MspInit(UART_HandleTypeDef *uart_handle) { 

    static DMA_HandleTypeDef dmaHandle_TX;
    static DMA_HandleTypeDef dmaHandle_RX;
    GPIO_InitTypeDef  GPIO_Init;

    __HAL_RCC_GPIOB_CLK_ENABLE(); //for TX and RX pins
    __HAL_RCC_USART5_CLK_ENABLE(); 

    GPIO_Init.Pin       = UART_TX_PIN;
    GPIO_Init.Mode      = GPIO_MODE_AF_PP;
    GPIO_Init.Pull      = GPIO_PULLUP;
    GPIO_Init.Speed     = GPIO_SPEED_FREQ_HIGH;
    GPIO_Init.Alternate = UART_TX_AF;

    //setup TX pin
    HAL_GPIO_Init(UART_GPIO_BANK, &GPIO_Init);

    GPIO_Init.Pin = UART_RX_PIN;
    GPIO_Init.Alternate = UART_RX_AF;

    //setup RX pin with similar settings
    HAL_GPIO_Init(UART_GPIO_BANK, &GPIO_Init);

    //DMA configuration is supposed to happen here as well
    // __HAL_RCC_DMA1_CLK_ENABLE();

    // //setup first DMA channel for: RX-Pin -> Memory
    // //circular mode so that RX DMA is running continously -> have to check buffer either periodically
    // //or with fill-status (half-done, done) interrupts
    // dmaHandle_RX.Instance                   = UART_RX_DMA_CHANNEL;
    // dmaHandle_RX.Init.Direction             = DMA_PERIPH_TO_MEMORY;
    // dmaHandle_RX.Init.PeriphInc             = DMA_PINC_DISABLE;
    // dmaHandle_RX.Init.MemInc                = DMA_MINC_ENABLE;
    // dmaHandle_RX.Init.PeriphDataAlignment   = DMA_PDATAALIGN_BYTE;
    // dmaHandle_RX.Init.MemDataAlignment      = DMA_MDATAALIGN_BYTE;
    // dmaHandle_RX.Init.Mode                  = DMA_CIRCULAR;
    // dmaHandle_RX.Init.Priority              = DMA_PRIORITY_HIGH;

    // HAL_DMA_Init(&dmaHandle_RX);
    // __HAL_LINKDMA(uart_handle, hdmarx, dmaHandle_RX); //link to DMA handle in USART handle

    // //setup second DMA channel for: Memory -> TX-Pin
    // //mode is normal since we only transfer occasionally
    // dmaHandle_TX.Instance                   = UART_TX_DMA_CHANNEL;
    // dmaHandle_TX.Init.Direction             = DMA_MEMORY_TO_PERIPH;
    // dmaHandle_TX.Init.PeriphInc             = DMA_PINC_DISABLE;
    // dmaHandle_TX.Init.MemInc                = DMA_MINC_ENABLE;
    // dmaHandle_TX.Init.PeriphDataAlignment   = DMA_PDATAALIGN_BYTE;
    // dmaHandle_TX.Init.MemDataAlignment      = DMA_MDATAALIGN_BYTE;
    // dmaHandle_TX.Init.Mode                  = DMA_NORMAL;
    // dmaHandle_TX.Init.Priority              = DMA_PRIORITY_HIGH;

    // HAL_DMA_Init(&dmaHandle_TX);
    // __HAL_LINKDMA(uart_handle, hdmatx, dmaHandle_TX); //link to DMA handle in USART handle

    // //remap DMA channels to work with USART5
    // __HAL_DMA1_REMAP(HAL_DMA1_CH2_USART5_TX);
    // __HAL_DMA1_REMAP(HAL_DMA1_CH3_USART5_RX);

    // //setup DMA interrupts
    // HAL_NVIC_SetPriority(UART_DMA_IRQn, 0, 0);
    // HAL_NVIC_EnableIRQ(UART_DMA_IRQn);

    // //enable UART interrupts

    // __HAL_USART_ENABLE_IT(uart_handle, USART_IT_IDLE);

    // HAL_NVIC_SetPriority(UART_IRQn, 1, 0);
    // HAL_NVIC_EnableIRQ(UART_IRQn);

}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
