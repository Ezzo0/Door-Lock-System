/*
 * Macros.h
 *
 * Created: 9/11/2022 2:10:45 AM
 *  Author: Mostafa Ayyad
 */ 


#ifndef MACROS_H_
#define MACROS_H_

	#define F_CPU 1000000UL
	#include <avr/io.h>
	#include <util/delay.h>
	
	
	//** Bit manipulation function-like macros **//
	#define set_pin(x,n) x|= (1<<n)
	#define clr_pin(x,n) x&= ~(1<<n)
	#define tgl_pin(x,n) x^= (1<<n)
	#define get_pin(x,n) ((x&(1<<n))>>n)
	
	
	//** PORT names to pass to functions **//
	#define PORT_A 'A'
	#define PORT_B 'B'
	#define PORT_C 'C'
	#define PORT_D 'D'


	
	
#endif /* MACROS_H_ */