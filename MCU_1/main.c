/*
 * MCU_1.c
 *
 * Created: 10/1/2022 8:30:07 AM
 * Author : mosta
 */ 

#include "MCAL/UART/UART.h"

uint16_t data;


int main(void)
{
    UART_init();
    while (1) 
    {
		_delay_ms(1000);
		UART_transmit(1);
		_delay_ms(1000);
		UART_transmit(0);
    }
}

