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
	readRegister(CCS811_REG_HW_ID, rxBuff, 1);
	if(rxBuff[0] != CCS811_HW_ID)
	{

		printf("CCS811 sensor error...\r\n");
		return ERR_IC_VERSION;
	}

	readRegister(CCS811_REG_HW_VERSION, rxBuff,1);
	printf("Leido de 0x%x el valor 0x%x \r\n", CCS811_REG_HW_VERSION, rxBuff[0]);

	/* APP is started if sensor has right ID */
	uint8_t appStart = CCS811_BOOTLOADER_APP_START;
	HAL_I2C_Master_Transmit(I2C_Handler, Device_Addr, &appStart, 1, 300);
	HAL_Delay(300);

	printf("CCS811 APP Comenzada... \r\n");

	if(mode && CCS811_MODE_INT_ENABLE)
	{
		f_InterruptMode = true;
	}

	txBuff[0] = mode;
	writeRegister(CCS811_REG_MEAS_MODE, txBuff, 1);
	HAL_Delay(300);
	readRegister(CCS811_REG_MEAS_MODE, rxBuff,1);
	printf("Leido de 0x%x el valor 0x%x \r\n", CCS811_REG_HW_VERSION, rxBuff[0]);

	readRegister(CCS811_REG_ERROR_ID, rxBuff,1);
	printf("Leido de 0x%x el valor 0x%x \r\n", CCS811_REG_ERROR_ID, rxBuff[0]);
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

bool CCS811::CheckDataAvail(void)
{
	/* In interrupt mode returns f_DataAvail flag from interrupt routine */
	if(f_InterruptMode && f_DataAvail)
	{
		readRegister(CCS811_REG_ALG_RESULT_DATA,(uint8_t *) &Data,8);
		reset_DataAvail_flag();
		return true;
	}
	/* In polling mode, checks if data is available from CCS811 */
	else
	{
		readRegister(CCS811_REG_STATUS, rxBuff,1);
		//uint8_t err;
 		//readRegister(CCS811_REG_ERROR_ID, &err, 1);
		if((rxBuff[0] >> 3) & 0x01)
		{
			readRegister(CCS811_REG_ALG_RESULT_DATA, rxBuff,8);
			Data.eCO2 =  (((uint16_t)rxBuff[0] << 8) | (uint16_t)rxBuff[1]);
			Data.TVOC = (((uint16_t)rxBuff[2] << 8) | (uint16_t)rxBuff[3]);
			Data.status = rxBuff[4];
			Data.error_id = rxBuff[5];
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
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

void CCS811::writeRegister(uint8_t reg, uint8_t * data, size_t size)
{
	HAL_I2C_Mem_Write(I2C_Handler, Device_Addr, reg, 1, (uint8_t *) data, size,300);
	 while (HAL_I2C_GetState(I2C_Handler) != HAL_I2C_STATE_READY)
	{
	}
	while (HAL_I2C_IsDeviceReady(I2C_Handler, CCS811_I2C_ADDRESS1, 10, 300) == HAL_TIMEOUT);
	while(HAL_I2C_GetState(I2C_Handler) != HAL_I2C_STATE_READY)
	{
	}
}

void CCS811::readRegister(uint8_t reg, uint8_t * data, size_t size)
{
	HAL_I2C_Mem_Read(I2C_Handler, Device_Addr, reg, 1, data, size, 300);
	while (HAL_I2C_GetState(I2C_Handler) != HAL_I2C_STATE_READY);
}
