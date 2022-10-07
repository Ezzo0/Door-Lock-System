/*
 * EEPROM.h
 *
 * Created: 10/7/2022 3:17:48 PM
 *  Author: mosta
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include "../../MCAL_2/TWI_Driver_2/TWI_2.h"
#include "../../Utilities_2/Macros_2.h"

void EEPROM_Read (uint8_t address, uint8_t* ptr);
void EEPROM_Write (char data, char address);



#endif /* EEPROM_H_ */