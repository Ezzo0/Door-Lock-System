/*
 * timer.c
 *
 * Created: 10/15/2022 12:15:57 PM
 *  Author: 3zz
 */ 

#include "timer_2.h"


/************************************************************************/
/* Timer 2                                                     */
/************************************************************************/
uint8_t number_of_overflows = 0; // variable for counting the overflows

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


/************************************************************************/
/* Timer 0                                                   */
/************************************************************************/

uint16_t max_ovf;
uint16_t ovf_cnt=0;
uint16_t init_val;


void TIMER_0_init()
{
	//selecting normal mode
	TCCR0 |= ((0<<3) | (0<<6));
}

void TIMER_0_set_init_value(uint16_t val)
{
	//assigning initial value after calculation
	TCNT0 = val;
}

void TIMER_0_start(float delay)
{
	max_ovf = delay/0.262144;
	if(delay/0.262144 > max_ovf){
		max_ovf++;
	}
	
	init_val = 256 - ((delay/0.001024)/max_ovf);
	
	TIMER_0_set_init_value(init_val);
	
	// Selecting 1024 prescaler
	TCCR0 |= ((1<<0) | (1<<2));
	
	// Waiting the overflow counter to reach max ovf value
	while(ovf_cnt <max_ovf);
}


void TIMER_0_stop()
{
	// Setting control register to 0 (no prescaler) to stop the timer
	TCCR0 = 0;
	
	// Resetting overflow counter
	ovf_cnt = 0;
}

// Delay function that perform the delay
void TIMER_0_delay(float delay)
{
	delay /= 1000;
	TIMER_0_start(delay);
	TIMER_0_stop();
}

// This function resets timer without stopping it
void TIMER_reset()
{
	TIMER_0_set_init_value(init_val);
	ovf_cnt = 0;
}

// Timer_0 overflow interrupt
ISR(TIMER_0_OVF){
	// Resetting initial value for the next timer cycle
	TIMER_0_set_init_value(init_val);
	
	// Incrementing overflow variable
	ovf_cnt++;
	
}