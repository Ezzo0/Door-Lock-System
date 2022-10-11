/*
 * internal_eeprom.c
 *
 * Created: 10/10/2022 11:40:31 PM
 *  Author: 3zz
 */ 
#include "internal_eeprom.h"

void int_eeprom_w(uint8_t addr, uint8_t data)
{
	//Wait for completion of previous write
	while(EECR & (1 << EEWE));
	
	//Set up address and data registers
	EEAR = addr;
	EEDR = data;
	
	//Write logical 1 to EEMWE
	set_pin(EECR,EEMWE);
	
	//Start eeprom write by setting EEWE
	set_pin(EECR,EEWE);
	
}

uint8_t int_eeprom_r(uint8_t addr)
{
	//Wait for completion of previous write
	while(EECR & (1 << EEWE));
	
	//Set up address register
	EEAR=addr;
	
	//Start eeprom read by writing EERE
	set_pin(EECR,EERE);
	
	/*Return data from data register*/
	return EEDR;
}