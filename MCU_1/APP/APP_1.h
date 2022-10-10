/*
 * APP.h
 *
 * Created: 10/1/2022 8:32:49 AM
 *  Author: mosta
 */ 


#ifndef APP_H_
#define APP_H_

#include "../MCAL_1/UART_Driver_1/UART_1.h"
#include "../ECUAL_1/Keypad_Driver/keypad.h"
#include "../ECUAL_1/LCD_Driver/lcd.h"

#define Zero_char_pressed 0
#define One_char_pressed 1
#define Two_char_pressed 2
#define Three_char_pressed 3

#define First_option '1'
#define Second_option '2'

void app_init();
void app_start();


#endif /* APP_H_ */