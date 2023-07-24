/*
 * test_message_handler.h
 *
 *  Created on: Jul 24, 2023
 *      Author: nguyentrunghieu
 */

#ifndef SRC_TEST_MESSAGE_HANDLER_H_
#define SRC_TEST_MESSAGE_HANDLER_H_
void turn(unsigned char* receiveBuffer, uint8_t pow);
void ctrl_mode(unsigned char* receiveBuffer, uint8_t ctrl_mode);
void set_wind(unsigned char* receiveBuffer, uint8_t wind_mode);
void request(unsigned char* receiveBuffer);
void print_mess(unsigned char* rep_mess_buff, uint8_t length);
void test_message_handler(unsigned char* receiveBuffer, unsigned char* sendBuffer);
#endif /* SRC_TEST_MESSAGE_HANDLER_H_ */
