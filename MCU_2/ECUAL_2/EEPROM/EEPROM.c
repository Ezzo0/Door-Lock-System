/*
 * EEPROM.c
 *
 * Created: 10/7/2022 8:11:32 PM
 *  Author: 3zz
 */ 
#include "EEPROM.h"

uint8_t FIRST_WORD = 0x00;
uint8_t SECOND_WORD = 0x08;

void EEPROM_inti(uint8_t prescalar)
{
	TWI_init(prescalar);
}
void EEPROM_write(uint8_t *data)
{
	if(TWI_start() == EVENT_OK)
	{
		if(TWI_send_address(EEPROM_ADDRESS,Write) == SLA_W_ACK_STATE)
		{
			if(TWI_send_address(FIRST_WORD,Write) == SLA_W_ACK_STATE)
			{
				if(TWI_data_event(&SECOND_WORD,Write,ACK) == SLA_W_ACK_STATE)
				{
					if(TWI_data_event(data,Write,ACK) == DATA_W_ACK_STATE)
					{
						TWI_stop();
					}
				}
			}
		}
	}
}
void EEPROM_read(uint8_t *data)
{
	if(TWI_start() == EVENT_OK)
	{
		if(TWI_send_address(EEPROM_ADDRESS,Write) == SLA_W_ACK_STATE)
		{
			if(TWI_data_event(data,Read,NOT_ACK) == DATA_R_NACK_STATE)
			{
				TWI_stop();
			}
		}
	}

}