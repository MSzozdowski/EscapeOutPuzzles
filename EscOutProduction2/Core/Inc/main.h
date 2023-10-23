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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BUZZER_Pin GPIO_PIN_9
#define BUZZER_GPIO_Port GPIOB
#define ID_RES_Pin GPIO_PIN_1
#define ID_RES_GPIO_Port GPIOA
#define DFR_TX_Pin GPIO_PIN_2
#define DFR_TX_GPIO_Port GPIOA
#define DFR_RX_Pin GPIO_PIN_3
#define DFR_RX_GPIO_Port GPIOA
#define DBG_LED_Pin GPIO_PIN_1
#define DBG_LED_GPIO_Port GPIOB
#define DFP_BUSY_Pin GPIO_PIN_2
#define DFP_BUSY_GPIO_Port GPIOB
#define RELAY_Pin GPIO_PIN_9
#define RELAY_GPIO_Port GPIOA
#define CAP_SENS_NC_Pin GPIO_PIN_6
#define CAP_SENS_NC_GPIO_Port GPIOC
#define CAP_SENS_NO_Pin GPIO_PIN_10
#define CAP_SENS_NO_GPIO_Port GPIOA
#define BUTTON_LED_Pin GPIO_PIN_11
#define BUTTON_LED_GPIO_Port GPIOA
#define BTN_LED_LIGHT_Pin GPIO_PIN_12
#define BTN_LED_LIGHT_GPIO_Port GPIOA
#define REED_SW5_Pin GPIO_PIN_15
#define REED_SW5_GPIO_Port GPIOA
#define REED_SW4_Pin GPIO_PIN_3
#define REED_SW4_GPIO_Port GPIOB
#define REED_SW3_Pin GPIO_PIN_4
#define REED_SW3_GPIO_Port GPIOB
#define REED_SW2_Pin GPIO_PIN_5
#define REED_SW2_GPIO_Port GPIOB
#define REED_SW1_Pin GPIO_PIN_8
#define REED_SW1_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
