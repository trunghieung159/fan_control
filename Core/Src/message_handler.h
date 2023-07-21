/*
 * message_handler.h
 *
 *  Created on: Jul 19, 2023
 *      Author: nguyentrunghieu
 */
#ifndef SRC_MESSAGE_HANDLER_H_
#define SRC_MESSAGE_HANDLER_H_
#include "stm32l4xx_hal.h"

typedef enum
	{OFF = 0,
	ON = 1}
	POWER;
typedef enum{
	LEVEL_0 = 0,
	LEVEL_1 = 1,
	LEVEL_2 = 2}
	WIND_MODE;
typedef enum{
	AUTOMATIC = 0,
	MANUAL = 1}
	CONTROL_MODE;

uint8_t handle_message(char* rec_mes_buffer, char* rep_mes_buffer);
uint8_t process_message(char* rec_mes_buffer, char* rep_mes_buffer);
#endif /* SRC_MESSAGE_HANDLER_H_ */
