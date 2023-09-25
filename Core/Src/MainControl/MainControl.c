/*****************************************************************************************************************************
 * \file   : MainControl.c    
 * \module : MainControl
 * \brief  : MainControl module  
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

/*****************************************************************************************************************************
 * Other Header File Inclusion
 ****************************************************************************************************************************/
#include "MainControl.h"
#include "../Scheduler/Task.h"
stINPUT_STA mInputSta = {GPIO_PIN_RESET};
stCOUNT mCount = {0};
stDOOR_STA mDoorSta = {HOME_POSITION, HOME_POSITION, UNCOMPLETE, UNCOMPLETE, HOLD, HOLD, 0, PHASE_0};
stKEY_STA mKeySta = {INVALID, UNCERTAIN, UNCERTAIN};
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

#pragma import(__use_no_semihosting)    //确保没有从C库链接使用半主机的函数，必须导入符号__use_no_semihosting
void _sys_exit(int x)                   //定义_sys_exit()以避免使用半主机模式
{
  x = x;
}
struct __FILE                           //标准库需要的支持函数
{
  int handle;
};
/* FILE is typedefed in stdio.h*/
FILE __stdout;
FILE __stdin;

/**
  * @brief     重定义fputc函数（重定向c库函数putchar、printf到USART1）
  * @param     ch - 字符
               *f - 文件指针
  * @retval    字符
  * @attention 不能放在中断中使用，具体可参考网上相关资料
  */


int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
  //while ((USART1->SR & UART_FLAG_TXE) == 0) {}  //等待数据发送完毕
	while ((USART1->ISR & UART_FLAG_TXE) == 0) {}  //等待数据发送完毕
  return ch;
}

void PrintfVersion(void)
{
	printf("Software Version: V1.00 20230920\r\n");

}
/*****************************************************************************************************************************
 * MainControl
 ****************************************************************************************************************************/
void MainControl(void)
{
	//do something
	mCount.delay10ms++;
	if(mInputSta.start == GPIO_PIN_RESET && mKeySta.nowKeySta != OPEN_DOOR) {	//有新的气感闭合信号
		mCount.key++;
		if(mCount.key > DELAY_150MS) {	 //150ms去抖
			mCount.key = 0;
			mKeySta.nextKeySta = OPEN_DOOR;
			mKeySta.isNewKeyCmd = TRUE;
			mCount.agingCheck = 0;
		}
	}
	else if(mInputSta.start == GPIO_PIN_SET && mKeySta.nowKeySta != CLOSE_DOOR)
	{
		mCount.key++;
		if(mCount.key > DELAY_150MS) {	 //150ms去抖
			mCount.key = 0;
			mKeySta.nextKeySta = CLOSE_DOOR;
			mKeySta.isNewKeyCmd = TRUE;
			mCount.agingCheck = 0;
		}
	}
	else{
		mCount.key = 0;
	}
	// if(mKeySta.isNewKeyCmd == TRUE && mDoorSta.toggleDirectionSta == UNCOMPLETE) {
	// 	mKeySta.isNewKeyCmd = FALSE;
	// 	mDoorSta.toggleDirectionSta = COMPLETE;
	// 	//Init variable
	// }
	if(mKeySta.nowKeySta == OPEN_DOOR) {	//闭合气感信号，要求开窗
		StartFan();
	}
	else {
		StopFan();
	}
	// switch (mRunSta)
	// {
	// 	case 3:
	// 		CloseWindows();		//关闭百叶窗
	// 		FAN_OFF;
	// 		windowsSta = CLOSEING;
	// 		fsm++;
	// 		fsmDelay = 0;
	// 		break;	
	// 	case 4:
	// 		fsmDelay++;
	// 		if(fsmDelay>DC_CURRENT_FSMDELAY)
	// 			fsm++;
	// 		break;	
	// 	case 5:
	// 			if(doorlimSta[0] == 1 && doorlimSta[1] == 1 && doorlimSta[2] == 1) {
	// 			fsmDelay = 0;
	// 			fsm = 11;
	// 		}
	// 		break;
	// 	case 7:
	// 		backward();			//打开百叶窗
	// 		FAN_ON;
	// 		windowsSta = OPENING;
	// 		fsm++;
	// 		fsmDelay = 0;
	// 		break;	
	// 	case 8:
	// 		fsmDelay++;
	// 		if(fsmDelay>DC_CURRENT_FSMDELAY)
	// 			fsm++;
	// 		break;
	// 	case 9:
	// 			if(doorlimSta[0] == 1 && doorlimSta[1] == 1 && doorlimSta[2] == 1) {
	// 			fsmDelay = 0;
	// 			fsm = 10;
	// 		}
	// 		break;
	// 	case 6:
	// 	case 10:
	// 	case 11:
	// 		stop();
	// 		break;
	// default:
	// 	break;
	// }
}
//风机输入端;低电平时间4us , 45us 一个周期 ，22KHZ  ，平时低电平
//直角边 53 斜边109
//FG 16MS 一个周期，50%占空比
void StartFan(void)
{

}

void StopFan(void)
{
	
}
/*****************************************************************************************************************************
 * END OF FILE: StepMotor.c
 ****************************************************************************************************************************/
