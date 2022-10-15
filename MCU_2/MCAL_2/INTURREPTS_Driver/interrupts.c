/*
 * interrupts.c
 *
 * Created: 10/15/2022 12:34:48 AM
 *  Author: 3zz
 */ 

#include "interrupts.h"

void enable_global_interrupts()
{
	SREG |= (1 << 7); // set bit 7 in SREG register to one
}

void timer2_enable_overflow_interrupt()
{
	TIMSK |= (1 << TOIE2); // set bit TOIE2 in TIMSK register to one
}