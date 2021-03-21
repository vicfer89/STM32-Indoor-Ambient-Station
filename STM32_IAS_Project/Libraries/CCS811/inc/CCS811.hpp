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

typedef enum _CCS811_Mode {
	Mode_Idle = 0,
	Mode_1s,
	Mode_10s,
	Mode_60s,
	Mode_250ms
}CSS811_Mode;

typedef struct _CCS811_Data
{
	uint16_t eCO2;
	uint16_t TVOC;
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
		uint8_t begin(CSS811_Mode mode);

		/* Data availability setter and resetter in interrupt mode */
		void set_DataAvail_flag(void),
			 reset_DataAvail_flag(void);

		/* Check if data available*/
		bool isDataAvail(void);

		/* Get sensor data */
		CCS811_Data get_Data(void);
		uint16_t 	get_eCO2(void),
					get_TVOC(void);

		/* Active interrupt mode */
		void active_interrupt(void);

	protected:

		void writeRegister(uint8_t reg, const void * data, size_t size);
		uint8_t readRegister(uint8_t reg, const void * data, size_t size);


	private:

		volatile bool f_DataAvail = false;
		volatile bool f_InterruptMode = false;

		I2C_HandleTypeDef * I2C_Handler;
		uint8_t Device_Addr;

		CCS811_Data Data;
};

#endif /* INC_CSS811_HPP_ */
