/*
 * motor.h
 *
 * Created: 10/11/2022 10:40:36 PM
 *  Author: 3zz
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#include "../../MCAL_2/DIO_Driver_2/DIO_2.h"
#include "../../MCAL_2/TIMER_Driver_2/timer_2.h"

#define enable_pin	PIN_5
#define cw_pin		PIN_6
#define acw_pin		PIN_7



void motor_init();
void motor_turn_cw();
void motor_turn_anti_cw();
void motor_brake();
void motor_response();


#endif /* MOTOR_H_ */