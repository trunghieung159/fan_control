/*
 * flash_mutate.h
 *
 *  Created on: Jul 26, 2023
 *      Author: nguyentrunghieu
 */

#ifndef SRC_FLASH_MUTATE_H_
#define SRC_FLASH_MUTATE_H_
#include "message_handler.h"
#include "stm32l4xx_hal.h"
void mutate_power(POWER power);
void mutate_control_mode(CONTROL_MODE control_mode);
void mutate_wind_mode(WIND_MODE wind_mode);

uint8_t get_power();
uint8_t get_control_mode();
uint8_t get_wind_mode();

#endif /* SRC_FLASH_MUTATE_H_ */
