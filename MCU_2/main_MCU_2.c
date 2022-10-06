/*
 * MCU_2.c
 *
 * Created: 10/1/2022 12:41:24 PM
 * Author : 3zz
 */ 

#include "MCAL_2/UART_Driver_2/UART_2.h"
#include "MCAL_2/DIO_Driver_2/DIO_2.h"

uint8_t data;
int main(void)
{
    UART_init(BAUD_rate,Data_bits,Stop_bits);
	DIO_init(port_A,PIN_0,OUT);
    while (1) 
    {
		data = UART_receive();
		if(data)
			DIO_write(port_A,0,HIGH);
		else
			DIO_write(port_A,0,LOW);
    }
}

