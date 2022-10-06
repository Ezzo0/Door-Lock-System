/*
 * DIO_2.c
 *
 * Created: 10/1/2022 12:42:19 PM
 *  Author: 3zz
 */ 

#include "DIO_2.h"

void DIO_init(uint8_t portnum,uint8_t pinnum, uint8_t direction)
{
	switch(portnum)
	{
		case port_A:
			if(direction == IN)
				clr_pin(DDRA,pinnum); // Make pin number (pinnum) in port A an input pin
			
			else if(direction == OUT)
				set_pin(DDRA,pinnum);	// Make pin number (pinnum) in port A an output pin
			
			else
			{
				//Error Handling
			}
		break;
		
		case port_B:
			if(direction == IN)
				clr_pin(DDRB,pinnum); // Make pin number (pinnum) in port B an input pin
			
			else if(direction == OUT)
				set_pin(DDRB,pinnum);	// Make pin number (pinnum) in port B an output pin
			
			else
			{
				//Error Handling
			}
		break;
		
		case port_C:
			if(direction == IN)
				clr_pin(DDRC,pinnum); // Make pin number (pinnum) in port C an input pin
		
			else if(direction == OUT)
				set_pin(DDRC,pinnum);	// Make pin number (pinnum) in port C an output pin
		
			else
			{
				//Error Handling
			}
		break;
		
		case port_D:
			if(direction == IN)
				clr_pin(DDRD,pinnum); // Make pin number (pinnum) in port D an input pin
		
			else if(direction == OUT)
				set_pin(DDRD,pinnum);	// Make pin number (pinnum) in port D an input pin
		
			else
			{
				//Error Handling
			}
		break;
		
		default:
		{
			//Error Handling
		}
	}
}

void DIO_write(uint8_t portnum,uint8_t pinnum, uint8_t value)
{
	switch(portnum)
	{
		case port_A:
			if(value == LOW)
				clr_pin(PORTA,pinnum); // make pin number (pinnum) in port A has a value of 0
			
			else if(value == HIGH)
				set_pin(PORTA,pinnum); // make pin number (pinnum) in port A has a value of 1
		
			else
			{
				//Error Handling
			}
		break;
		
		case port_B:
			if(value == LOW)
				clr_pin(PORTB,pinnum); // make pin number (pinnum) in port B has a value of 0
		
			else if(value == HIGH)
				set_pin(PORTB,pinnum); // make pin number (pinnum) in port B has a value of 1
		
			else
			{
				//Error Handling
			}
		break;
		
		case port_C:
			if(value == LOW)
				clr_pin(PORTC,pinnum); // make pin number (pinnum) in port C has a value of 0
		
			else if(value == HIGH)
				set_pin(PORTC,pinnum); // make pin number (pinnum) in port C has a value of 1
		
			else
			{
				//Error Handling
			}
		break;
		
		case port_D:
			if(value == LOW)
				clr_pin(PORTD,pinnum); // make pin number (pinnum) in port D has a value of 0
		
			else if(value == HIGH)
				set_pin(PORTD,pinnum); // make pin number (pinnum) in port D has a value of 1
		
			else
			{
				//Error Handling
			}
		break;
		
		default:
		{
			//Error Handling
		}
	}
}

void DIO_toggle(uint8_t portnum,uint8_t pinnum)
{
	switch(portnum)
	{
		case port_A:
			tgl_pin(PORTA,pinnum); // toggle pin number (pinnum) in port A
		break;
		
		case port_B:
			tgl_pin(PORTB,pinnum); // toggle pin number (pinnum) in port B
		break;
		
		case port_C:
			tgl_pin(PORTC,pinnum); // toggle pin number (pinnum) in port C
		break;
		
		case port_D:
			tgl_pin(PORTD,pinnum); // toggle pin number (pinnum) in port D
		break;
		
		default:
		{
			//Error Handling
		}
	}
}

void DIO_read(uint8_t portnum,uint8_t pinnum, uint8_t *value)
{
	switch(portnum)
	{
		case port_A:
			*value = get_pin(PINA,pinnum); // save the value of pin number (pinnum) in port A in a variable
		break;
		
		case port_B:
			*value = get_pin(PINB,pinnum); // save the value of pin number (pinnum) in port B in a variable
		break;
		
		case port_C:
			*value = get_pin(PINC,pinnum); // save the value of pin number (pinnum) in port C in a variable
		break;
		
		case port_D:
			*value = get_pin(PIND,pinnum); // save the value of pin number (pinnum) in port D in a variable
		break;
		
		default:
		{
			//Error Handling
		}
	}
}

