/*
 * TWI.c
 *
 * Created: 10/6/2022 2:38:44 PM
 *  Author: 3zz
 */ 

#include "TWI_2.h"

void TWI_init(uint8_t prescalar)
{
	TWSR = 0x00; // Clear Status Register
	
	// Choosing a prescalar
	switch(prescalar)
	{
		case 1:
		break;
		
		case 4:
			set_pin(TWSR,TWPS0);
		break;
		
		case 16:
			 set_pin(TWSR,TWPS1);
		break;
		
		case 64:
			set_pin(TWSR,TWPS0);
			set_pin(TWSR,TWPS1);
		break;
		
		default:
			//error
		break;
	}
	
	TWBR = BitRate; // Set Bit Rate register
}


EN_returnStatus_t TWI_start()
{
	uint8_t status;
	set_pin(TWCR,TWINT); // Clear interrupt flag in control register
	set_pin(TWCR,TWSTA); // Set start bit in control register
	set_pin(TWCR,TWEN); // Enable TWI 
	while (!( TWCR & (1 << TWINT) )); // Wait for TWINT Flag set
	
	// Check state on TWI Status register
	status = (TWSR & 0xF8); // Reading TWI status register
	if(status != START_STATE)
		return START_NOT_SENT;
	else
		return EVENT_OK;
}

EN_returnStatus_t repeated_TWI_start()
{
	uint8_t status;
	set_pin(TWCR,TWINT); // Clear interrupt flag in control register
	set_pin(TWCR,TWSTA); // Set start bit in control register
	set_pin(TWCR,TWEN); // Enable TWI
	while (!( TWCR & (1 << TWINT) )); // Wait for TWINT Flag set
	
	// Check state on TWI Status register
	status = (TWSR & 0xF8); // Reading TWI status register
	if(status != REPEATED_START_STATE)
		return REPEATED_START_NOT_SENT;
	else
		return EVENT_OK;
}

EN_returnStatus_t TWI_send_address(uint8_t address, uint8_t r_or_w)
{
	uint8_t status;
	if(r_or_w == Write)
		TWDR = address + Write; // Writing SLA+W in TWI data register
	else if(r_or_w == Read)
		TWDR = address + Read; // Writing SLA+R in TWI data register
	else
	{
		//error
	}
	set_pin(TWCR,TWINT); // Clear interrupt flag in TWI control register
	set_pin(TWCR,TWEN); // Enable TWI
	while (!( TWCR & (1 << TWINT) )); // Wait for TWINT Flag set
	
	// Check state on TWI Status register
	status = (TWSR & 0xF8); // Reading TWI status register
	if( status == SLA_W_ACK_STATE )
		return SLA_W_ACK_SENT;		// SLA+W transmitted & Ack received  
	else if( status == SLA_W_NACK_STATE )
		return SLA_W_NACK_SENT;		// SLA+W transmitted & NO Ack received
	else if( status == SLA_R_ACK_STATE )
		return SLA_R_ACK_SENT;		// SLA+R transmitted & Ack received
	else if( status == SLA_R_NACK_STATE )
		return SLA_R_NACK_SENT;		// SLA+R transmitted & NO Ack received
	else
		return SLA_RW_FAILED;
}

EN_returnStatus_t TWI_data_event(uint8_t *data, uint8_t r_or_w, uint8_t ack)
{
	uint8_t status;
	if(r_or_w == Write)
	{
		TWDR = *data; // Put data into TWI data register
		set_pin(TWCR,TWINT); // clear interrupt flag in TWI control register
		set_pin(TWCR,TWEN); // Enable TWI
		while (!( TWCR & (1 << TWINT) )); // Wait for TWINT Flag set
		
		// Check state on TWI Status register
		status = (TWSR & 0xF8); // Reading TWI status register
		if( status == DATA_W_ACK_STATE )
			return DATA_W_ACK_SENT;		// Data written & Ack received 
		else if( status == DATA_W_NACK_STATE )
			return DATA_W_NACK_SENT;	// Data written & No Ack received 
		else
			return DATA_W_FAILED;		// Data transmission failed
		
	}
	else if(r_or_w == Read)
	{
		if(ack == ACK)
		{
			// Enable ACK, TWI
			set_pin(TWCR,TWINT);
			set_pin(TWCR,TWEN);
			set_pin(TWCR,TWEA);
		}
		else if(ack == NOT_ACK)
		{
			// Enable TWI without ACK
			set_pin(TWCR,TWINT);
			set_pin(TWCR,TWEN);
		}
		while (!( TWCR & (1 << TWINT) )); // Waiting for TWI to finish its current job
		
		*data = TWDR; // Reading data in TWI data register
		
		// Check state on TWI Status register
		status = (TWSR & 0xF8); // Reading TWI status register
		if( status == DATA_R_ACK_STATE )
			return DATA_R_ACK_SENT; // Data transmitted with ACK
		else if( status == DATA_W_NACK_STATE )
			return DATA_R_NACK_SENT; // Data transmitted with NO ACK
		else
			return DATA_R_FAILED; // Data transmission failed 
	}
}

void TWI_stop()
{
	// Enable TWI, stop condition
	set_pin(TWCR,TWINT);
	set_pin(TWCR,TWSTO);
	set_pin(TWCR,TWEN);
	while (!( TWCR & (1 << TWINT) )); // Wait until stop condition execution 
}
