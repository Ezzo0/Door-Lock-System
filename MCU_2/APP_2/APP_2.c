/*
 * APP.c
 *
 * Created: 10/1/2022 8:32:38 AM
 *  Author: mosta
 */ 
#include "APP_2.h"

uint8_t received_password[17] = {'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
uint8_t eeprom_password[17];
uint8_t matched_password = No_Match;

void app_init()
{
	UART_init();
	EEPROM_init();
}

void app_start()
{
	while (1)
	{
		UART_receiveString(received_password);
		if(received_password[0] != '\0')
			EEPROM_write_string(received_password);
	}
}