/*
 * lcd.h
 *
 * Created: 10/3/2022 1:45:43 PM
 *  Author: 3zz
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "../../MCAL_1/DIO_Driver_1/DIO_1.h"

// Macros
#define LCD_commandData_dir DDRC
#define LCD_commandData_port PORTC
#define LCD_control_port PORTD
#define Control_PINS_port port_D
#define RS_PIN PIN_5
#define RW_PIN PIN_6
#define E_PIN PIN_7

#define Password_was_not_entered 0
#define Password_was_entered 1

void LCD_8_bit_init();
void LCD_8_bit_sendCommand(uint8_t cmnd);
void LCD_8_bit_sendChar(uint8_t char_data);
void LCD_8_bit_cursor_left();
void LCD_8_bit_cursor_right();
void LCD_8_bit_clear_all();
void LCD_8_bit_welcoming();
void LCD_8_bit_display_options();
void LCD_8_bit_enter_pass();
void LCD_8_bit_sendString(uint8_t *string_data);


#endif /* LCD_H_ */