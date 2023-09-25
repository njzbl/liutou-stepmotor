/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "main.h"

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
typedef struct INPUT_STA
{
  GPIO_PinState fg;
  GPIO_PinState faultM;
  GPIO_PinState chk;
  GPIO_PinState start;
  GPIO_PinState yl01;
  GPIO_PinState yl02;
}stINPUT_STA;


void ToggleWDI(void);
GPIO_PinState getFGSta(void);
void setFanCtrl(uint8_t sta);
void setResetMotor(uint8_t sta);
void setSleepMotor(uint8_t sta);
GPIO_PinState getFaultMotorSta(void);
void setCurrentMotor(uint8_t val);
void setPhaseMotor(uint8_t val);
void setExtLED(uint8_t sta);
GPIO_PinState getYL01Sta(void);
GPIO_PinState getChkSta(void);
GPIO_PinState getStartSta(void);
GPIO_PinState getYL02Sta(void);
void setS1Ctrl(uint8_t sta);
void setYL03Ctrl(uint8_t sta);
void setExt24VCtrl(uint8_t sta);
stINPUT_STA getAllInputSta(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

