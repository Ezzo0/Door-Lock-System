/*
 * TWI.h
 *
 * Created: 10/6/2022 2:38:33 PM
 *  Author: 3zz
 */ 


#ifndef TWI_H_
#define TWI_H_

#include "../../Utilities_2/Macros_2.h"

#define SCL_frq 400000UL


//States
#define START_STATE 0x08
#define REPEATED_START_STATE 0x10
#define SLA_W_ACK_STATE 0x18
#define SLA_W_NACK_STATE 0x20
#define SLA_R_ACK_STATE 0x40
#define SLA_R_NACK_STATE 0x48
#define DATA_W_ACK_STATE 0x28
#define DATA_W_NACK_STATE 0x30
#define DATA_R_ACK_STATE 0x50
#define DATA_R_NACK_STATE 0x58


// Returns
typedef enum EN_returnStatus_t
{
	EVENT_OK, START_NOT_SENT, REPEATED_START_NOT_SENT, SLA_W_ACK_SENT, SLA_W_NACK_SENT, SLA_R_ACK_SENT, SLA_R_NACK_SENT,SLA_RW_FAILED, 
	DATA_W_ACK_SENT, DATA_W_NACK_SENT,DATA_W_FAILED, DATA_R_ACK_SENT, DATA_R_NACK_SENT,DATA_R_FAILED
}EN_returnStatus_t;

#define Write 0
#define Read 1

#define ACK 0
#define NOT_ACK 1

// Setting bit rate value
#define BitRate ((F_CPU / SCL_frq) - 16) / (2 * pow(4,(TWSR & ((1 << TWPS0) | (1 << TWPS1)))))

void TWI_init();
void TWI_start(uint8_t addr);
void TWI_write_data(uint8_t data);
void TWI_write_addr(uint8_t mem_addr);
void TWI_read_ack(uint8_t *data);
void TWI_read_nack(uint8_t *data);
void TWI_stop();
EN_returnStatus_t TWI_get_status();

#endif /* TWI_H_ */