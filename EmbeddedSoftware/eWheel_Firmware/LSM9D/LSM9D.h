/* 
* LSM9D.h
*
* Created: 26.06.2018 23:08:02
* Author: dominik hellhake
*/


#ifndef __LSM9D_H__
#define __LSM9D_H__

#include <math.h>
#include "..\LowLevel\SPI\SPI.h"
#include "..\LowLevel\System\System.h"

#include "..\AT45DB\AT45DB.h"
#include "..\SSD1306\SSD1306.h"
#include "..\Executable.h"

// Register addresses
#define STATUS_REG_1					0x27
#define CTRL_REG5_XL					0x1F
#define CTRL_REG6_XL					0x20
#define CTRL_REG7_XL					0x21
#define OUT_X_L_XL						0x28
#define INT1_CTRL						0x0C

// Sensor Sensitivity Constants
#define SENSITIVITY_ACCELEROMETER_4		1.22


class LSM9D : public Executable
{
	/************************************************************************/
	/* Executable Interface implementation                                  */
	/************************************************************************/
	public:
		SSD1306 *OLED = NULL;
		AT45DB *TraceLink = NULL;
	public:
		virtual bool CanExecute() { return ((PORT->Group[0].IN.reg >> 13) & 0x1) != 0x0; };
		virtual RUN_RESULT Run();
		virtual void Propagate();
		virtual void EnableTrace();
		virtual void DisableTrace();
	
	/************************************************************************/
	/* Class implementation                                                 */
	/************************************************************************/
	public:
		float Pitch = 0;
		float Roll = 0;
		
		TracePage Page;
		volatile uint16_t TraceIndex = 0;
	public:
		LSM9D();	
	private:				
		uint8_t ReadBytes(uint8_t address, uint8_t *dest, uint8_t count);	
		uint8_t WriteRegister(uint8_t address, uint8_t data);
}; //LSM9D

#endif //__LSM9D_H__
