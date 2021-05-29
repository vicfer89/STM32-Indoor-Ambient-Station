/*
 * GNSS.hpp
 *
 *  Created on: 10 abr. 2021
 *      Author: Vic
 */

#ifndef GNSS_GNSS_HPP_
#define GNSS_GNSS_HPP_

#include <main.hpp>
#include "NMEA.hpp"

typedef struct _position
{
	float latitude;
	float longitude;
	float altitude;
}position_t;

typedef struct _datetime
{
	int hour;
	int minute;
	int second;
	int day;
	int month;
	int hour;
}datetime_t;

typedef struct _DOP
{
	int PDOP;
	int HDOP;
}DOP_t;

typedef struct _GNNS_Data_t
{
	position_t position;
	datetime_t datetime;
	DOP_t DOP;
}GNSS_Data_t;

class GNSS
{
	public:
		/* Class Construcctor */
		GNSS( UART_HandleTypedef * _huart = NULL ) :
			  huart_handler(_huart),
			  GNSS_Data({
					   	 .position = {0,0,0},
					   	 .datetime = {0,0,0,0,0,0},
						 .DOP = {0,0}
						})
		{
			/* RX ISR Pointer to handler function*/
			huart_handler->RxISR = &ISR_Rx_GNSS_UART;
			huart_handler->TxISR = &ISR_Tx_GNSS_UART;
		};

		/* Class Destructor */
		~GNSS()
		{};

		void check_new_packet();

		GNSS_Data_t get_GNSS_Data(void);
		position_t get_GNSS_pos(void);
		datetime_t get_GNSS_datetime(void);
		DOP_t	get_GNSS_DOP(void);

		void set_flag_packet_avail(void)
		{
			flag_packet_avail = true;
		}

		void reset_flag_packet_avail(void)
		{
			flag_packet_avail = false;
		}

		void set_flag_pps_avail(void)
		{
			flag_pps_avail = true;
		}

		void reset_flag_pps_avail(void)
		{
			flag_pps_avail = false;
		}

		void ISR_Rx_GNSS_UART(struct __UART_HandleTypeDef *huart)
		{

		}

		void ISR_Tx_GNSS_UART(struct __UART_HandleTypeDef *huart)
		{

		}

	private:

	volatile bool flag_packet_avail = false;
	volatile bool flag_pps_avail = false;

	uint8_t rxBuff[256];
	uint8_t txBuff[256];

	UART_HandleTypeDef * huart_handler;
	GNSS_Data_t GNSS_Data;
};


#endif /* GNSS_GNSS_HPP_ */
