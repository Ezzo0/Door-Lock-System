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

uint8_t data_w = 5;
uint8_t data_r;
uint8_t *p = &data_r;

int main(void)
{
	uint8_t pass_w[16] = "mostafa";
	uint8_t pass_r[16];
	DDRB = 0xFF;
    EEPROM_init();
	
	EEPROM_write_string(pass_w);
	_delay_ms(500);
	EEPROM_read_byte(&p);
	_delay_ms(500);
	PORTB = data_r;
	
    while (1) 
    {
		
    }
}

