/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for CalcTask */
osThreadId_t CalcTaskHandle;
const osThreadAttr_t CalcTask_attributes = {
  .name = "CalcTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 256 * 4
};
/* Definitions for AD7705Task */
osThreadId_t AD7705TaskHandle;
const osThreadAttr_t AD7705Task_attributes = {
  .name = "AD7705Task",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 128 * 4
};
/* Definitions for AD7705Queue */
osMessageQueueId_t AD7705QueueHandle;
const osMessageQueueAttr_t AD7705Queue_attributes = {
  .name = "AD7705Queue"
};
/* Definitions for DRDYSem */
osSemaphoreId_t DRDYSemHandle;
const osSemaphoreAttr_t DRDYSem_attributes = {
  .name = "DRDYSem"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartCalcTask(void *argument);
void StartAD7705Task(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of DRDYSem */
  DRDYSemHandle = osSemaphoreNew(1, 1, &DRDYSem_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of AD7705Queue */
  AD7705QueueHandle = osMessageQueueNew (1, sizeof(uint16_t), &AD7705Queue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of CalcTask */
  CalcTaskHandle = osThreadNew(StartCalcTask, NULL, &CalcTask_attributes);

  /* creation of AD7705Task */
  AD7705TaskHandle = osThreadNew(StartAD7705Task, NULL, &AD7705Task_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartCalcTask */
/**
  * @brief  Function implementing the CalcTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartCalcTask */
void StartCalcTask(void *argument)
{
  /* USER CODE BEGIN StartCalcTask */
	uint16_t t_ad_ish;
  /* Infinite loop */
  for(;;)
  {
	  osMessageQueueGet(AD7705QueueHandle, &t_ad_ish, 0, osWaitForever);
	  printf("Therm AD7705 ish: %i \n\r", t_ad_ish);
	  osDelay(500);
  }
  /* USER CODE END StartCalcTask */
}

/* USER CODE BEGIN Header_StartAD7705Task */
/**
* @brief Function implementing the AD7705Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartAD7705Task */
void StartAD7705Task(void *argument)
{
  /* USER CODE BEGIN StartAD7705Task */
  /* Infinite loop */
  for(;;)
  {
	  if (osSemaphoreAcquire(DRDYSemHandle, osWaitForever) == osOK){
		  uint16_t t_ad_ish = readADResult(CHN_AIN1);
	  	 osMessageQueuePut(AD7705QueueHandle, &t_ad_ish, 0, osWaitForever);
	  	 }
	  osDelay(1);
  }
  /* USER CODE END StartAD7705Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == AD_DRDY_Pin) {
		osSemaphoreRelease(DRDYSemHandle);
	}
}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
