/*****************************************************************************************************************************
 * \file   : MainControl.h    
 * \module : MainControl
 * \brief  : 
 * \project: NEO-180160-SM
 * \author : ZBL
 *============================================================================================================================
 *                                                   Revision control History
 *============================================================================================================================
 * V1.0.0: 2023-09-19: Initial Version
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
#include "usart.h"
#include "string.h"
#include "stdarg.h"
#include "stdio.h"

/*****************************************************************************************************************************
 * Compile Option or configuration Section (for/debug)                                                
 ****************************************************************************************************************************/

/*****************************************************************************************************************************
 * Macro Definition
 ****************************************************************************************************************************/
#define OPEN_DOOR                       0
#define CLOSE_DOOR                      1
#define UNCERTAIN                       2

#define INVALID                         0
#define VALID                           1

#define TRUE                            1
#define FALSE                           0

#define RUN                             1
#define STOP                            0

#define DELAY_150MS                     15
#define HOME_POSITION                   0
#define FARTHEST_POSITION               1470//55°     1253  //47°      1120  //42°  1066  // 40°     770   //29°    0xf460 


/*****************************************************************************************************************************
 * Enumeration Definition
 ****************************************************************************************************************************/

/*****************************************************************************************************************************
 * Typedef Definition
 ****************************************************************************************************************************/
typedef struct COUNT
{
  uint32_t delay10ms;
  uint32_t key;
  uint32_t agingCheck;
  uint32_t motor;
  uint32_t fan;
}stCOUNT;

typedef struct DOOR_STA
{
  uint16_t nowDoorPosition;
  uint16_t nextDoorPosition;
  uint8_t toggleDirSta;   //正向反向运动切换完成的标志 //toggleDirection
  uint8_t toggleDirPreSta;   //正向反向运动切换预处理的标志
  uint8_t runSta;               //open or close
  uint8_t speedSta;             //ACC DEC HOLD ,上电默认是HOLD，然后根据按键来运动
  uint8_t slowStep;             //ACC DEC 的步数
  uint8_t phase;                //当前的相位
}stDOOR_STA;

typedef struct KEY_STA
{
  uint8_t isNewKeyCmd;
  uint8_t nowKeySta;
  uint8_t nextKeySta;
}stKEY_STA;

/*****************************************************************************************************************************
 * Table Definition
 ****************************************************************************************************************************/

/*****************************************************************************************************************************
 * Global Function Prototypes
 ****************************************************************************************************************************/
extern stINPUT_STA mInputSta;
extern stCOUNT mCount;
extern stDOOR_STA mDoorSta;
extern stKEY_STA mKeySta;

extern void PrintfVersion(void);
extern void MainControl(void);
extern void FanCtrl(void);
extern void StartFan(void);
extern void StopFan(void);
#endif
/*****************************************************************************************************************************
 * END OF FILE: StepMotor.h
 ****************************************************************************************************************************/
