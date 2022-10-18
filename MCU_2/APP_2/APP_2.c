/*
 * APP.c
 *
 * Created: 10/1/2022 8:32:38 AM
 *  Author: mosta
 */ 
#include "APP_2.h"

// variable to receive the value of the password_checker flag from MCU_1
uint8_t pass_check = 2;

// variable to receive the value of the matched_password flag from MCU_1
uint8_t pass_match = 1;

// Char array to send/receive password to/from the EEPROM through I2C (TWI)
uint8_t pass_recieve_save[17] = {'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
	
// Char array to receive password from MCU_1 through UART, then compare it to pass_recieve_save
uint8_t pass_recieve_cmpr[17] = {'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
	
// Char array to reset the EEPROM
uint8_t clr[17] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, 0xFF};

// Variable to receive option from MCU_1 through UART
uint8_t opt = 0;

// Variable to receive choosed_option from MCU_1 through UART
uint8_t chs_opt =0;

// Variable to receive wrong_password from MCU_1 through UART
uint8_t wrong_pass;

// Variable to indicate the state of the alert
uint8_t alert_on = 0;


void app_init(){
	UART_init();
	EEPROM_init();
	motor_init();
	DIO_init(port_D,PIN_6,OUT);
	DIO_init(port_D,PIN_7,OUT);
	
	// Global interrupts activation
	enable_global_interrupts();
	
	// Timer_2 interrupt activation
	timer2_enable_overflow_interrupt();
	
	// Timers mode selection
	timer2_select_mode(normal);
	
	// Timers initial value
	timer2_set_initial_value(Timer_initial_value);
	
	// Timer_0 interrupt activation
	timer0_enable_overflow_interrupt();
	TIMER_0_init();
	
}



void app_start()
{
	while(1){
		
		// setting pass_match to 1 every iteration start
		pass_match = 1;
		
		// receive pass_check from MCU_1 (internal EEPROM)
		pass_check = UART_receive();
		
		
		if(pass_check == Password_was_entered)
		{
			// received choosed_option from MCU_1
			chs_opt = UART_receive();
			
			if(chs_opt == Choosed)
			{
				// clearing pass_recieve_cmpr & pass_recieve_save
				reset_pass_array();
				
				// received option from MCU_1
				opt = UART_receive();
				
				// compare pass_recieve_cmpr & pass_recieve_save
				compare_incoming_pass();
				
				if(pass_match)
				{
					if(alert_on)
					{
						timer2_timer_stop();
						DIO_write(port_D,PIN_7,LOW);
						DIO_write(port_D,PIN_6,LOW);
						alert_on = 0;
					}
					
					if(opt == First_option)
					{
						// opening the door
						motor_response();
					}
					else if(opt == Second_option)
					{
						// delete old password in the EEPROM (reset)
						EEPROM_write_string(clr);
						
						reset_pass_array();
						
						// store the new password in the EEPROM
						set_new_pass();
						
						// Sending the guaranteed matched value to prevent first_option() function in APP_1 from waiting forever for the value
						UART_transmit(Matched);
						
					}
				}
				else
				{
					// receive wrong_password count from MCU_1 through UART
					wrong_pass = UART_receive();
					if(wrong_pass >= 3 && !alert_on)
					{
						// starting timer to make the led blink each overflow
						timer2_timer_start(Timer_prescalar);
						
						// turning on the buzzer
						DIO_write(port_D,PIN_7,HIGH);
						
						// setting alarm_on value
						alert_on = 1;
					}
				}
			}

		}
		else if(pass_check == Password_was_not_entered)
		{
			// if it is the first time the system boots, the user will enter the first password
			set_new_pass();
			reset_pass_array();
		}
	}
}


void reset_pass_array()
{
	for(uint8_t i=0; i<17; i++){
		pass_recieve_cmpr[i] = '\0';
		pass_recieve_save[i] = '\0';
	}
}

void compare_incoming_pass()
{
	UART_receiveString(pass_recieve_cmpr);
	EEPROM_read_string(pass_recieve_save);
	
	// pass_match is set to a default value of 1. the value will be 0 only if there is a different character in the for loop
	for(uint8_t i=0; i<16; i++){
		if(pass_recieve_save[i] != pass_recieve_cmpr[i]){
			pass_match = 0;
		}
	}
	
	// send pass_match flag to MCU_1 through UART
	UART_transmit(pass_match);
}

void set_new_pass()
{
	// receive password string from MCU_1 through UART
	UART_receiveString(pass_recieve_save);
	
	// store the received password in the EEPROM through the I2C (TWI)
	EEPROM_write_string(pass_recieve_save);
}