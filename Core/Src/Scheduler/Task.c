/*****************************************************************************************************************************
 * \file   : Task.c    
 * \module : Task
 * \brief  : Task module  
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
#include "Task.h"
#include "Sch.h"

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
 *                                                                  Function Source code
 ****************************************************************************************************************************/


/*****************************************************************************************************************************
 * Task_Init
 ****************************************************************************************************************************/
void Task_Init(void)
{
	//do something
	SCH_Delete_Task(0);
}


/*****************************************************************************************************************************
 * Task_1ms
 ****************************************************************************************************************************/
/*!
 * \brief     : 357.1us Periodic task 
 * \param[in] : void
 * \return    : void
 * \see
 * \note
 *
 */
void Task_Step_Ctrl(void)
{
	StepMotorCtrl();
}

/*****************************************************************************************************************************
 * Task_10ms
 *****************************************************************************************************************************/
/*!
 * \brief : 10ms Periodic task
 * \param[in]
 * \param[out]
 * \return
 * \see
 * \note
 *	ACC DEC阶段，不用相应新的按键命令，等待ACC 	DEC结束再响应
 */
void Task_10ms(void)
{	
	MainControl();
}

/*****************************************************************************************************************************
 * Task_200ms
 ****************************************************************************************************************************/
/*!
 * \brief :200ms Periodic task
 * \param[in]
 * \param[out]
 * \return
 * \see
 * \note
 *
 */
void Task_200ms(void)
{
	ToggleWDI();
}


/*****************************************************************************************************************************
 * END OF FILE: Task.c
 ****************************************************************************************************************************/
