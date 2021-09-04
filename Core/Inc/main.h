/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define AD_DOUT_Pin GPIO_PIN_6
#define AD_DOUT_GPIO_Port GPIOA
#define AD_DIN_Pin GPIO_PIN_7
#define AD_DIN_GPIO_Port GPIOA
#define AD_CS_Pin GPIO_PIN_0
#define AD_CS_GPIO_Port GPIOB
#define AD_RESET_Pin GPIO_PIN_9
#define AD_RESET_GPIO_Port GPIOA
#define DIMMER_ZERO_Pin GPIO_PIN_6
#define DIMMER_ZERO_GPIO_Port GPIOC
#define DIMMER_ZERO_EXTI_IRQn EXTI4_15_IRQn
#define AD_DRDY_Pin GPIO_PIN_7
#define AD_DRDY_GPIO_Port GPIOC
#define AD_DRDY_EXTI_IRQn EXTI4_15_IRQn
#define DIMMER1_Pin GPIO_PIN_8
#define DIMMER1_GPIO_Port GPIOC
#define DS18B20_Pin GPIO_PIN_1
#define DS18B20_GPIO_Port GPIOD
#define AD_SCK_Pin GPIO_PIN_3
#define AD_SCK_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
