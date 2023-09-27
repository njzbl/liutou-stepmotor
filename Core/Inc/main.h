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
#define CTRL_EXT_EN_Pin GPIO_PIN_0
#define CTRL_EXT_EN_GPIO_Port GPIOF
#define YL03_CTRL_Pin GPIO_PIN_1
#define YL03_CTRL_GPIO_Port GPIOF
#define S1_CTRL_Pin GPIO_PIN_0
#define S1_CTRL_GPIO_Port GPIOA
#define YL02_Pin GPIO_PIN_4
#define YL02_GPIO_Port GPIOA
#define START_Pin GPIO_PIN_5
#define START_GPIO_Port GPIOA
#define CHK_Pin GPIO_PIN_6
#define CHK_GPIO_Port GPIOA
#define YL01_Pin GPIO_PIN_7
#define YL01_GPIO_Port GPIOA
#define LED_EXT_Pin GPIO_PIN_0
#define LED_EXT_GPIO_Port GPIOB
#define BI1_M_Pin GPIO_PIN_1
#define BI1_M_GPIO_Port GPIOB
#define BI0_M_Pin GPIO_PIN_2
#define BI0_M_GPIO_Port GPIOB
#define AI1_M_Pin GPIO_PIN_10
#define AI1_M_GPIO_Port GPIOB
#define AI0_M_Pin GPIO_PIN_11
#define AI0_M_GPIO_Port GPIOB
#define BIN2_M_Pin GPIO_PIN_12
#define BIN2_M_GPIO_Port GPIOB
#define BIN1_M_Pin GPIO_PIN_13
#define BIN1_M_GPIO_Port GPIOB
#define AIN1_M_Pin GPIO_PIN_14
#define AIN1_M_GPIO_Port GPIOB
#define AIN2_M_Pin GPIO_PIN_15
#define AIN2_M_GPIO_Port GPIOB
#define FAULT_M_Pin GPIO_PIN_8
#define FAULT_M_GPIO_Port GPIOA
#define SLP_M_Pin GPIO_PIN_9
#define SLP_M_GPIO_Port GPIOA
#define RST_M_Pin GPIO_PIN_6
#define RST_M_GPIO_Port GPIOC
#define FAN_CTRL_Pin GPIO_PIN_7
#define FAN_CTRL_GPIO_Port GPIOC
#define FG_Pin GPIO_PIN_10
#define FG_GPIO_Port GPIOA
#define FG_EXTI_IRQn EXTI4_15_IRQn
#define WDI_Pin GPIO_PIN_5
#define WDI_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
