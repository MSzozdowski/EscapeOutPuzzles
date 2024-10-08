/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "defs.h"
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
#define DEBUG_LED_Pin GPIO_PIN_0
#define DEBUG_LED_GPIO_Port GPIOA
#define LCD_A0_LEFT_Pin GPIO_PIN_3
#define LCD_A0_LEFT_GPIO_Port GPIOA
#define LCD_RST_LEFT_Pin GPIO_PIN_4
#define LCD_RST_LEFT_GPIO_Port GPIOA
#define LCD_CS_LEFT_Pin GPIO_PIN_5
#define LCD_CS_LEFT_GPIO_Port GPIOA
#define LCD_A0_RIGHT_Pin GPIO_PIN_6
#define LCD_A0_RIGHT_GPIO_Port GPIOA
#define LCD_RST_RIGHT_Pin GPIO_PIN_7
#define LCD_RST_RIGHT_GPIO_Port GPIOA
#define LCD_CS_RIGHT_Pin GPIO_PIN_0
#define LCD_CS_RIGHT_GPIO_Port GPIOB
#define LCD_PWR_LEFT_Pin GPIO_PIN_1
#define LCD_PWR_LEFT_GPIO_Port GPIOB
#define RELAY_Pin GPIO_PIN_2
#define RELAY_GPIO_Port GPIOB
#define CAP_SENS_NC_Pin GPIO_PIN_8
#define CAP_SENS_NC_GPIO_Port GPIOA
#define CAP_SENS_NO_Pin GPIO_PIN_9
#define CAP_SENS_NO_GPIO_Port GPIOA
#define LCD_PWR_RIGHT_Pin GPIO_PIN_6
#define LCD_PWR_RIGHT_GPIO_Port GPIOC
#define LOCK_STATE_Pin GPIO_PIN_10
#define LOCK_STATE_GPIO_Port GPIOA
#define MCU_SEL1_Pin GPIO_PIN_15
#define MCU_SEL1_GPIO_Port GPIOA
#define MCU_SEL2_Pin GPIO_PIN_3
#define MCU_SEL2_GPIO_Port GPIOB
#define MCU_SEL3_Pin GPIO_PIN_4
#define MCU_SEL3_GPIO_Port GPIOB
#define MCU_SEL4_Pin GPIO_PIN_5
#define MCU_SEL4_GPIO_Port GPIOB
#define RS_485_EN_Pin GPIO_PIN_8
#define RS_485_EN_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
