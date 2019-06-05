/* 
* Chassis.cpp
*
* Created: 28.04.2019 20:30:49
* Author: Dominik Hellhake
*/
#include "Chassis.h"
#include "..\LSM9D\LSM9D.h"

Chassis Board;

/************************************************************************/
/* Executable Interface implementation                                  */
/************************************************************************/
RUN_RESULT Chassis::Run(uint32_t timeStamp)
{
	if (Gyro.TaskStatus != TASK_STATUS::COMPLETE)
		return RUN_RESULT::IDLE;
	
	float pitch = Gyro.Pitch - this->Road_Pitch;
	
	this->Chassis_Pitch = this->Chassis_Pitch - (0.3 * (this->Chassis_Pitch - pitch));	
	this->Chassis_Roll = Gyro.Roll - this->Road_Pitch;	
	
	switch (this->State)
	{
		case ChassisState::Starting:
			if (!this->IsStartPosition())
				this->State = ChassisState::Normal;		
		break;
		case ChassisState::Normal:			
			if (this->IsRolledOver() || this->IsPitchedOver())
				this->DropOver_Dbnc += timeStamp - this->LAST_RUNNED;
			else
				this->DropOver_Dbnc = 0;
						
			if (this->DropOver_Dbnc > 200)
				this->State = ChassisState::DroppedOver;
		break;
		case ChassisState::DroppedOver:
			if (this->IsStartPosition())
				this->State = ChassisState::Starting;
		break;
	}
	
	this->TaskStatus = TASK_STATUS::COMPLETE;
	return RUN_RESULT::SUCCESS;
}


/************************************************************************/
/* Class implementation                                                 */
/************************************************************************/
Chassis::Chassis()
{
} //Chassis

void Chassis::SetLED(bool state)
{
	if (state)
		PORT->Group[0].OUTSET.reg = PORT_PA28;
	else
		PORT->Group[0].OUTCLR.reg = PORT_PA28;
}