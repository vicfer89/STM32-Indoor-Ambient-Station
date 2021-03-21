/*
 * CSS811.cpp
 *
 *  Created on: 18 mar. 2021
 *      Author: Victor Fernández Fernández
 */

#include "../inc/CCS811.hpp"


uint8_t CCS811::begin(CSS811_Mode mode)
{
	if(this->I2C_Handler == NULL)
	{
		return ERR_I2C;
	}

	return ERR_OK;
}

void CCS811::set_DataAvail_flag(void)
{
	if(this->I2C_Handler == NULL)
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
	if(f_InterruptMode == true){
		return f_DataAvail;
	}
	/* In polling mode, checks if data is available from CCS811 */
	else{
		return false;
	}
}

CCS811_Data CCS811::get_Data(void)
{
	return Data;
}

uint16_t CCS811::get_eCO2(void)
{
	return Data.eCO2;
}

uint16_t CCS811::get_TVOC(void)
{
	return Data.TVOC;
}
