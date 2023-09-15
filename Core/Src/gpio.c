/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, CTRL_EXT_EN_Pin|YL03_CTRL_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, S1_CTRL_Pin|SLP_M_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED_EXT_Pin|BI1_M_Pin|BI0_M_Pin|AI1_M_Pin
                          |AI0_M_Pin|BIN2_M_Pin|BIN1_M_Pin|AIN1_M_Pin
                          |AIN2_M_Pin|WDI_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, RST_M_Pin|FAN_CTRL_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PFPin PFPin */
  GPIO_InitStruct.Pin = CTRL_EXT_EN_Pin|YL03_CTRL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : PAPin PAPin */
  GPIO_InitStruct.Pin = S1_CTRL_Pin|SLP_M_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PAPin PAPin PAPin PAPin
                           PAPin PAPin */
  GPIO_InitStruct.Pin = YL02_Pin|START_Pin|CHK_Pin|YL01_Pin
                          |FAULT_M_Pin|FG_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin PBPin
                           PBPin PBPin PBPin PBPin
                           PBPin PBPin */
  GPIO_InitStruct.Pin = LED_EXT_Pin|BI1_M_Pin|BI0_M_Pin|AI1_M_Pin
                          |AI0_M_Pin|BIN2_M_Pin|BIN1_M_Pin|AIN1_M_Pin
                          |AIN2_M_Pin|WDI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = RST_M_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(RST_M_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = FAN_CTRL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(FAN_CTRL_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */
void ToggleWDI(void)
{
    HAL_GPIO_TogglePin(WDI_GPIO_Port, WDI_Pin);
}

GPIO_PinState getFGSta(void)
{
    return  HAL_GPIO_ReadPin(FG_GPIO_Port, FG_Pin);
}

//sta == 1 fan run
//sat == 0 fan stop
void setFanCtrl(uint8_t sta)
{
    GPIO_PinState pinSta;
    if(sta == 1)
        pinSta = GPIO_PIN_SET;
    else
        pinSta = GPIO_PIN_RESET;
    HAL_GPIO_WritePin(FAN_CTRL_GPIO_Port, FAN_CTRL_Pin, pinSta);
}

//sta == 1 set RST_M_Pin
//sat == 0 reset RST_M_Pin
void setResetMotor(uint8_t sta)
{
    GPIO_PinState pinSta;
    if(sta == 1)
        pinSta = GPIO_PIN_SET;
    else
        pinSta = GPIO_PIN_RESET;
    HAL_GPIO_WritePin(RST_M_GPIO_Port, RST_M_Pin, pinSta);
}

//sta == 1 set SLP_M_Pin
//sat == 0 reset SLP_M_Pin
void setSleepMotor(uint8_t sta)
{
    GPIO_PinState pinSta;
    if(sta == 1)
        pinSta = GPIO_PIN_SET;
    else
        pinSta = GPIO_PIN_RESET;
    HAL_GPIO_WritePin(SLP_M_GPIO_Port, SLP_M_Pin, pinSta);
}

GPIO_PinState getFaultMotorSta(void)
{
    return  HAL_GPIO_ReadPin(FAULT_M_GPIO_Port, FAULT_M_Pin);
}

void setCurrentMotor(uint8_t val)
{
    if(val == 0) {
          HAL_GPIO_WritePin(GPIOB, BI1_M_Pin|BI0_M_Pin|AI1_M_Pin
                          |AI0_M_Pin, GPIO_PIN_RESET);
    }
    else if(val == 30) {
          HAL_GPIO_WritePin(GPIOB, BI0_M_Pin|AI0_M_Pin, GPIO_PIN_SET);
          HAL_GPIO_WritePin(GPIOB, BI1_M_Pin|AI1_M_Pin, GPIO_PIN_RESET);
    }
    else if(val == 70) {
          HAL_GPIO_WritePin(GPIOB, BI1_M_Pin|AI1_M_Pin, GPIO_PIN_SET);
          HAL_GPIO_WritePin(GPIOB, BI0_M_Pin|AI0_M_Pin, GPIO_PIN_RESET);
    }
    else if(val == 100) {
          HAL_GPIO_WritePin(GPIOB, BI1_M_Pin|BI0_M_Pin|AI1_M_Pin
                          |AI0_M_Pin, GPIO_PIN_SET);
    }
}

void setPhaseMotor(uint8_t val)
{   
    if(val == 0) {
          HAL_GPIO_WritePin(GPIOB, AIN1_M_Pin|BIN1_M_Pin, GPIO_PIN_SET);
          HAL_GPIO_WritePin(GPIOB, AIN2_M_Pin|BIN2_M_Pin, GPIO_PIN_RESET);
    }
    else if(val == 1) {
          HAL_GPIO_WritePin(GPIOB, AIN1_M_Pin|BIN2_M_Pin, GPIO_PIN_SET);
          HAL_GPIO_WritePin(GPIOB, AIN2_M_Pin|BIN1_M_Pin, GPIO_PIN_RESET);
    }
    else if(val == 2) {
          HAL_GPIO_WritePin(GPIOB, AIN2_M_Pin|BIN2_M_Pin, GPIO_PIN_SET);
          HAL_GPIO_WritePin(GPIOB, AIN1_M_Pin|BIN1_M_Pin, GPIO_PIN_RESET);
    }
    else {
          HAL_GPIO_WritePin(GPIOB, AIN2_M_Pin|BIN1_M_Pin, GPIO_PIN_SET);
          HAL_GPIO_WritePin(GPIOB, AIN1_M_Pin|BIN2_M_Pin, GPIO_PIN_RESET);
    }
}
//sta == 1 set LED_EXT_Pin
//sat == 0 reset LED_EXT_Pin
void setExtLED(uint8_t sta)
{
    GPIO_PinState pinSta;
    if(sta == 1)
        pinSta = GPIO_PIN_SET;
    else
        pinSta = GPIO_PIN_RESET;
    HAL_GPIO_WritePin(LED_EXT_GPIO_Port, LED_EXT_Pin, pinSta);
}

GPIO_PinState getYL01Sta(void)
{
    return  HAL_GPIO_ReadPin(YL01_GPIO_Port, YL01_Pin);
}

GPIO_PinState getChkSta(void)
{
    return  HAL_GPIO_ReadPin(CHK_GPIO_Port, CHK_Pin);
}

GPIO_PinState getStartSta(void)
{
    return  HAL_GPIO_ReadPin(START_GPIO_Port, START_Pin);
}

GPIO_PinState getYL02Sta(void)
{
    return  HAL_GPIO_ReadPin(YL02_GPIO_Port, YL02_Pin);
}

//sta == 1 set S1_CTRL_Pin
//sat == 0 reset S1_CTRL_Pin
void setS1Ctrl(uint8_t sta)
{
    GPIO_PinState pinSta;
    if(sta == 1)
        pinSta = GPIO_PIN_SET;
    else
        pinSta = GPIO_PIN_RESET;
    HAL_GPIO_WritePin(S1_CTRL_GPIO_Port, S1_CTRL_Pin, pinSta);
}

//sta == 1 set YL03_CTRL_Pin
//sat == 0 reset YL03_CTRL_Pin
void setYL03Ctrl(uint8_t sta)
{
    GPIO_PinState pinSta;
    if(sta == 1)
        pinSta = GPIO_PIN_SET;
    else
        pinSta = GPIO_PIN_RESET;
    HAL_GPIO_WritePin(YL03_CTRL_GPIO_Port, YL03_CTRL_Pin, pinSta);
}

stINPUT_STA getAllInputSta(void)
{
    stINPUT_STA inputsta;
    inputsta.fg =  getFGSta();
    inputsta.faultM =  getFaultMotorSta();
    inputsta.chk =  getChkSta();
    inputsta.start = getStartSta();
    inputsta.yl02 =  getYL02Sta();
    inputsta.yl01 =  getYL01Sta();
    return inputsta;

}

/* USER CODE END 2 */
