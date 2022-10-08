/*
 * EEPROM.h
 *
 * Created: 10/7/2022 8:11:41 PM
 *  Author: 3zz
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include "../../MCAL_2/TWI_Driver_2/TWI_2.h"
#include "../../Utilities_2/Macros_2.h"


void EEPROM_init();
void EEPROM_write_byte(uint8_t data);
void EEPROM_read_byte(uint8_t **data);

void EEPROM_write_string(uint8_t *data);
void EEPROM_read_string(uint8_t *data);

#endif /* EEPROM_H_ */