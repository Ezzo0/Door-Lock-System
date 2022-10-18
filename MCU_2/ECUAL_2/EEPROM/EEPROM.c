/*
 * EEPROM.c
 *
 * Created: 10/7/2022 8:11:32 PM
 *  Author: 3zz
 */ 

#include "EEPROM.h"

void EEPROM_init()
{
	TWI_init();
}

void EEPROM_write_byte(uint8_t data)
{
	// sending the start condition and the device write address
	TWI_start(0b10100110+Write);
	
	/* sending the memory location we want to write to */
	TWI_write_addr(0x00);
	TWI_write_addr(0x00);
	
	// sending the data 
	TWI_write_data(data);
	
	// sending the stop condition
	TWI_stop();
}

void EEPROM_read_byte(uint8_t **data)
{
	// sending the start condition and the device write address
	TWI_start(0b10100110+Write);
	
	// sending memory location we want to read
	TWI_write_addr(0x00);
	TWI_write_addr(0x00);
	
	// stopping the first procedure as we moved the memory pointer to the desired location without writing
	TWI_stop();
	
	// doing a repeated start with read address
	TWI_start(0b10100110+Read);
	
	// reading data from the EEPORM
	TWI_read_nack(*data);
	
	// generating stop condition
	TWI_stop();
}

void EEPROM_write_string(uint8_t *data)
{
	TWI_start(0b10100110+Write);
	TWI_write_addr(0x00);
	TWI_write_addr(0x00);
	
	// writing data up to 16 characters
	for(uint8_t i=0; i<16; i++){
		TWI_write_data(*(data+i));
	}
	
	TWI_stop();
}

void EEPROM_read_string(uint8_t *data)
{
	TWI_start(0b10100110+Write);
	TWI_write_addr(0x00);
	TWI_write_addr(0x00);
	TWI_stop();
	TWI_start(0b10100110+Read);
	
	// reading data up to 16 characters
	for(uint8_t i=0; i<16; i++){
		TWI_read_ack(data+i);
	}
	
	TWI_stop();
}

