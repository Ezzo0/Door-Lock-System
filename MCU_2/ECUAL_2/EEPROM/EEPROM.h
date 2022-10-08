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



#define EEPROM_ADDRESS 0xAE

void EEPROM_inti(uint8_t prescalar);
void EEPROM_write(uint8_t *data);
void EEPROM_read(uint8_t *data);

#endif /* EEPROM_H_ */