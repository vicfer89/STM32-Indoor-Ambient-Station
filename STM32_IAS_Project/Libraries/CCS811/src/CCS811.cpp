/*
 * CSS811.cpp
 *
 *  Created on: 18 mar. 2021
 *      Author: Victor Fernández Fernández
 */

#include "../inc/CCS811.hpp"
#include "stdio.h"


uint8_t CCS811::begin(uint8_t mode)
{
	if(I2C_Handler == NULL)
	{
		return ERR_I2C;
	}

	HAL_Delay(70); // Wait for 70 ms

	/* HW ID register is readed */
	readRegister(CCS811_REG_HW_ID, &rxBuff, 1);
	if(rxBuff[0] != CCS811_HW_ID)
	{
		printf("CCS811 sensor error...\r\n");
		return ERR_IC_VERSION;
	}

	/* APP is started if sensor has right ID */
	writeRegister(CCS811_BOOTLOADER_APP_START, NULL, 0);
	HAL_Delay(20);
	//uint8_t mode = CCS811_MODE_1S | CCS811_MODE_INT_ENABLE | CCS811_MODE_THRESHOLD_DISSABLE;
	writeRegister(CCS811_REG_MEAS_MODE, &mode, 1);
	HAL_Delay(20);

	return ERR_OK;
}

void CCS811::set_DataAvail_flag(void)
{
	if(I2C_Handler == NULL)
	{
		return;
	}

	f_DataAvail = true;
}

void CCS811::reset_DataAvail_flag(void)
{
	f_DataAvail = false;
}

bool CCS811::isDataAvail(void)
{
	/* In interrupt mode returns f_DataAvail flag from interrupt routine */
	if(f_InterruptMode == true)
	{
		return f_DataAvail;
	}
	/* In polling mode, checks if data is available from CCS811 */
	else
	{
		return false;
	}
}

CCS811_Data CCS811::getData(void)
{
	return Data;
}

uint16_t CCS811::getCO2(void)
{
	return Data.eCO2;
}

uint16_t CCS811::getTVOC(void)
{
	return Data.TVOC;
}

void CCS811::writeRegister(uint8_t reg, const void * data, size_t size)
{
	HAL_I2C_Mem_Write(I2C_Handler, Device_Addr, reg, 1, (uint8_t *) data, size, 100);
}

void CCS811::readRegister(uint8_t reg, const void * data, size_t size)
{
	HAL_I2C_Master_Receive(I2C_Handler, Device_Addr, (uint8_t *) data, size, 100);
}
