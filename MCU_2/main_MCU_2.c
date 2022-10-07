/*
 * MCU_2.c
 *
 * Created: 10/1/2022 12:41:24 PM
 * Author : 3zz
 */ 

#include "MCAL_2/UART_Driver_2/UART_2.h"
#include "MCAL_2/DIO_Driver_2/DIO_2.h"
#include "MCAL_2/TWI_Driver_2/TWI_2.h"

uint8_t data;
uint8_t btee5;

int main(void)
{
	DDRB = 0xFF;
    TWI_init(1);
	
	if(TWI_start()==EVENT_OK){
		if(TWI_send_address(0x10, Read) == SLA_R_ACK_SENT){
			if(TWI_data_event(&data, Read, NOT_ACK)== DATA_R_NACK_SENT){
				TWI_stop();
			}
		}
	}
	
	if(TWI_start()==EVENT_OK){
		if(TWI_send_address(0x10, Write) == SLA_W_ACK_SENT){
			if(TWI_data_event(&data, Write, ACK)== DATA_W_NACK_SENT){
				TWI_stop();
			}
		}
	}
	
	PORTB = data;
	
	
    while (1) 
    {
		
		
		
    }
}

