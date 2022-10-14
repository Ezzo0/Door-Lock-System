/*
 * APP.c
 *
 * Created: 10/1/2022 8:32:38 AM
 *  Author: mosta
 */ 
#include "APP_2.h"

uint8_t pass_check = 2;
uint8_t pass_match = 1;
uint8_t pass_recieve_save[17] = {'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
uint8_t pass_recieve_cmpr[17] = {'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
uint8_t clr[17] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, 0xFF};
uint8_t opt = 0;
uint8_t chs_opt =0;

void app_init(){
	UART_init();
	EEPROM_init();
	motor_init();
	DDRA = 0xFF;
}



void app_start()
{
	while(1){
		pass_match = 1;
		pass_check = UART_receive();
		
		
		if(pass_check == Password_was_entered)
		{
			chs_opt = UART_receive();
			
			if(chs_opt == Choosed)
			{
				
				reset_pass_array();
				
				opt = UART_receive();
				
				compare_incoming_pass();
				
				
				if(pass_match)
				{
					if(opt == First_option)
					{
						motor_response();
					}
					else if(opt == Second_option)
					{
						
						EEPROM_write_string(clr);
						
						reset_pass_array();
						set_new_pass();
						UART_transmit(Matched);
						
					}
				}
			}

		}
		else if(pass_check == Password_was_not_entered)
		{
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
	
	
	for(uint8_t i=0; i<16; i++){
		if(pass_recieve_save[i] != pass_recieve_cmpr[i]){
			pass_match = 0;
		}
	}
	UART_transmit(pass_match);
}

void set_new_pass()
{
	UART_receiveString(pass_recieve_save);
	EEPROM_write_string(pass_recieve_save);
}