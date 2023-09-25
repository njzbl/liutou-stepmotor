/*****************************************************************************************************************************
 * \file   : StepMotor.c    
 * \module : StepMotor
 * \brief  : StepMotor module  
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
#include "StepMotor.h"

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
const uint8_t PhaseTable[17] = {ACC_STEP_0,ACC_STEP_1,ACC_STEP_2,ACC_STEP_3,ACC_STEP_4,ACC_STEP_5,ACC_STEP_6,ACC_STEP_7,
                     CONST_STEP,DEC_STEP_0,DEC_STEP_1,DEC_STEP_2,DEC_STEP_3,DEC_STEP_4,DEC_STEP_5,DEC_STEP_6,DEC_STEP_7};

/*****************************************************************************************************************************
 * Static Local Functions Declaration
 ****************************************************************************************************************************/


/*****************************************************************************************************************************
 *                                                                  Function Source code
 ****************************************************************************************************************************/


/*****************************************************************************************************************************
 *                                                                  Function Source code
 ****************************************************************************************************************************/

 void RunOnePhase(void)
 {
	if(mDoorSta.runSta == OPEN_DOOR) {  //正向
		mDoorSta.phase++;
		mDoorSta.nowDoorPosition++;
		mDoorSta.phase = mDoorSta.phase & PHASE_MAX;
		// printf("mDoorSta.phase++,now,next == %d,%d,%d\r\n",mDoorSta.phase,mDoorSta.nowDoorPosition,mDoorSta.nextDoorPosition);

	}
	else if(mDoorSta.runSta == CLOSE_DOOR) {//反向
		mDoorSta.phase--;
		if(mDoorSta.nowDoorPosition > 0)
			mDoorSta.nowDoorPosition--;
		mDoorSta.phase = mDoorSta.phase & PHASE_MAX;
		// printf("mDoorSta.phase--,now,next == %d,%d,%d\r\n",mDoorSta.phase,mDoorSta.nowDoorPosition,mDoorSta.nextDoorPosition);
	}
	else {
		printf("mDoorSta.phase,now,next == %d,%d,%d\r\n",mDoorSta.phase,mDoorSta.nowDoorPosition,mDoorSta.nextDoorPosition);		
	}
	// mDoorSta.phase = mDoorSta.phase % PHASE_MAX;
	setPhaseMotor(mDoorSta.phase);
 }

/*****************************************************************************************************************************
 * StepMotorCtrl  constant  4 per for 1 phase of 700pps
  The 0.3581 degree is 1mm, The 9.5 steps are 1mm too.So ACC and DEC are 8 steps.
 ****************************************************************************************************************************/
void StepMotorCtrl(void)
{
	setYL03Ctrl(1);
	mCount.motor++;
	mInputSta = getAllInputSta();
	if(mKeySta.isNewKeyCmd == TRUE) {
		
		// printf("mKeySta.isNewKeyCmd == TRUE\r\n");
		//Do something for isNewKeyCmd
		//Set new value to mDoorSta
		if(mKeySta.nextKeySta != mKeySta.nowKeySta) { //方向不同 , 立刻走完加减速
			if(mDoorSta.toggleDirPreSta == UNCOMPLETE) {
				// if(mDoorSta.runSta == OPEN_DOOR) {	//	if(mKeySta.nowKeySta == OPEN_DOOR) {	//进入该函数前一定要先进入上电初始化，默认上电后先关门。
				// 	mDoorSta.nextDoorPosition = mDoorSta.nowDoorPosition + DEC_STEP_MAX * 2 - mDoorSta.slowStep;
				// }
				// else if(mDoorSta.runSta == CLOSE_DOOR){
				// 	mDoorSta.nextDoorPosition = mDoorSta.nowDoorPosition - DEC_STEP_MAX * 2 + mDoorSta.slowStep;
				// }
				mDoorSta.toggleDirPreSta = COMPLETE;
			}
			else {
				if(mDoorSta.speedSta == HOLD) {
					if(mKeySta.nextKeySta == OPEN_DOOR) {
						mDoorSta.nextDoorPosition = FARTHEST_POSITION;
					}
					else {
						mDoorSta.nextDoorPosition = HOME_POSITION;
					}
					mKeySta.nowKeySta = mKeySta.nextKeySta;
					mKeySta.isNewKeyCmd = FALSE;
					mDoorSta.runSta = mKeySta.nowKeySta;
					mDoorSta.speedSta = ACCELERATION;
					mDoorSta.slowStep = 0;
					mDoorSta.toggleDirSta = COMPLETE;
				}
				else {
					if(mDoorSta.runSta == OPEN_DOOR) {	//	if(mKeySta.nowKeySta == OPEN_DOOR) {	//进入该函数前一定要先进入上电初始化，默认上电后先关门。
						mDoorSta.nextDoorPosition = mDoorSta.nowDoorPosition + DEC_STEP_MAX * 2 - mDoorSta.slowStep;
					}
					else if(mDoorSta.runSta == CLOSE_DOOR){
						mDoorSta.nextDoorPosition = mDoorSta.nowDoorPosition - DEC_STEP_MAX * 2 + mDoorSta.slowStep;
					}
				}
			}
		}
		else {
			mDoorSta.toggleDirPreSta = UNCOMPLETE;
			mDoorSta.toggleDirSta = UNCOMPLETE;
		}
	}
	else {
		//Noting
	}

	if(mCount.motor >= PhaseTable[mDoorSta.slowStep]) {
		switch (mDoorSta.speedSta)
		{
			case ACCELERATION:
				mDoorSta.slowStep++;
				if(mDoorSta.slowStep >= 8) {
					mDoorSta.speedSta = CONSTANT;
					mDoorSta.slowStep = 8;
				}
				setCurrentMotor(100);
				RunOnePhase();
				break;
			case CONSTANT:
				if((mKeySta.nowKeySta == OPEN_DOOR) && (mDoorSta.nowDoorPosition >= (mDoorSta.nextDoorPosition - DEC_STEP_MAX)))
					mDoorSta.speedSta = DECELERATION;
				if((mKeySta.nowKeySta == CLOSE_DOOR) && (mDoorSta.nowDoorPosition <= (mDoorSta.nextDoorPosition + DEC_STEP_MAX)))
					mDoorSta.speedSta = DECELERATION;
				setCurrentMotor(100);
				RunOnePhase();
				break;
			case DECELERATION:
				mDoorSta.slowStep++;
				if(mDoorSta.slowStep >= 16) {
					mDoorSta.speedSta = HOLD;
					mDoorSta.runSta = HOLD;
					mDoorSta.slowStep = 16;
				}
				setCurrentMotor(100);
				RunOnePhase();
				break;
			case HOLD:
				mDoorSta.speedSta = HOLD;
				mDoorSta.runSta = HOLD;
				mDoorSta.slowStep = 0;
				setCurrentMotor(0);
				break;
			default:
				break;
		}
		mCount.motor = 0;
	}
	setYL03Ctrl(0);
	//maincontrol set direction
	//本函数记录目前门板的具体位置（0~10000 就是具体位置），方向（目前方向和未来的方向，如果未来方向和本次目前方向不一致，要等减速完成后再换向），加减速匀速状态，
	//如果还没到极限位置就检测到到位信号，则立刻减速。关门，并重新置相关变量。如位置信号到mDoorPosition = 0
}

void InitDrv8841(void)
{
	setCurrentMotor(0);
	setSleepMotor(1);
	setResetMotor(1);
}


/*****************************************************************************************************************************
 * END OF FILE: StepMotor.c
 ****************************************************************************************************************************/
