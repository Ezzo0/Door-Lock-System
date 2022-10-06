/*
 * Macros_2.h
 *
 * Created: 10/1/2022 12:45:57 PM
 *  Author: 3zz
 */ 


#ifndef MACROS_2_H_
#define MACROS_2_H_

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

// Port names to pass them to functions
#define port_A 'A'
#define port_B 'B'
#define port_C 'C'
#define port_D 'D'
// PINS
#define PIN_0 0
#define PIN_1 1
#define PIN_2 2
#define PIN_3 3
#define PIN_4 4
#define PIN_5 5
#define PIN_6 6
#define PIN_7 7


// Bit manipulation function-like macros 

#define set_pin(reg,pin) reg |= (1<<pin) // set a pin
#define clr_pin(reg,pin) reg &= ~(1<<pin) // clear a pin
#define tgl_pin(reg,pin) reg ^= (1<<pin) // toggle the value of a pin
#define get_pin(reg,pin) ((reg & (1 << pin)) >> pin) // read the value of a pin

#endif /* UTILITIES_H_ */