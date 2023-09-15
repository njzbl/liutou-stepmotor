/*****************************************************************************************************************************
 * \file   : Sch.c   
 * \module : Sch 
 * \brief  : task scheduler   
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
 * Other header files
 * **************************************************************************************************************************/
#include "tim.h"
#include "Sch.h"
#include "Task.h"

/*****************************************************************************************************************************
 * Local Variables Declaration
 ****************************************************************************************************************************/
static Task_ObjType SCH_TASKS_G[SCH_MAX_TASKS];

/*****************************************************************************************************************************
 * Global variables definition
 ****************************************************************************************************************************/


/*****************************************************************************************************************************
 * Static Local Function decalaration property
 ****************************************************************************************************************************/

/*****************************************************************************************************************************
 * Function definition
 ****************************************************************************************************************************/

/*****************************************************************************************************************************
 ** Function Name         : SCH_Init
 **
 ** Service ID            : 0x01
 **
 ** Description           : This is a Scheduler initial function
 **
 ****************************************************************************************************************************/
void SCH_Init(void)
{
    uint8_t index;
    
    for ( index = 0U; index < SCH_MAX_TASKS; index++ ) {
        SCH_Delete_Task(index);
    }
    (void)SCH_Add_Task(Task_Init, TASK_INIT_DELAY, TASK_INIT_PERIOD);
    (void)SCH_Add_Task(Task_Step_Ctrl,    TASK0_DELAY, TASK0_PERIOD);
    (void)SCH_Add_Task(Task_10ms,    TASK1_DELAY, TASK1_PERIOD);
    (void)SCH_Add_Task(Task_200ms,   TASK2_DELAY, TASK2_PERIOD);
}

/*****************************************************************************************************************************
 ** Function Name         : SCH_Start
 **
 ** Service ID            : 0x02
 **
 ** Description           : This is a Scheduler statrt function
 **
 ****************************************************************************************************************************/
void SCH_Start(void)
{
	/*1ms interrupt*/
    if (HAL_TIM_Base_Start_IT(&htim14) != HAL_OK)//start TIM14
    {
        Error_Handler();
    }
}

/*****************************************************************************************************************************
 ** Function Name         : SCH_Update
 **
 ** Service ID            : 0x03
 **
 ** Description           : This is a Scheduler update function,
 **
 ****************************************************************************************************************************/
void SCH_Update(void)
{
    uint8_t i;

    for ( i = 0U; i < SCH_MAX_TASKS; i++ ) 
    {
        if ( SCH_TASKS_G[i].pTask != (void (*)(void))0U ) 
        {
            if ( SCH_TASKS_G[i].DelayTime > 0U ) 
            {
                SCH_TASKS_G[i].DelayTime--;
            }
            if ( SCH_TASKS_G[i].DelayTime == 0U )
            {
                SCH_TASKS_G[i].Runtimes = 1U;
                SCH_TASKS_G[i].DelayTime = SCH_TASKS_G[i].Period;
            }
        }
    }
}

/*****************************************************************************************************************************
 ** Function Name         : SCH_Add_Task
 **
 ** Service ID            : 0x04
 **
 ** Description           : This is a Scheduler add task function
 **
 ****************************************************************************************************************************/
uint32_t SCH_Add_Task(void(*TaskPtr)(void), uint32_t TaskDelay,  uint32_t TaskPeriod)
{
    uint8_t TaskID = 0U;
    
    while( (TaskID < SCH_MAX_TASKS) && (SCH_TASKS_G[TaskID].pTask != (void (*)(void))0U) ) {
        TaskID++;
    }
    
    if ( TaskID < SCH_MAX_TASKS ) {
        SCH_TASKS_G[TaskID].pTask        = TaskPtr;
        SCH_TASKS_G[TaskID].DelayTime    = TaskDelay;
        SCH_TASKS_G[TaskID].Period       = TaskPeriod;
        SCH_TASKS_G[TaskID].Runtimes     = 0U;
    }
    return TaskID;
}

/*****************************************************************************************************************************
 ** Function Name         : SCH_Dispatch_Tasks
 **
 ** Service ID            : 0x05
 **
 ** Description           : This is a Scheduler dispatch function
 **
 ****************************************************************************************************************************/
void SCH_Dispatch_Tasks(void)
{
    uint8_t i;

    for ( i = 0U; i < SCH_MAX_TASKS; i++ ) {
        if ( SCH_TASKS_G[i].Runtimes > 0U ) {
            if ( SCH_TASKS_G[i].pTask != (void (*)(void))0U ) {
                SCH_TASKS_G[i].pTask();
            }
            SCH_TASKS_G[i].Runtimes = 0U;
        }
    }
}

/*****************************************************************************************************************************
 ** Function Name         : SCH_Delete_Task
 **
 ** Service ID            : 0x06
 **
 ** Description           : 
 **
 ****************************************************************************************************************************/
void SCH_Delete_Task(uint32_t TaskID)
{
    if ( SCH_TASKS_G[TaskID].pTask != (void (*)(void))0U ) {
        SCH_TASKS_G[TaskID].DelayTime   = 0U;
        SCH_TASKS_G[TaskID].Period      = 0U;
        SCH_TASKS_G[TaskID].Runtimes    = 0U;
        SCH_TASKS_G[TaskID].pTask       = (void (*)(void))0U;
    }
}

/*****************************************************************************************************************************
 ** Function Name         : SCH_GetTaskRuntimes
 **
 ** Service ID            : 0x07
 **
 ** Description           : 
 **
 ****************************************************************************************************************************/
uint32_t SCH_GetTaskRuntimes(uint32_t TaskID)
{
    return SCH_TASKS_G[TaskID].Runtimes;
}
/*****************************************************************************************************************************
 * END OF FILE: Sch.c
 ****************************************************************************************************************************/

