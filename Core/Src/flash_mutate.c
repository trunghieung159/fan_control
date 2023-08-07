/*
 * flash_mutate.c
 *
 *  Created on: Jul 26, 2023
 *      Author: nguyentrunghieu
 */
#include"flash_mutate.h"
uint32_t power_page = 0;
uint32_t control_mode_page = 1;
uint32_t wind_mode_page = 2;
uint32_t p_error_page;

uint32_t power_page_address = 0x08080000;
uint32_t control_mode_page_address  = 0x08080800;
uint32_t wind_mode_page_address = 0x08081000;


void mutate_power(POWER power){
	FLASH_EraseInitTypeDef flash_erase_power_init;
	flash_erase_power_init.TypeErase =  0x00;
	flash_erase_power_init.Banks = FLASH_BANK_2;
	flash_erase_power_init.NbPages = 1;
	flash_erase_power_init.Page = power_page;

	uint32_t* p_control_mode = (uint32_t*) control_mode_page_address;
	uint32_t* p_wind_mode = (uint32_t*) wind_mode_page_address;
	uint32_t* p_power = (uint32_t*) power_page_address;
	if(*p_power != power){
		if(power == OFF){
			wind_control(htim1, LEVEL_0);
		}
		else{
			if(*p_control_mode == MANUAL){
				wind_control(htim1, *p_wind_mode);
			}
			else{
				//TO DO
			}
		}
		HAL_FLASH_Unlock();
		HAL_FLASHEx_Erase(&flash_erase_power_init, &p_error_page);
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, power_page_address, power);
		HAL_FLASH_Lock();
	}
}


void mutate_control_mode(CONTROL_MODE control_mode){
	FLASH_EraseInitTypeDef flash_erase_control_mode_init;
	flash_erase_control_mode_init.TypeErase =  0x00;
	flash_erase_control_mode_init.Banks = FLASH_BANK_2;
	flash_erase_control_mode_init.NbPages = 1;
	flash_erase_control_mode_init.Page = control_mode_page;

	uint32_t* p_control_mode = (uint32_t*) control_mode_page_address;
	if(*p_control_mode != control_mode){
		HAL_FLASH_Unlock();
		HAL_FLASHEx_Erase(&flash_erase_control_mode_init, &p_error_page);
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, control_mode_page_address, control_mode);
		HAL_FLASH_Lock();
		if(control_mode == MANUAL){
			uint32_t* p_wind_mode = (uint32_t*) wind_mode_page_address;
			wind_control(htim1, *p_wind_mode);
		}
		else{
			// TO DO
		}
	}
}


void mutate_wind_mode(WIND_MODE wind_mode){
	FLASH_EraseInitTypeDef flash_erase_wind_mode_init;
	flash_erase_wind_mode_init.TypeErase = 0x00;
	flash_erase_wind_mode_init.Banks = FLASH_BANK_2;
	flash_erase_wind_mode_init.NbPages = 1;
	flash_erase_wind_mode_init.Page = wind_mode_page;

	uint32_t* p_wind_mode = (uint32_t*) wind_mode_page_address;
	if(*p_wind_mode != wind_mode){
		HAL_FLASH_Unlock();
		HAL_FLASHEx_Erase(&flash_erase_wind_mode_init, &p_error_page);
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, wind_mode_page_address, wind_mode);
		HAL_FLASH_Lock();
		wind_control(htim1, wind_mode);
	}
}

uint8_t get_power(){
	uint32_t* p_power = (uint32_t*) power_page_address;
	return *p_power;
}

uint8_t get_control_mode(){
	uint32_t* p_control_mode = (uint32_t*) control_mode_page_address;
	return *p_control_mode;
}

uint8_t get_wind_mode(){
	uint32_t* p_wind_mode = (uint32_t*) wind_mode_page_address;
	return *p_wind_mode;
}

void wind_control(TIM_HandleTypeDef tim_handler, WIND_MODE wind_mode){
	switch(wind_mode){
	case LEVEL_0:
		__HAL_TIM_SET_COMPARE(&tim_handler, TIM_CHANNEL_2, 0);
		break;
	case LEVEL_1:
		__HAL_TIM_SET_COMPARE(&tim_handler, TIM_CHANNEL_2, 599);
		break;
	case LEVEL_2:
		__HAL_TIM_SET_COMPARE(&tim_handler, TIM_CHANNEL_2, 799);
		break;
	}
}




