/*
 * MCU_2.c
 *
 * Created: 10/1/2022 12:41:24 PM
 * Author : 3zz
 */ 

#include "ECUAL_2/MOTOR_Driver/motor.h"

int main(void)
{
	//app_init();
	//app_start();
	motor_init();
	motor_turn_cw();
	_delay_ms(2000);
	motor_turn_anti_cw();
	_delay_ms(1512);
	morot_brake();
}

