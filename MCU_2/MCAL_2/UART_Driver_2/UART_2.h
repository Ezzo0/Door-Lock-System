/*
 * UART_2.h
 *
 * Created: 10/1/2022 4:49:50 PM
 *  Author: 3zz
 */ 


#ifndef UART_2_H_
#define UART_2_H_


#include "../../Utilities_2/Macros_2.h"

#define BAUD_rate 9600
#define Data_bits 8
#define Stop_bits 1

void UART_init(uint16_t baud, uint8_t bitnum, uint8_t stopbits);
void UART_set_BAUD(uint16_t baud);
void UART_set_frame(uint8_t bitnum, uint8_t stopbits);
void UART_transmit(uint8_t data);
uint8_t UART_receive();
void UART_receiveString(uint8_t *string);


#endif /* UART_2_H_ */