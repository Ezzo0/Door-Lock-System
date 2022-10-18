/*
 * timer.h
 *
 * Created: 10/15/2022 12:15:49 PM
 *  Author: 3zz
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "../DIO_Driver_2/DIO_2.h"
#include "../INTURREPTS_Driver_2/interrupts_2.h"

// Modes Macros
#define normal 'n'
#define pwm 'p'
#define ctc 'c'
#define fast_pwm 'f'
#define Timer_initial_value 11
#define Timer_prescalar 1024

void timer2_select_mode(uint8_t mode);
void timer2_set_initial_value(uint8_t value);
void timer2_timer_start(int prescalar);
void timer2_timer_reset();
void timer2_timer_stop();

void TIMER_0_init();
void TIMER_0_set_init_value(uint16_t val);
void TIMER_0_start(float delay);
void TIMER_0_stop();
void TIMER_0_delay(float delay);
void TIMER_reset();



#endif /* TIMER_H_ */