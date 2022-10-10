/*
 * APP.c
 *
 * Created: 10/1/2022 8:32:38 AM
 *  Author: mosta
 */ 

#include "APP_1.h"

uint8_t password[17] = {'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
uint8_t clr[17] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,'\0'};
uint8_t keypadInput;
uint8_t cnt = 0;
uint8_t option;
extern uint8_t password_checker;

void app_init()
{
	Keypad_init();
	LCD_8_bit_init();
	UART_init();
	DDRB = 0xFF;
}

void app_start()
{
	while(1)
	{
		if(password_checker == Password_was_entered)
		{
			keypadInput = Keypad_pressed();
			set_pin(PORTB,PIN_0);
			clr_pin(PORTB,PIN_1);
			if(keypadInput == First_option)
			{
				LCD_8_bit_clear_all();
				LCD_8_bit_enter_pass();
				password_checker = Password_was_not_entered;
			}
			else if(keypadInput == Second_option)
			{
				LCD_8_bit_clear_all();
				LCD_8_bit_enter_pass();
				password_checker = Password_was_not_entered;
			}
		}
		else if(password_checker == Password_was_not_entered)
		{
			keypadInput = Keypad_pressed();
			set_pin(PORTB,PIN_1);
			clr_pin(PORTB,PIN_0);
			if(keypadInput == '=')
			{
				UART_transmitString(password);
				password_checker = Password_was_entered;
				LCD_8_bit_clear_all();
				LCD_8_bit_display_options();
			}
			
			else if(keypadInput == 'c')
			{
				LCD_8_bit_clear_all();
				LCD_8_bit_enter_pass();
			}
			
			else
			{
				if(keypadInput != NOT_pressed)
				{
					LCD_8_bit_sendChar(keypadInput);
					password[cnt] = keypadInput;
					++cnt;
				}
			}
		}
	}
}
