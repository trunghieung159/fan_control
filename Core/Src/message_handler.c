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
	 * return 0 if there is an error
	 * return 1 otherwise
	 */

	if(*rec_mes_buffer != 0x02){
			return 0;
		}
	uint8_t expected_length = process_messange(rec_mes_buffer, rep_mes_buffer);
	if(expected_length == -1){
		return 0;
	}
	if (*(rec_mes_buffer + expected_length + 2) != 0x03){
		*(rep_mes_buffer + 3) = 0xFF;
		return 0;
	}
	else{
		return 1;
	}
}



uint8_t process_messange(char* rec_mes_buffer, char* rep_mes_buffer){
	/*
	 * read command from receive buffer and write reply to rep buffer
	 *
	*/

	uint8_t* frame_type = rec_mes_buffer + 1;
	uint8_t expected_length;
	switch (*frame_type){
		case 0x01:
			expected_length = 1;
			if (*(rec_mes_buffer + 3) == 0x00){
				*rep_mes_buffer = 0x00;
				power = OFF;
			}
			else if(*(rec_mes_buffer + 2) == 0x01){
				*rep_mes_buffer = 0x00;
				power = ON;
			}
			else{
				*rep_mes_buffer = 0xFF;
			}
			break;
		case 0x02:
			expected_length = 1;
			if(power == OFF){
				*(rec_mes_buffer + 3) = 0x02;
			}
			else{
				if(*(rec_mes_buffer + 3) == 0x00){
					*(rep_mes_buffer + 3) = 0x00;
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
			expected_length = 1;
			if(power == OFF){
				*(rep_mes_buffer + 3) = 0x02;
			}
			else{
				if(*(rec_mes_buffer + 3) == 0x00){
					*(rep_mes_buffer + 3) = 0x00;
					wind_mode = LEVEL_0;
				}
				else if(*(rec_mes_buffer + 3) == 0x01){
					*(rep_mes_buffer + 3) = 0x01;
					wind_mode = LEVEL_1;
				}
				else if(*(rec_mes_buffer + 3) == 0x02){
					*(rep_mes_buffer + 3) = 0x02;
					wind_mode = LEVEL_2;
				}
				else{
					*(rep_mes_buffer + 3) = 0x01;
				}
			}
			break;
		case 0x04:
			expected_length = 0;
			// TO DO
			break;
		default:
			return -1;
	}
	return expected_length;

}


