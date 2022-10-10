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
	TWI_start(0b10100110+Write);
	TWI_write_addr(0x00);
	TWI_write_addr(0x00);
	
	TWI_write_data(data);
	
	TWI_stop();
}

void EEPROM_read_byte(uint8_t **data)
{
	TWI_start(0b10100110+Write);
	TWI_write_addr(0x00);
	TWI_write_addr(0x00);
	TWI_stop();
	TWI_start(0b10100110+Read);
	TWI_read_nack(*data);
	TWI_stop();
}

void EEPROM_write_string(uint8_t *data)
{
	TWI_start(0b10100110+Write);
	TWI_write_addr(0x00);
	TWI_write_addr(0x00);
	
	for(uint8_t i=0; *(data+i)!='\0'; i++){
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
	uint8_t temp=0;
	for(uint8_t i=0; *(data+i+1)!='\0'; i++){
		TWI_read_ack(data+i);
		temp = i+1;
	}
	TWI_read_nack(data+temp);
	TWI_stop();
}