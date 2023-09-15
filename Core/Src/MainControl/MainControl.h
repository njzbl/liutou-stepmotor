/*****************************************************************************************************************************
 * \file   : MainControl.h    
 * \module : MainControl
 * \brief  : 
 * \project: NEO-180160-SM
 * \author : ZBL
 *============================================================================================================================
 *                                                   Revision control History
 *============================================================================================================================
 * V1.0.0: 2023-09-01: Initial Version
 *
 *
 *
 ****************************************************************************************************************************/
#ifndef MAINCONTROL_H
#define	MAINCONTROL_H

/*****************************************************************************************************************************
 * Other Header File Inclusion 
 ****************************************************************************************************************************/
#include "stm32g0xx_hal.h"
#include "gpio.h"

typedef struct COUNT
{
  uint32_t delay10ms;
  uint32_t key;
  uint32_t agingTest;
}stCOUNT;
/*****************************************************************************************************************************
 * Compile Option or configuration Section (for/debug)                                                
 ****************************************************************************************************************************/

/*****************************************************************************************************************************
 * Macro Definition
 ****************************************************************************************************************************/

/*****************************************************************************************************************************
 * Enumeration Definition
 ****************************************************************************************************************************/

/*****************************************************************************************************************************
 * Typedef Definition
 ****************************************************************************************************************************/

/*****************************************************************************************************************************
 * Table Definition
 ****************************************************************************************************************************/

/*****************************************************************************************************************************
 * Global Function Prototypes
 ****************************************************************************************************************************/
extern stINPUT_STA mInputSta = {GPIO_PIN_RESET};
extern stCOUNT mCount = {0};
extern uint8_t mNewKeyCmd = 0;
extern uint8_t mKeyStatus = 0;
extern void MainControl(void);

#endif
/*****************************************************************************************************************************
 * END OF FILE: StepMotor.h
 ****************************************************************************************************************************/