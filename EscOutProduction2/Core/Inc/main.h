/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BUZZER_Pin GPIO_PIN_9
#define BUZZER_GPIO_Port GPIOB
#define RELAY_Pin GPIO_PIN_14
#define RELAY_GPIO_Port GPIOC
#define USER_BUTTON_Pin GPIO_PIN_15
#define USER_BUTTON_GPIO_Port GPIOC
#define POTENTIOMER_OUT_Pin GPIO_PIN_0
#define POTENTIOMER_OUT_GPIO_Port GPIOA
#define PIEZO_SENS_Pin GPIO_PIN_1
#define PIEZO_SENS_GPIO_Port GPIOA
#define ANALOG_SENS_OUT_Pin GPIO_PIN_2
#define ANALOG_SENS_OUT_GPIO_Port GPIOA
#define DEBUG_LED_Pin GPIO_PIN_1
#define DEBUG_LED_GPIO_Port GPIOB
#define CAP_SENS_NC_Pin GPIO_PIN_5
#define CAP_SENS_NC_GPIO_Port GPIOB
#define CAP_SENS_NO_Pin GPIO_PIN_6
#define CAP_SENS_NO_GPIO_Port GPIOB
#define BIG_PUSH_LED_Pin GPIO_PIN_7
#define BIG_PUSH_LED_GPIO_Port GPIOB
#define BIG_PUSH_BTN_Pin GPIO_PIN_8
#define BIG_PUSH_BTN_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
