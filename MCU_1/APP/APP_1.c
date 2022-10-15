/*
 * APP.c
 *
 * Created: 10/1/2022 8:32:38 AM
 *  Author: mosta
 */ 

#include "APP_1.h"

uint8_t password[17] = {'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
uint8_t keypadInput;
uint8_t cnt = 0;
uint8_t option = Not_choosed;
uint8_t choosed_option = Not_choosed;
uint8_t password_checker;
uint8_t matched_password = Matched;
uint8_t wrong_password = 0;

void app_init()
{
	Keypad_init();
	LCD_8_bit_init();
	UART_init();
}

void reset_password_array(uint8_t *array)
{
	for(uint8_t i = 0; i < 17; ++i)
	{
		array[i] = '\0';
	}
	cnt = 0;
}

void firstOption()
{
	while (1)
	{
		keypadInput = Keypad_pressed();
		
		if(keypadInput == '=')
		{
			if(cnt >= 4)
			{
				UART_transmitString(password);
				LCD_8_bit_clear_all();
				LCD_8_bit_loading();
				_delay_ms(1000);
				reset_password_array(password);
				break;
			}
			else
			{
				LCD_8_bit_clear_all();
				LCD_8_bit_4_chars_needed();
				_delay_ms(2000);
				reset_password_array(password);
				LCD_8_bit_clear_all();
				LCD_8_bit_enter_pass();
			}
		}
		else if(keypadInput == 'c')
		{
			LCD_8_bit_clear_all();
			LCD_8_bit_enter_pass();
			reset_password_array(password);
		}
		else
		{
			if(keypadInput != NOT_pressed)
			{
				if(cnt < 16)
				{
					LCD_8_bit_sendChar(keypadInput);
					password[cnt] = keypadInput;
					++cnt;
				}
			}
		}
	}
	if(password_checker == Password_was_entered)
		matched_password = UART_receive();
}

void secondOption()
{
	firstOption();
	if(matched_password == Matched)
	{
		LCD_8_bit_clear_all();
		LCD_8_bit_enter_new_pass();
		firstOption();
		choosed_option = Not_choosed;
		option = Not_choosed;
		wrong_password = 0;
	}
	else
	{
		++wrong_password;
		UART_transmit(wrong_password);
		LCD_8_bit_clear_all();
		LCD_8_bit_wrong_pass();
		_delay_ms(2000);
		LCD_8_bit_clear_all();
		LCD_8_bit_enter_pass();
	}
}

void app_start()
{	
	while(1)
	{
		password_checker = int_eeprom_r(0x00);
		UART_transmit(password_checker);
		if(password_checker == Password_was_not_entered)
		{
			LCD_8_bit_enter_new_pass();
			firstOption();
			int_eeprom_w(0x00,1);
		}
		
		else if(password_checker == Password_was_entered)
		{
			
			if(choosed_option == Not_choosed)
			{
				LCD_8_bit_clear_all();
				LCD_8_bit_display_options();
				option = Keypad_pressed();
				while(option != First_option && option != Second_option)
					option = Keypad_pressed();
				
				LCD_8_bit_clear_all();
				LCD_8_bit_enter_pass();
				choosed_option = Choosed;
			}
			
			UART_transmit(choosed_option);
			if(option == First_option)
			{
				UART_transmit(option);
				firstOption();
				if(matched_password == Matched)
				{
					LCD_8_bit_clear_all();
					LCD_8_bit_opening();
					_delay_ms(3000);
					LCD_8_bit_clear_all();
					LCD_8_bit_closing();
					_delay_ms(2000);
					choosed_option = Not_choosed;
					option = Not_choosed;
					wrong_password = 0;
				}
				else
				{
					++wrong_password;
					UART_transmit(wrong_password);
					LCD_8_bit_clear_all();
					LCD_8_bit_wrong_pass();
					_delay_ms(2000);
					LCD_8_bit_clear_all();
					LCD_8_bit_enter_pass();
				}
			}
			
			else if(option == Second_option)
			{
				UART_transmit(option);
				secondOption();
			}
		}
	}
}
