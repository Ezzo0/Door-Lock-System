/*
 * UART_1.h
 *
 * Created: 10/1/2022 4:49:50 PM
 *  Author: 3zz
 */ 


#ifndef UART_1_H_
#define UART_1_H_

#include "../../Utilities_1/Macros_1.h"

#define BAUD_rate 9600
#define Data_bits 8
#define Stop_bits 1

void UART_init(uint16_t baud, uint8_t bitnum, uint8_t stopbits);
void UART_set_BAUD(uint16_t baud);
void UART_set_frame(uint8_t bitnum, uint8_t stopbits);
void UART_transmit(uint8_t data);
void UART_transmitString(uint8_t *string_data);
uint8_t UART_receive();

#endif /* UART_1_H_ */