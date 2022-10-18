/*
 * motor.c
 *
 * Created: 10/11/2022 10:40:46 PM
 *  Author: 3zz
 */ 
#include "motor.h"

void motor_init()
{
	DIO_init(port_B,enable_pin,OUT);
	DIO_init(port_B,cw_pin,OUT);
	DIO_init(port_B,PIN_7,OUT);
}

void motor_turn_cw()
{
	DIO_write(port_B,enable_pin,HIGH);
	DIO_write(port_B,cw_pin,HIGH);
	DIO_write(port_B,acw_pin,LOW);
}

void motor_turn_anti_cw()
{
	DIO_write(port_B,enable_pin,HIGH);
	DIO_write(port_B,cw_pin,LOW);
	DIO_write(port_B,acw_pin,HIGH);
}

void motor_brake()
{
	DIO_write(port_B,enable_pin,HIGH);
	DIO_write(port_B,cw_pin,HIGH);
	DIO_write(port_B,acw_pin,HIGH);
}

void motor_response()
{
	TIMER_0_delay(1000);
	motor_turn_cw();
	TIMER_0_delay(1500);
	motor_brake();
	TIMER_0_delay(1500);
	motor_turn_anti_cw();
	TIMER_0_delay(2000);
	motor_brake();
}