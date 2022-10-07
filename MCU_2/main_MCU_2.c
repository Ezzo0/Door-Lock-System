/*
 * MCU_2.c
 *
 * Created: 10/1/2022 12:41:24 PM
 * Author : 3zz
 */ 

#include "MCAL_2/UART_Driver_2/UART_2.h"
#include "MCAL_2/DIO_Driver_2/DIO_2.h"
#include "MCAL_2/TWI_Driver_2/TWI_2.h"
#include "ECUAL_2/EEPROM/EEPROM.h"

uint8_t data = 0xFF;
uint8_t data_read;
int main(void)
{
	DDRB = 0xFF;
    EEPROM_inti(1);
	EEPROM_write(&data);
	_delay_ms(1000);
    EEPROM_read(&data_read);
	PORTB = data_read;
	
    while (1) 
    {
		
    }
}

