/*
 * flash_mutate.c
 *
 *  Created on: Jul 26, 2023
 *      Author: nguyentrunghieu
 */
#include"flash_mutate.h"
extern uint32_t* volatile p_power;
extern uint32_t* volatile p_control_mode;
extern uint32_t* volatile p_wind_mode;

extern uint32_t* volatile p_error_page;

extern FLASH_EraseInitTypeDef* flash_power_init;
extern FLASH_EraseInitTypeDef* flash_control_mode_init;
extern FLASH_EraseInitTypeDef* flash_wind_mode_init;


void mutate_power(POWER power){
	if(*p_power != power){
		HAL_FLASH_Unlock();
		HAL_FLASHEx_Erase(flash_power_init, p_error_page);
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_FAST, p_power, power);
		HAL_FLASH_Lock();
	}
}


void mutate_control_mode(CONTROL_MODE control_mode){
	if(*p_control_mode != control_mode){
		HAL_FLASH_Unlock();
		HAL_FLASHEx_Erase(flash_control_mode_init, p_error_page);
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_FAST, p_control_mode, control_mode);
		HAL_FLASH_Lock();
	}
}


void mutate_wind_mode(WIND_MODE wind_mode){
	if(*p_wind_mode != wind_mode){
		HAL_FLASH_Unlock();
		HAL_FLASHEx_Erase(flash_wind_mode_init, p_error_page);
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_FAST, p_wind_mode, wind_mode);
		HAL_FLASH_Lock();
	}
}

uint8_t get_power(){
	HAL_FLASH_Unlock();
	return *p_power;
	HAL_FLASH_Lock();
}

uint8_t get_control_mode(){
	HAL_FLASH_Unlock();
	return *p_control_mode;
	HAL_FLASH_Lock();
}

uint8_t get_wind_mode(){
	HAL_FLASH_Unlock();
	return *p_wind_mode;
	HAL_FLASH_Lock();
}





