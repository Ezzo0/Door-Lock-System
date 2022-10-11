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
#include "../MCAL_1/Internal_EEPROM_Driver/internal_eeprom.h"

#define Zero_char_pressed 0
#define One_char_pressed 1
#define Two_char_pressed 2
#define Three_char_pressed 3

#define Password_was_not_entered 0xFF
#define Password_was_entered 1

#define First_option '1'
#define Second_option '2'
#define Not_choosed 0
#define Choosed 1

#define Matched 1
#define No_Match 0

void app_init();
void app_start();
void reset_password_array(uint8_t *array);
void firstOption();
void secondOption();


#endif /* APP_H_ */