# ST7565 3-inch chip-on-glass LCD display library for STM32Cube

## Getting started (example)
Step #1:
In common_cog.h include file (for example):
```
#ifndef COMMON_COG_H
#define COMMON_COG_H

/* SPI */
#define SPI_PORT hspi1

/* GPIO */
#define cog_port GPIOA
#define COG_GPIO_CLK_ENABLE()                  __HAL_RCC_GPIOA_CLK_ENABLE()
#define cog_RS GPIO_PIN_8
#define cog_RST GPIO_PIN_9
#define cog_CS GPIO_PIN_10

#endif // COMMON_COG_H
```

Step 2:
spi.h:
```
#ifndef SPI_H
#define SPI_H

#include "stm32f4xx_hal.h"

#include "common_cog.h"

 void spi_init(void);

#endif // SPI_H
```

spi.c:
```
#include "spi.h"

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef SPI_PORT;

/* Private function prototypes -----------------------------------------------*/
// void SystemClock_Config(void);
static void MX_SPI1_Init(void);

void spi_init(void) {

  MX_SPI1_Init();

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    // Error_Handler();
  }
}

/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void) // probably not necessary
{

  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();

  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_0);

  /* System interrupt init*/
}

/**
* @brief SPI MSP Initialization
* This function configures the hardware resources used in this example
* @param hspi: SPI handle pointer
* @retval None
*/
void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(hspi->Instance==SPI1)
  {
    /* Peripheral clock enable */
    __HAL_RCC_SPI1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**SPI1 GPIO Configuration
    PA5     ------> SPI1_SCK
    PA7     ------> SPI1_MOSI
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  }

}

// /**
//   * @brief  This function is executed in case of error occurrence.
//   * @retval None
//   */
// void Error_Handler(void)
// {
//   /* USER CODE BEGIN Error_Handler_Debug */
//   /* User can add his own implementation to report the HAL error return state */
//   __disable_irq();
//   while (1)
//   {
//   }
//   /* USER CODE END Error_Handler_Debug */
// }
```

Step #3:
In main():
```
  spi_init();
  ST7565_init();

  char str1[] = "How";
  ST7565_drawstring_anywhere((LCD_WIDTH/2)-((strlen(str1)/2)*6), (LCD_HEIGHT*3/3)-15, str1);
  char str2[] = "much";
  ST7565_drawstring_anywhere((LCD_WIDTH/2)-((strlen(str2)/2)*6),  (LCD_HEIGHT*2/3)-15, str2);
  char str3[] = "wood";
  ST7565_drawstring_anywhere((LCD_WIDTH/2)-((strlen(str3)/2)*6),  (LCD_HEIGHT/3)-15, str3);

  //ST7565_drawstring(0,0, "How much wood would a woodchuck chuck if a woodchuck could chuck wood?	");

  updateDisplay();
```
