#include "main.h"

typedef struct GPIO_Info LED;

struct GPIO_Info {
    GPIO_TypeDef *Bank;
    uint16_t Pin;
};

//use LED as indicator for received data
const LED LED0 = { .Bank = GPIOA, .Pin = LED0_PIN };
const LED LED1 = { .Bank = GPIOB, .Pin = LED1_PIN };

UART_HandleTypeDef UartHandle;

static void Error_Handler(void);
static void SystemClock_Config(void);
static void LED_GPIO_Init(const LED *led);
static void checkDMABuffer();

const size_t RXBUFSIZE = 4;
uint8_t rxBuffer[RXBUFSIZE];

int main(void) {

    HAL_Init();
    SystemClock_Config();

    __HAL_RCC_GPIOA_CLK_ENABLE(); //enable clock to GPIOA
    __HAL_RCC_GPIOB_CLK_ENABLE(); //enable clock to GPIOB

    LED_GPIO_Init(&LED0);
    LED_GPIO_Init(&LED1);

    UartHandle.Instance        = USART5;
    UartHandle.Init.BaudRate   = 9600;
    UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
    UartHandle.Init.StopBits   = UART_STOPBITS_1;
    UartHandle.Init.Parity     = UART_PARITY_NONE;
    UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
    UartHandle.Init.Mode       = UART_MODE_TX_RX;
    UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
    UartHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    if(HAL_UART_DeInit(&UartHandle) != HAL_OK) {
        Error_Handler();
    }  
    if(HAL_UART_Init(&UartHandle) != HAL_OK) {
        Error_Handler();
    }

    HAL_GPIO_WritePin(LED0.Bank, LED0.Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED1.Bank, LED1.Pin, GPIO_PIN_RESET);

    //send start message to test connection
    uint8_t txMessage[] = "Hello from STM32F030CCT6!\n";
    HAL_UART_Transmit(&UartHandle, txMessage, sizeof(txMessage)-1, 0x1FFFFFF); //do not transmit '\0'

    //simple mirror without interrupts or DMA
    while(1) {
        HAL_UART_Receive(&UartHandle, rxBuffer, 1, 0x1FFFFFF);
        HAL_UART_Transmit(&UartHandle, rxBuffer, 1, 0x1FFFFFF);
    }

    return 0;
}

static void SystemClock_Config(void) {
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;

    /* Activate PLL with HSI as source */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV2; //this is FIXED!!!
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12; //8MHz * 12 / 2 = 48MHz
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        while(1); //single stepping will get stuck here, indicating an error
    }

    /* Select PLL as system clock source and configure the HCLK, PCLK1 clocks dividers */
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    // RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
        while(1);
    }
}

static void Error_Handler(void) {
    while(1) {
        HAL_GPIO_TogglePin(LED1.Bank, LED1.Pin); //error LED
        HAL_Delay(500);
    }
}

static void LED_GPIO_Init(const LED *led) {
    GPIO_InitTypeDef GPIO_Init;
    GPIO_Init.Pin = led->Pin;
    GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Init.Pull = GPIO_PULLUP;
    GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(led->Bank, &GPIO_Init);
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle) {
    UNUSED(UartHandle);
    Error_Handler();
}