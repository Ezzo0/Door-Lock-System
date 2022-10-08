/*
 * TWI.c
 *
 * Created: 10/6/2022 2:38:44 PM
 *  Author: 3zz
 */ 

#include "TWI_2.h"

void TWI_init()
{
	TWSR = 0x00; // Clear Status Register
	TWBR = BitRate; // Set Bit Rate register
}


void TWI_start(uint8_t dev_addr)
{
	set_pin(TWCR,TWINT); // Clear interrupt flag in control register
	set_pin(TWCR,TWSTA); // Set start bit in control register
	set_pin(TWCR,TWEN); // Enable TWI 
	while (!( TWCR & (1 << TWINT) )); // Wait for TWINT Flag set
	
	TWDR = dev_addr;
	set_pin(TWCR,TWINT); // Clear interrupt flag in TWI control register
	set_pin(TWCR,TWEN); // Enable TWI
	while (!( TWCR & (1 << TWINT) )); // Wait for TWINT Flag set
}


void TWI_write_addr(uint8_t mem_addr)
{
	TWDR = mem_addr;
	set_pin(TWCR,TWINT); // Clear interrupt flag in TWI control register
	set_pin(TWCR,TWEN); // Enable TWI
	while (!( TWCR & (1 << TWINT) )); // Wait for TWINT Flag set
}

void TWI_write_data(uint8_t data)
{
	TWDR = data;
	set_pin(TWCR,TWINT); // Clear interrupt flag in TWI control register
	set_pin(TWCR,TWEN); // Enable TWI
	while (!( TWCR & (1 << TWINT) )); // Wait for TWINT Flag set
}


void TWI_read_ack(uint8_t *data){
	// Enable ACK, TWI
	set_pin(TWCR,TWINT);
	set_pin(TWCR,TWEN);
	set_pin(TWCR,TWEA);
	
	while (!( TWCR & (1 << TWINT) )); // Wait for TWINT Flag set
	
	*data = TWDR;
}

void TWI_read_nack(uint8_t *data){
	// Enable ACK, TWI
	set_pin(TWCR,TWINT);
	set_pin(TWCR,TWEN);
	
	while (!( TWCR & (1 << TWINT) )); // Wait for TWINT Flag set
	
	*data = TWDR;
}


void TWI_stop()
{
	TWCR = (1 << TWSTO) | (1 << TWINT) | (1 << TWEN);// Enable TWI, generate stop
	while( TWCR & (1 << TWSTO) );	// Wait until stop condition execution 
}

EN_returnStatus_t TWI_get_status(){
	uint8_t status;
	status = (TWSR & 0xF8); // Reading TWI status register
	
	return status;
}