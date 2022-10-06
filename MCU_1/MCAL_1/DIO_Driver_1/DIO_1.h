/*
 * DIO_1.h
 *
 * Created: 10/1/2022 12:42:33 PM
 *  Author: 3zz
 */ 


#ifndef DIO_H_
#define DIO_H_

#include "../../Utilities_1/Macros_1.h"

#define HIGH 1
#define LOW 0

#define OUT 1
#define IN 0

// Function prototypes
void DIO_init(uint8_t portnum,uint8_t pinnum, uint8_t direction); // initializations of a pin
void DIO_write(uint8_t portnum,uint8_t pinnum, uint8_t value); // write data to a pin
void DIO_toggle(uint8_t portnum,uint8_t pinnum); // toggle a pin
void DIO_read(uint8_t portnum,uint8_t pinnum, uint8_t *value); // read a pin




#endif /* DIO_H_ */