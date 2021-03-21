/*
 * CSS811_Commands.hpp
 *
 *  Created on: 19 mar. 2021
 *      Author: Victor Fernández Fernández
 */

#ifndef INC_CSS811_COMMANDS_HPP_
#define INC_CSS811_COMMANDS_HPP_

#define CCS811_I2C_ADDRESS1                      (0x5A << 1)
#define CCS811_I2C_ADDRESS2                      (0x5B << 1)

#define CCS811_REG_STATUS                        0x00
#define CCS811_REG_MEAS_MODE                     0x01
#define CCS811_REG_ALG_RESULT_DATA               0x02
#define CCS811_REG_RAW_DATA                      0x03
#define CCS811_REG_ENV_DATA                      0x05
#define CCS811_REG_NTC                           0x06
#define CCS811_REG_THRESHOLDS                    0x10
#define CCS811_REG_BASELINE                      0x11
#define CCS811_REG_HW_ID                         0x20
#define CCS811_REG_HW_VERSION                    0x21
#define CCS811_REG_FW_BOOT_VERSION               0x23
#define CCS811_REG_FW_APP_VERSION                0x24
#define CCS811_REG_INTERNAL_STATE                0xA0
#define CCS811_REG_ERROR_ID                      0xE0
#define CCS811_REG_SW_RESET                      0xFF

#define CCS811_BOOTLOADER_APP_ERASE              0xF1
#define CCS811_BOOTLOADER_APP_DATA               0xF2
#define CCS811_BOOTLOADER_APP_VERIFY             0xF3
#define CCS811_BOOTLOADER_APP_START              0xF4

#define CCS811_HW_ID                             0x81

#define CSS811_OK								 0

#define ERR_OK             						 0      //OK
#define ERR_I2C									 1
#define ERR_DATA_BUS      						 2      //error in data bus
#define ERR_IC_VERSION    						 3      //chip version mismatch

#endif /* INC_CSS811_COMMANDS_HPP_ */
