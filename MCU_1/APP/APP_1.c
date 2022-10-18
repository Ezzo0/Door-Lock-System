/*
 * APP.c
 *
 * Created: 10/1/2022 8:32:38 AM
 *  Author: mosta
 */ 

#include "APP_1.h"

// Array to store password from keypad to be sent to the MCU_2 through UART
uint8_t password[17] = {'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
	
// Variable to return keypressed() function value into
uint8_t keypadInput;

// Variable to count number of characters the user inputs through the keypad 
uint8_t cnt = 0;

// Variable to store the option chose by the user to be sent to MCU_2 through UART
uint8_t option = Not_choosed;

// Variable to store whether an option is chosen or not to be sent to MCU_2 through UART
uint8_t choosed_option = Not_choosed;

/* Variable that stores the value of the pass_check flag in the MCU_1 internal EEPROM to 
   check if it is the first time the system operates or not */
uint8_t password_checker;

// Variable to store whether an password is matched with saved password (in External EEPROM) or not to be recieved from MCU_2 through UART
uint8_t matched_password = Matched;

// Variable to count the number of times the user entered incorrect password 
uint8_t wrong_password = 0;


// Function that initializes all driver
void app_init()
{
	Keypad_init();
	LCD_8_bit_init();
	UART_init();
}

// Function to reset password array that is filled with keypad input (lcd is cleared after)
void reset_password_array(uint8_t *array)
{
	for(uint8_t i = 0; i < 17; ++i)
	{
		array[i] = '\0';
	}
	cnt = 0;					// resets the variable to keep track of the input count
}


// Function that takes input password from the user and verify its length then send it to MCU_2 through UART and waits for the  matched_password flag
void firstOption()
{
	while (1)
	{
		// Variable that stores the return char value from Keypad_pressed() function every iteration
		keypadInput = Keypad_pressed();
		
		// '=' means the user wants to submit the password
		if(keypadInput == '=')
		{
			// Checking if the length condition is met
			if(cnt >= 4)
			{
				UART_transmitString(password);		// send password array to MCU_2 through UART
				LCD_8_bit_clear_all();
				LCD_8_bit_loading();				// displays "loading" statement 
				_delay_ms(1000);
				reset_password_array(password);
				break;
			}
			else
			{
				LCD_8_bit_clear_all();
				LCD_8_bit_4_chars_needed();			// displays "4 characters needed" statement
				_delay_ms(2000);
				reset_password_array(password);
				LCD_8_bit_clear_all();
				LCD_8_bit_enter_pass();				// displays "Enter password" statement
			}
		}
		// 'c' means the user wants to delete what was typed (before submission)
		else if(keypadInput == 'c')
		{
			LCD_8_bit_clear_all();
			LCD_8_bit_enter_pass();
			reset_password_array(password);
		}
		else
		{
			// Keypad_pressed() function returns NOT_pressed by default if the user didn't press any button
			if(keypadInput != NOT_pressed)
			{
				// to make sure there is no more than 16 characters typed in the password [the length of the lcd]
				if(cnt < 16)
				{
					LCD_8_bit_sendChar('*');				// To add more privacy to the user while typing the password
					password[cnt] = keypadInput;
					++cnt;									// Increment the variable to keep track of the input count
				}
			}
		}
	}
	// If there was already a password stored in the External EEPROM, receive it from the MCU_2 through UART into the matched_password flag
	if(password_checker == Password_was_entered)
		matched_password = UART_receive();
}

// Function that lets the users make a new password
void secondOption()
{
	// It is required to enter the old password before changing it to a new one
	firstOption();
	if(matched_password == Matched)
	{
		LCD_8_bit_clear_all();
		LCD_8_bit_enter_new_pass();					// displays "Enter new password" statement
		
		// This time it takes the input from the user, verify it, and send it to MCU_2 and get guaranteed matched_password flag value of (matched)
		firstOption();			
		
		/* Resetting all variables to enter new iteration without errors */					
		choosed_option = Not_choosed;
		option = Not_choosed;
		wrong_password = 0;
	}
	else
	{
		++wrong_password;						// If the password was incorrect, increment wrong_password.
		UART_transmit(wrong_password);			// Keep MCU_2 updated with the flag value
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
		password_checker = int_eeprom_r(0x00);					// reads flag value from internal EEPROM to check if there is already a saved password	
		UART_transmit(password_checker);						// Keep MCU_2 updated with the flag value
		
		
		if(password_checker == Password_was_not_entered)		
		{
			LCD_8_bit_enter_new_pass();
			firstOption();
			int_eeprom_w(0x00,1);								// Sets the flag in the internal EEPROM
		}
		
		else if(password_checker == Password_was_entered)
		{
			
			if(choosed_option == Not_choosed)
			{
				LCD_8_bit_clear_all();
				LCD_8_bit_display_options();					// displays options 1&2 statements (1- Open the door, 2- Alter password)
				option = Keypad_pressed();
				
				// To make sure there is no response for any other buttons pressed
				while(option != First_option && option != Second_option)
					option = Keypad_pressed();
				
				LCD_8_bit_clear_all();
				LCD_8_bit_enter_pass();
				choosed_option = Choosed;
			}
			
			UART_transmit(choosed_option);						// Keep MCU_2 updated with the variable value
			
			if(option == First_option)
			{
				UART_transmit(option);							// Keep MCU_2 updated with the variable value
				
				firstOption();
				if(matched_password == Matched)
				{
					LCD_8_bit_clear_all();
					LCD_8_bit_opening();						// displays "Opening" statement (while motors are actually opening the door)
					_delay_ms(3000);
					LCD_8_bit_clear_all();
					LCD_8_bit_closing();						// displays "Closing" statement (while motors are actually closing the door)
					_delay_ms(2000);
					
					/* Resetting all variables to enter new iteration without errors */
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
				UART_transmit(option);							// Keep MCU_2 updated with the variable value
				secondOption();
			}
		}
	}
}
