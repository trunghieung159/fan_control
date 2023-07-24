/*
 * test_message_handler.c
 *
 *  Created on: Jul 24, 2023
 *      Author: nguyentrunghieu
 */

#include "message_handler.h"
void turn(unsigned char* receiveBuffer, uint8_t pow){
	/**
	 * @brief write power message to buffer
	*/
	receiveBuffer[0] = 0x02;
	receiveBuffer[1] = 0x01;
	receiveBuffer[2] = 0x01;
	if(pow == 0){
		receiveBuffer[3] = 0x00;
	}
	else{
		receiveBuffer[3] = 0x01;
	}
	receiveBuffer[4] = 0x03;
}

void ctrl_mode(unsigned char* receiveBuffer, uint8_t ctrl_mode){
	/**
	 * @brief write mode control message to buffer
	*/
	receiveBuffer[0] = 0x02;
	receiveBuffer[1] = 0x02;
	receiveBuffer[2] = 0x01;
	if(ctrl_mode == 0){
		receiveBuffer[3] = 0x00;
	}
	else{
		receiveBuffer[3] = 0x01;
	}
	receiveBuffer[4] = 0x03;
}

void set_wind(unsigned char* receiveBuffer, uint8_t wind_mode){
	/**
	 * @brief write wind mode message to buffer
	*/
	receiveBuffer[0] = 0x02;
	receiveBuffer[1] = 0x03;
	receiveBuffer[2] = 0x01;
	receiveBuffer[3] = wind_mode;
	receiveBuffer[4] = 0x03;
}

void request(unsigned char* receiveBuffer){
	/**
	 * @brief write request message to buffer
	*/
	receiveBuffer[0] = 0x02;
	receiveBuffer[1] = 0x04;
	receiveBuffer[2] = 0x00;
	receiveBuffer[3] = 0x03;
}

void print_mess(unsigned char* rep_mess_buff, uint8_t length){
	/**
	 * @brief print value of message's buffer
	*/
  printf("Actual:   ");
  for (uint8_t i =0; i<length; i++ ){
    printf("%X ", *(rep_mess_buff+i));
  }
  printf("\n");
}

void test_message_handler(unsigned char* receiveBuffer, unsigned char* sendBuffer){
	/*
	 * @brief test message_handler() function
	 */


	// Test case 1:
	turn(receiveBuffer, 1);
	printf("Expected: 2 81 1 0 3\n");
	print_mess(sendBuffer, handle_message(receiveBuffer, sendBuffer));

	// Test case 2:
	ctrl_mode(receiveBuffer ,1);
	printf("Expected: 2 82 1 0 3\n");
	print_mess(sendBuffer ,handle_message(receiveBuffer, sendBuffer));

	// Test case 4:
	set_wind(receiveBuffer, 2);
	printf("Expected: 2 83 1 0 3\n");
	print_mess(sendBuffer ,handle_message(receiveBuffer, sendBuffer));

	// Test case 5:
	request(receiveBuffer);
	printf("Expected: 2 84 5 0 1 1 2 0 3\n");
	print_mess(sendBuffer ,handle_message(receiveBuffer, sendBuffer));

	// Test case 6:
	turn(receiveBuffer, 0);
	handle_message(receiveBuffer, sendBuffer);
	ctrl_mode(receiveBuffer, 0);
	printf("Expected: 2 82 1 FF 3\n");
	print_mess(sendBuffer ,handle_message(receiveBuffer, sendBuffer));

	// Test case 7:
	set_wind(receiveBuffer, 1);
	printf("Expected: 2 83 1 FF 3\n");
	print_mess(sendBuffer ,handle_message(receiveBuffer, sendBuffer));

	// Test case 8:
	request(receiveBuffer);
	printf("Expected: 2 84 5 0 0 1 2 0 3\n");
	print_mess(sendBuffer, handle_message(receiveBuffer, sendBuffer));

}
