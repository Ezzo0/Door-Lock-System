/*
 * UART.h
 *
 * Created: 9/30/2022 7:03:33 PM
 *  Author: mosta
 */ 


#ifndef UART_H_
#define UART_H_

#include "../../Utils_2/Macros_2.h"

void UART_init();
void UART_set_baud_rate(uint16_t baud_rate);
void UART_recieve();
void UART_transmit(uint8_t d);




#endif /* UART_H_ */