/*
 * test_flash_mutate.c
 *
 *  Created on: Jul 28, 2023
 *      Author: nguyentrunghieu
 */


#include "test_flash_mutate.h"

void print_state(uint8_t state){
	printf("Actual:   %d\n", state);
}
void test_get(){
	mutate_power(OFF);
	printf("Expected: 0\n");
	print_state(get_power());
}
void test_mutate(){

	mutate_power(OFF);
	printf("Expected: 0\n");
	print_state(get_power());

	mutate_power(ON);
	printf("Expected: 1\n");
	print_state(get_power());

	mutate_control_mode(AUTOMATIC);
	printf("Expected: 0\n");
	print_state(get_control_mode());

	mutate_control_mode(MANUAL);
	printf("Expected: 1\n");
	print_state(get_control_mode());

	mutate_wind_mode(LEVEL_0);
	printf("Expected: 0\n");
	print_state(get_wind_mode());

	mutate_wind_mode(LEVEL_1);
	printf("Expected: 1\n");
	print_state(get_wind_mode());

	mutate_wind_mode(LEVEL_2);
	printf("Expected: 2\n");
	print_state(get_wind_mode());

}
