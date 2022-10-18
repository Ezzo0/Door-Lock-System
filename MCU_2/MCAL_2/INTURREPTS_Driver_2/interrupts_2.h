/*
 * interrupts.h
 *
 * Created: 10/15/2022 12:34:40 AM
 *  Author: 3zz
 */ 


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include "../../Utilities_2/Macros_2.h"

// Macros of Vectors
#define TIMER_2_OVF __vector_5
#define TIMER_0_OVF __vector_11

// Macro of interrupt service routine function
#define ISR(INT_VECT) void INT_VECT(void) __attribute__((signal,used));\
void INT_VECT(void)

void enable_global_interrupts();
void timer2_enable_overflow_interrupt();
void timer0_enable_overflow_interrupt();


#endif /* INTERRUPTS_H_ */