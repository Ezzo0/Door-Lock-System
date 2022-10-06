/*
 * keypad.h
 *
 * Created: 10/2/2022 6:39:31 AM
 *  Author: 3zz
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../../MCAL_1/DIO_Driver_1/DIO_1.h"

#define NOT_pressed 0

void Keypad_init();
uint8_t Keypad_pressed();



#endif /* KEYPAD_H_ */