/*****************************************************************************************************************************
 * \file   : MainControl.c    
 * \module : MainControl
 * \brief  : MainControl module  
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

/*****************************************************************************************************************************
 * Other Header File Inclusion
 ****************************************************************************************************************************/
#include "MainControl.h"
#include "../Scheduler/Task.h"
stINPUT_STA mInputSta = {GPIO_PIN_RESET};
stCOUNT mCount = {0};
uint8_t mNewKeyCmd = 0;
uint8_t mKeyStatus = 0;
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
 * Static Local Variables Declaration
 ****************************************************************************************************************************/

/*****************************************************************************************************************************
 * Table Constant Definition
 ****************************************************************************************************************************/

/*****************************************************************************************************************************
 * Static Local Functions Declaration
 ****************************************************************************************************************************/


/*****************************************************************************************************************************
 *                                                                  Function Source code
 ****************************************************************************************************************************/


/*****************************************************************************************************************************
 * StepMotorCtrl
 ****************************************************************************************************************************/
void MainControl(void)
{
	//do something
	mCount.delay10ms++;
	mInputSta = getAllInputSta();
	if(mInputSta.start == GPIO_PIN_RESET && mKeyStatus != 0) {	//有新的气感闭合信号
		mCount.key++;
		if(mCount.key > 15) {	 //150ms去抖
			mCount.key = 0;
			mKeyStatus = 0;
			mNewKeyCmd = 1;
			mCount.agingTest = 0;
		}
	}
	else if(mInputSta.start == GPIO_PIN_SET && mKeyStatus != 1)
	{
		mCount.key++;
		if(mCount.key > 15) {	 //150ms去抖
			mCount.key = 0;
			mKeyStatus = 1;
			mNewKeyCmd = 1;
			mCount.agingTest = 0;
		}
	}
	else{
		mCount.key = 0;
	}
	if(mNewKeyCmd == 1) {
		mNewKeyCmd = 0;
	}
	if(mKeyStatus == 0) {
		
	}
	else {

	}
	switch (mRunSta)
	{
		case 3:
			CloseWindows();		//关闭百叶窗
			FAN_OFF;
			windowsSta = CLOSEING;
			fsm++;
			fsmDelay = 0;
			break;	
		case 4:
			fsmDelay++;
			if(fsmDelay>DC_CURRENT_FSMDELAY)
				fsm++;
			break;	
		case 5:
				if(doorlimSta[0] == 1 && doorlimSta[1] == 1 && doorlimSta[2] == 1) {
				fsmDelay = 0;
				fsm = 11;
			}
			break;
		case 7:
			backward();			//打开百叶窗
			FAN_ON;
			windowsSta = OPENING;
			fsm++;
			fsmDelay = 0;
			break;	
		case 8:
			fsmDelay++;
			if(fsmDelay>DC_CURRENT_FSMDELAY)
				fsm++;
			break;
		case 9:
				if(doorlimSta[0] == 1 && doorlimSta[1] == 1 && doorlimSta[2] == 1) {
				fsmDelay = 0;
				fsm = 10;
			}
			break;
		case 6:
		case 10:
		case 11:
			stop();
			break;
	default:
		break;
	}
}
/*****************************************************************************************************************************
 * END OF FILE: StepMotor.c
 ****************************************************************************************************************************/
