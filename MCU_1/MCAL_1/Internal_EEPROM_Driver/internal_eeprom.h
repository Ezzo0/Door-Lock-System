/*
 * internal_eeprom.h
 *
 * Created: 10/10/2022 11:40:19 PM
 *  Author: 3zz
 */ 


#ifndef INTERNAL_EEPROM_H_
#define INTERNAL_EEPROM_H_

#include "../../Utilities_1/Macros_1.h"

void int_eeprom_w(uint8_t addr, uint8_t data);
uint8_t int_eeprom_r(uint8_t addr);


#endif /* INTERNAL_EEPROM_H_ */