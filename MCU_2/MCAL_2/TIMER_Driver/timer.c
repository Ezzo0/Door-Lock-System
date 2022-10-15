/*
 * timer.c
 *
 * Created: 10/15/2022 12:15:57 PM
 *  Author: 3zz
 */ 

#include "timer.h"

uint8_t number_of_overflows = 0; // variable for counting the overflows

/************************************************************************/
/* Timer 2 functions                                                    */
/************************************************************************/

void timer2_select_mode(uint8_t mode)
{
	switch(mode)
	{
		case normal:
		TCCR2 = 0x00; // set timer 2 to Normal mode
		break;
		
		case pwm:
		TCCR2 |= (1 << WGM20); // set timer 0 to PWM mode
		break;
		
		case ctc:
		TCCR2 |= (1 << WGM21); // set timer 0 to CTC mode
		break;
		
		case fast_pwm:
		TCCR2 |= ((1 << WGM20) | (1 << WGM21)); // set timer 0 to Fast PWM mode
		break;
		
		default:
		{
			//Error
		}
	}
}

void timer2_set_initial_value(uint8_t value)
{
	TCNT2 = value;
}

void timer2_timer_start(int prescalar)
{
	switch(prescalar)
	{
		case 0:
		TCCR2 |= (1 << CS20); // choose no prescalar
		break;
		
		case 8:
		TCCR2 |= (1 << CS21); // choose prescalar of 8
		break;
		
		case 32:
		TCCR2 |= ((1 << CS20) | (1 << CS21)); // choose prescalar of 32
		break;
		
		case 64:
		TCCR2 |= (1 << CS22); // choose prescalar of 64
		break;
		
		case 128:
		TCCR2 |= ((1 << CS20) | (1 << CS22)); // choose prescalar of 128
		break;
		
		case 256:
		TCCR2 |= ((1 << CS21) | (1 << CS22)); // choose prescalar of 256
		break;
		
		case 1024:
		TCCR2 |= ((1 << CS20) | (1 << CS21) | (1 << CS22)); // choose prescalar of 1024
		break;
		
		default:
		// Error Handling
		break;
	}
}

void timer2_timer_reset()
{
	number_of_overflows = 0;
	timer2_set_initial_value(Timer_initial_value);
}

void timer2_timer_stop()
{
	number_of_overflows = 0;
	TCCR2 = 0x00; // stop the timer
}

// Timer 2 over flow interrupt service routine function
ISR(TIMER_2_OVF)
{
	timer2_set_initial_value(Timer_initial_value);
	++number_of_overflows;
	if(number_of_overflows)
	{
		DIO_toggle(port_D,PIN_6);
	}
}