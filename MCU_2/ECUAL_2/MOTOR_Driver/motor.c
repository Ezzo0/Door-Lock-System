/*
 * motor.c
 *
 * Created: 10/11/2022 10:40:46 PM
 *  Author: 3zz
 */ 
#include "motor.h"

void motor_init()
{
	DIO_init(port_B,PIN_5,OUT);
	DIO_init(port_B,PIN_6,OUT);
	DIO_init(port_B,PIN_7,OUT);
}

void motor_turn_cw()
{
	DIO_write(port_B,PIN_5,HIGH);
	DIO_write(port_B,PIN_6,HIGH);
	DIO_write(port_B,PIN_7,LOW);
}

void motor_turn_anti_cw()
{
	DIO_write(port_B,PIN_5,HIGH);
	DIO_write(port_B,PIN_6,LOW);
	DIO_write(port_B,PIN_7,HIGH);
}

void morot_brake()
{
	DIO_write(port_B,PIN_5,HIGH);
	DIO_write(port_B,PIN_6,HIGH);
	DIO_write(port_B,PIN_7,HIGH);
}