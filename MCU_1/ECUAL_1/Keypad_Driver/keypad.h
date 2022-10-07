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

// Column macros
#define column_4 PIN_0
#define column_3 PIN_1
#define column_2 PIN_2
#define column_1 PIN_3
// row macros
#define row_A PIN_7
#define row_B PIN_6
#define row_C PIN_5
#define row_D PIN_4

void Keypad_init();
uint8_t Keypad_pressed();



#endif /* KEYPAD_H_ */