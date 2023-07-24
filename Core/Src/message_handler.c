/*
 * message_handler.c
 *
 *  Created on: Jul 19, 2023
 *      Author: nguyentrunghieu
 */

#include "message_handler.h"


uint8_t handle_message(unsigned char* received_buf, unsigned char* sent_buf){
	/**
	 * @brief read received message in read buffer and write reply in write buffer
	 * @param read_buf incoming message's buffer
	 * @param write_buf sending message's buffer
	 * @return 0 if don't send the reply
	 * return the length of reply message buff otherwise
	 */
	uint8_t sent_buf_length;
	uint8_t* stx = received_buf;
	if(*stx != 0x02){
		sent_buf_length = 0;
		goto terminate;
	}

	uint8_t* received_frame_type  = received_buf + 1;
	uint8_t* sent_frame_type = sent_buf + 1;
	uint8_t* p_sent_data_length = sent_buf + 2;
	uint8_t sent_data_length;
	uint8_t received_data_length;
	
	*sent_buf = 0x02;
	switch(*received_frame_type){
		case 0x01:
			process_power_message(received_buf, sent_buf);
			sent_data_length = 1;
			received_data_length = 1;
			break;
		case 0x02:
			process_control_mode_message(received_buf, sent_buf);
			sent_data_length = 1;
			received_data_length = 1;
			break;
		case 0x03:
			process_wind_mode_message(received_buf, sent_buf);
			sent_data_length = 1;
			received_data_length = 1;
			break;
		case 0x04:
			sent_data_length = process_states_request_message(received_buf, sent_buf);
			received_data_length = 0; 
			break;
		default:
			sent_buf_length = 0;
			goto terminate;
	}
	*sent_frame_type = *received_frame_type + 0x80;
	*p_sent_data_length = sent_data_length;

	uint8_t* received_ETX = received_buf + 3 + received_data_length;
	if(*received_ETX != 0x03){
		sent_buf_length = 0;
		goto terminate;
	}


	uint8_t* sent_ETX = sent_buf + 3 + sent_data_length; 
	*sent_ETX = 0x03;
	sent_buf_length = sent_data_length + 4;
	terminate: return sent_buf_length;
}



void process_power_message(unsigned char* received_buf, unsigned char* sent_buf){
	/**
	 * @brief read power message from received_buf and replies in sent_buf 
	 * @param received_buf power message's buffer
	 * @param sent_buf reply message's buffer 
	 * return message data length otherwise
	 *
	*/
	if(!check_message_data_length(received_buf, 1)){
		return;
	}

	uint8_t* received_data = received_buf + 3;
	uint8_t* sent_data = sent_buf + 3;
	if(*received_data == 0x00){
		power = OFF;
		*sent_data = 0x00;
	}
	else if(*received_data == 0x01){
		power = ON;
		*sent_data = 0x00;
	}
	else{
		*sent_data = 0xFF;
	}
}

void process_control_mode_message(unsigned char* received_buf, unsigned char* sent_buf){
	/**
	 * @brief read mode control message from received_buf and replies in sent_buf 
	 * @param received_buf mode control message's buffer
	 * @param sent_buf reply message's buffer 
	 *
	*/
	if(!check_message_data_length(received_buf, 1)){
		return;
	}

	uint8_t* received_data = received_buf + 3;
	uint8_t* sent_data = sent_buf + 3;
	if(*received_data == AUTOMATIC || *received_data == MANUAL){
		control_mode = *received_data;
		*sent_data = 0x00;
	}
	else{
		*sent_data = 0xFF;
	}
}

void process_wind_mode_message(unsigned char* received_buf, unsigned char* sent_buf){
	/**
	 * @brief read win mode message from received_buf and replies in sent_buf 
	 * @param received_buf win mode message's buffer
	 * @param sent_buf reply message's buffer 
	 *
	*/
	if(!check_message_data_length(received_buf, 1)){
		return;
	}

	uint8_t* received_data = received_buf + 3;
	uint8_t* sent_data = sent_buf + 3;
	if(*received_data == LEVEL_0 || *received_data == LEVEL_1 || *received_data == LEVEL_2){
		wind_mode = *received_data;
		*sent_data = 0x00;
	}
	else{
		*sent_data = 0xFF;
	}
}

uint8_t process_states_request_message(unsigned char* received_buf, unsigned char* sent_buf){
	/**
	 * @brief read states request message from received_buf and replies in sent_buf 
	 * @param received_buf sates request message's buffer
	 * @param sent_buf reply message's buffer 
	 * @return sent message's data length
	*/
	uint8_t* sent_data = sent_buf + 3;
	uint8_t sent_data_length;
	if(!check_message_data_length(received_buf, 0)){
		sent_data_length = 1;
		*sent_data = 0x00;
	}
	else{
		sent_data_length = 5;
		*sent_data = 0xFF;
	}
	return sent_data_length;
}

uint8_t check_message_data_length(unsigned char* received_buf, uint8_t expected_value){
	/**
	* @brief check whether the length message is correct or not 
	* @return 1 if it is correct 
	* return  0 other wise  
	*/
	uint8_t* length = received_buf + 2;
	if(*length == expected_value){
		return 1;
	}
	else{
		return 0;
	}
}

