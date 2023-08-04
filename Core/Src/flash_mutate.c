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

	uint32_t* p_power_page = (uint32_t*) power_page_address;
	if(*p_power_page != power){
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

	uint32_t* p_control_mode_page = (uint32_t*) control_mode_page_address;
	if(*p_control_mode_page != control_mode){
		HAL_FLASH_Unlock();
		HAL_FLASHEx_Erase(&flash_erase_control_mode_init, &p_error_page);
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, control_mode_page_address, control_mode);
		HAL_FLASH_Lock();
	}
}


void mutate_wind_mode(WIND_MODE wind_mode){
	FLASH_EraseInitTypeDef flash_erase_wind_mode_init;
	flash_erase_wind_mode_init.TypeErase = 0x00;
	flash_erase_wind_mode_init.Banks = FLASH_BANK_2;
	flash_erase_wind_mode_init.NbPages = 1;
	flash_erase_wind_mode_init.Page = wind_mode_page;

	uint32_t* p_wind_mode_page = (uint32_t*) wind_mode_page_address;
	if(*p_wind_mode_page != wind_mode){
		HAL_FLASH_Unlock();
		HAL_FLASHEx_Erase(&flash_erase_wind_mode_init, &p_error_page);
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, wind_mode_page_address, wind_mode);
		HAL_FLASH_Lock();
	}
}

uint8_t get_power(){
	uint32_t* p_power_page = (uint32_t*) power_page_address;
	return *p_power_page;
}

uint8_t get_control_mode(){
	uint32_t* p_control_mode_page = (uint32_t*) control_mode_page_address;
	return *p_control_mode_page;
}

uint8_t get_wind_mode(){
	uint32_t* p_wind_mode_page = (uint32_t*) wind_mode_page_address;
	return *p_wind_mode_page;
}





