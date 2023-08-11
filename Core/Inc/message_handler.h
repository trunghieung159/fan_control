/*
 * message_handler.h
 *
 *  Created on: Jul 19, 2023
 *      Author: nguyentrunghieu
 */
#ifndef SRC_MESSAGE_HANDLER_H_
#define SRC_MESSAGE_HANDLER_H_
#include "stm32l4xx_hal.h"


typedef enum{
	OFF = 0,
	ON = 1
} POWER;
	
typedef enum{
	LEVEL_0 = 0,
	LEVEL_1 = 1,
	LEVEL_2 = 2
} WIND_MODE;
	
typedef enum{
	AUTOMATIC = 0,
	MANUAL = 1
}  CONTROL_MODE;

extern POWER power;
extern WIND_MODE wind_mode;
extern CONTROL_MODE control_mode;
extern float volatile temperature;

uint8_t handle_message(unsigned char* received_buf, unsigned char* sent_buf);
void process_power_message(unsigned char* received_buf, unsigned char* sent_buf);
void process_control_mode_message(unsigned char* received_buf, unsigned char* sent_buf);
void process_wind_mode_message(unsigned char* received_buf, unsigned char* sent_buf);
uint8_t process_states_request_message(unsigned char* received_buf, unsigned char* sent_buf);
uint8_t check_message_data_length(unsigned char* received_buf, uint8_t expected_value);
#endif /* SRC_MESSAGE_HANDLER_H_ */
