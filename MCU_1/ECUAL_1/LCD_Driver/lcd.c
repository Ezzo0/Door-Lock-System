/*
 * lcd.c
 *
 * Created: 10/3/2022 1:45:33 PM
 *  Author: 3zz
 */ 

#include "lcd.h"

// Displayed strings
uint8_t welcomeStr[] = "Welcome To";
uint8_t welcomeStr_2[] = "Door Lock System";
uint8_t enter_pass_str[] = "Enter password";
uint8_t option_1[] = "1.Open the door";
uint8_t option_2[] = "2.Alter Password";
uint8_t password_checker = Password_was_not_entered;

void LCD_8_bit_init()
{
	LCD_commandData_dir = 0xFF; // Make LCD command port direction as o/p
	// Make LCD control pins in the MCU direction as o/p
	DIO_init(Control_PINS_port,RS_PIN,OUT);
	DIO_init(Control_PINS_port,RW_PIN,OUT);
	DIO_init(Control_PINS_port,E_PIN,OUT);
	// LCD power on delay
	_delay_ms(20);
	LCD_8_bit_sendCommand(0x38); // Initialization of 16x2 LCD in 8 bit mode
	LCD_8_bit_sendCommand(0x0E); // Display on and cursor blinking
	LCD_8_bit_sendCommand(0x06); // Auto increment for the cursor
	LCD_8_bit_sendCommand(0x01); // Clear Display
	LCD_8_bit_sendCommand(0x80); // Cursor at home position
	LCD_8_bit_welcoming(); // Displaying welcoming words
	_delay_ms(1000); // wait for 1 sec
	LCD_8_bit_clear_all(); // Clear every char on LCD
	
	if(password_checker == Password_was_not_entered)
		LCD_8_bit_enter_pass();
	else
		LCD_8_bit_display_options();
}

void LCD_8_bit_sendCommand(uint8_t cmnd)
{
	LCD_commandData_port = cmnd;
	clr_pin(LCD_control_port,RS_PIN); // RS = 0 command register
	clr_pin(LCD_control_port,RW_PIN); // RW = 0 write operation
	set_pin(LCD_control_port,E_PIN); // Enable pulse
	_delay_ms(1);
	clr_pin(LCD_control_port,E_PIN);
	_delay_ms(3);
}

void LCD_8_bit_sendChar(uint8_t char_data) // Writing function on LCD
{
	LCD_commandData_port = char_data;
	set_pin(LCD_control_port,RS_PIN); // RS = 1 data register
	clr_pin(LCD_control_port,RW_PIN); // RW = 0 write operation
	set_pin(LCD_control_port,E_PIN); // Enable pulse
	_delay_ms(1);
	clr_pin(LCD_control_port,E_PIN);
	_delay_ms(3);
}

void LCD_8_bit_cursor_left()
{
	LCD_8_bit_sendCommand(0x10); // Move cursor to left
}

void LCD_8_bit_cursor_right()
{
	LCD_8_bit_sendCommand(0x14); // Move cursor to right
}

void LCD_8_bit_clear_all()
{
	LCD_8_bit_sendCommand(0x01); // Clear Display
	LCD_8_bit_sendCommand(0x80); // Cursor at home position
}

void LCD_8_bit_welcoming()
{
	LCD_8_bit_sendString(welcomeStr); // Displaying welcome words
	LCD_8_bit_sendCommand(0xC0); // Cursor at 2nd line
	LCD_8_bit_sendString(welcomeStr_2); // Displaying second welcome words
}

void LCD_8_bit_display_options()
{
	LCD_8_bit_sendString(option_1); // Displaying option words
	LCD_8_bit_sendCommand(0xC0); // Cursor at 2nd line
	LCD_8_bit_sendString(option_2); // Displaying second option words
}

void LCD_8_bit_enter_pass()
{
	LCD_8_bit_sendString(enter_pass_str); // Displaying option words
	LCD_8_bit_sendCommand(0xC0); // Cursor at 2nd line
}

void LCD_8_bit_sendString(uint8_t *string_data)
{
	for (uint8_t cnt = 0; *(string_data+cnt) != '\0'; ++cnt) // Loop for sending each char in the string to the LCD
		LCD_8_bit_sendChar(*(string_data+cnt)); // call the writing function on LCD
}