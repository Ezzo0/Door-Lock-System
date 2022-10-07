/*
 * EEPROM.c
 *
 * Created: 10/7/2022 3:17:38 PM
 *  Author: mosta
 */ 

#include "EEPROM.h"

void EEPROM_Read (uint8_t address, uint8_t* ptr) 
{
	//TWI_start();
//
	//TWI_send_address(10100010, Write);    //send device address
//
	//TWI_send_address(address);            //send memory location

	
}

void EEPROM_Write (char data, char address)

{

	//TWI_start();
//
	//TWI_send_address(0xA8); //slave address is 1010.100 and a 0 in the 8th bit to indicate Writting.
//
	//TWI_send_address(address);

	//TWI_Write(data);
//
	//TWI_Stop();

}