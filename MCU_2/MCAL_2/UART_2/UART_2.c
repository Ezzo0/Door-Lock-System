/*
 * UART.c
 *
 * Created: 9/30/2022 7:03:23 PM
 *  Author: mosta
 */ 

#include "UART_2.h"
extern uint16_t data;

void UART_init(){
	
	// Baud rate settings
	//rate= 9600, freq= 8MH
	UART_set_baud_rate(51);
	
	//UART enable tx and rx
	set_pin(UCSRB, 3);
	set_pin(UCSRB, 4);
	
	// Set character size
	set_pin(UCSRC,7);
	set_pin(UCSRC,1);
	set_pin(UCSRC,2);
	
	
}

void UART_set_baud_rate(uint16_t baud_rate){
	UBRRH = (uint8_t)(baud_rate >> 8);
	UBRRL = (uint8_t) baud_rate;
	
}

void UART_recieve(){
	while(get_pin(UCSRA, 7) == 0);
	data = UDR;
}


void UART_transmit(uint8_t d){
	while(get_pin(UCSRA, 5) == 0);
	UDR = d;
	
}