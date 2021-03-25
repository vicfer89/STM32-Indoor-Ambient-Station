/*
 * CSS811.h
 *
 *  Created on: 18 mar. 2021
 *      Author: Victor Fernández Fernández
 */

#ifndef INC_CSS811_HPP_

#define INC_CSS811_HPP_

#include <main.hpp>
#include "CCS811_Commands.hpp"

typedef struct _CCS811_Data
{
	uint16_t eCO2;
	uint16_t TVOC;
	uint8_t status;
	uint8_t error_id;
	uint8_t current;
	uint8_t raw_adc;
}CCS811_Data;

class CCS811
{
	public:

		/* Class Constructor */
		CCS811( I2C_HandleTypeDef * _I2C_Handler = NULL, uint8_t _Device_Addr = CCS811_I2C_ADDRESS1 )
				: I2C_Handler(_I2C_Handler), Device_Addr(_Device_Addr) {};

		/* Class Destructor */
		~CCS811() {};

		/* Begin sensor */
		uint8_t begin(uint8_t mode);

		/* Data availability setter and resetter in interrupt mode */
		void set_DataAvail_flag(void),
			 reset_DataAvail_flag(void);

		/* Check if data available*/
		bool isDataAvail(void);

		/* Get sensor data */
		void updateData(void);
		CCS811_Data getData(void);
		uint16_t 	getCO2(void),
					getTVOC(void);
		uint8_t		getStatus(void),
					getErrId(void),
					getCurrent(void),
					getAdcRaw(void);

		/* Sensor configuration */
		void setEnvData(float humidity, float temperature);
		void setThreshold(uint16_t LowToMed, uint16_t MedtoHigh);

		/* Active interrupt mode */
		void active_interrupt(void);

	protected:

		void writeRegister(uint8_t reg, const void * data, size_t size);
		void readRegister(uint8_t reg, const void * data, size_t size);


	private:
		uint8_t rxBuff[8] = {0x00};
		uint8_t txBuff[8] = {0x00};

		volatile bool f_DataAvail = false;
		volatile bool f_InterruptMode = false;

		I2C_HandleTypeDef * I2C_Handler;
		uint8_t Device_Addr;

		CCS811_Data Data;
};

#endif /* INC_CSS811_HPP_ */
