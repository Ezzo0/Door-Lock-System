/*
 * APP.h
 *
 * Created: 10/1/2022 8:32:49 AM
 *  Author: mosta
 */ 


#ifndef APP_H_
#define APP_H_

#include "../MCAL_2/DIO_Driver_2/DIO_2.h"
#include "../MCAL_2/UART_Driver_2/UART_2.h"
#include "../ECUAL_2/EEPROM/EEPROM.h"
#include "../ECUAL_2/MOTOR_Driver/motor.h"


#define Password_was_not_entered 0xFF
#define Password_was_entered 1

#define Matched 1
#define No_Match 0

#define First_option '1'
#define Second_option '2'

#define Not_choosed 0
#define Choosed 1


void app_init();
void app_start();
void reset_pass_array();
void compare_incoming_pass();
void set_new_pass();




#endif /* APP_H_ */