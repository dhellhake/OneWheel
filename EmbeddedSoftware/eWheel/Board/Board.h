/* 
* Board.h
*
* Created: 22.05.2020 13:43:45
* Author: dominik hellhake
*/
#ifndef __BOARD_H__
#define __BOARD_H__

#include "sam.h"
#include "..\Task.h"

class Board : public Task
{
	/************************************************************************/
	/* Executable Interface implementation                                  */
	/************************************************************************/
	virtual RUN_RESULT Run(uint32_t timeStamp);

	/************************************************************************/
	/* Class implementation                                                 */
	/************************************************************************/

	
	private:
		uint32_t IMU_Update_Tstmp;

}; //Board

extern Board Chassis;

#endif //__BOARD_H__
