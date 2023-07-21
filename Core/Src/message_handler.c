/*
 * message_handler.c
 *
 *  Created on: Jul 19, 2023
 *      Author: nguyentrunghieu
 */

#include "message_handler.h"
extern POWER power;
extern WIND_MODE wind_mode;
extern CONTROL_MODE control_mode;

uint8_t handle_message(char* rec_mes_buffer, char* rep_mes_buffer){
	/*
	 * handle message
	 * return 0 if don't send the reply
	 * return the length of reply message buff otherwise
	 */
	uint8_t* ETX;
	if(*rec_mes_buffer != 0x02){
			return 0;
		}
	uint8_t rep_mes_data_length = process_message(rec_mes_buffer, rep_mes_buffer);
	if(rep_mes_data_length == 1){
		ETX = rec_mes_buffer + 4;
	}
	else if(rep_mes_data_length == 5){
		ETX = rec_mes_buffer + 8;
	}
	else{
		return 0;
	}
	if(*ETX != 0x03){
		return 0;
	}
	return rep_mes_data_length+4;
}



uint8_t process_message(char* rec_mes_buffer, char* rep_mes_buffer){
	/*
	 * read command from receive buffer and write reply to rep buffer
	 * return 0 if don't reply
	 * return message data length otherwise
	 *
	*/

	uint8_t* frame_type = (uint8_t*)rec_mes_buffer + 1;
	uint8_t rec_data_length;
	uint8_t rep_mes_data_length;
	if(*frame_type == 0x04){
		rep_mes_data_length = 5;
	}
	else{
		rep_mes_data_length = 1;
	}
	switch (*frame_type){
		case 0x01:
			rec_data_length = 1;
			if (*(rec_mes_buffer + 3) == 0x00){
				*(rep_mes_buffer+3) = 0x00;
				power = OFF;
			}
			else if(*(rec_mes_buffer + 3) == 0x01){
				*(rep_mes_buffer+3) = 0x00;
				power = ON;
			}
			else{
				*(rep_mes_buffer+3) = 0xFF;
			}
			break;
		case 0x02:
			rec_data_length = 1;
			if(power == OFF){
				*(rep_mes_buffer + 3) = 0x02;
			}
			else{
				if(*(rec_mes_buffer + 3) == 0x00){
					*(rep_mes_buffer + 3) = 0x00;
					// TO DO
					control_mode = AUTOMATIC;
				}
				else if(*(rec_mes_buffer + 3) == 0x01){
					*(rep_mes_buffer + 3) = 0x00;
					control_mode = MANUAL;
				}
				else{
					*(rep_mes_buffer + 3) = 0x01;
				}
			}
			break;
		case 0x03:
			rec_data_length = 1;
			if(power == OFF){
				*(rep_mes_buffer + 3) = 0x02;
			}
			else{
				if(*(rec_mes_buffer + 3) == 0x00){
					*(rep_mes_buffer + 3) = 0x00;
					wind_mode = LEVEL_0;
					control_mode = MANUAL;
				}
				else if(*(rec_mes_buffer + 3) == 0x01){
					*(rep_mes_buffer + 3) = 0x00;
					wind_mode = LEVEL_1;
					control_mode = MANUAL;
				}
				else if(*(rec_mes_buffer + 3) == 0x02){
					*(rep_mes_buffer + 3) = 0x00;
					wind_mode = LEVEL_2;
					control_mode = MANUAL;
				}
				else{
					*(rep_mes_buffer + 3) = 0x01;
				}
			}
			break;
		case 0x04:
			rec_data_length = 0;
			*(rep_mes_buffer + 3) = 0x00;
			*(rep_mes_buffer + 4) = power;
			*(rep_mes_buffer + 5) = control_mode;
			*(rep_mes_buffer + 6) = wind_mode;
			// read temperature sensor
			*(rep_mes_buffer + 7) = 0x00; 
			break;
		default:
			return 0;
	}
	if(*(rec_mes_buffer+2) != rec_data_length){
		*(rep_mes_buffer+3) = 0xFF;
	}
	return rep_mes_data_length;

}


