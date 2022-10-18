/*
 * keypad.c
 *
 * Created: 10/2/2022 6:39:21 AM
 *  Author: 3zz
 */ 
#include "keypad.h"

uint8_t rows[4] = {row_A,row_B,row_C,row_D};
uint8_t columns[4] = {column_1,column_2,column_3,column_4};
uint8_t keypad [4][4] = {{'7','8','9','/'},\
						 {'4','5','6','x'},\
						 {'1','2','3','-'},\
						 {'c','0','=','+'}};

void Keypad_init()
{
	// Initialization of rows
	DIO_init(port_A,PIN_4,OUT);
	DIO_init(port_A,PIN_5,OUT);
	DIO_init(port_A,PIN_6,OUT);
	DIO_init(port_A,PIN_7,OUT);
	
	// Initialization of columns
	DIO_init(port_A,PIN_0,IN);
	DIO_init(port_A,PIN_1,IN);
	DIO_init(port_A,PIN_2,IN);
	DIO_init(port_A,PIN_3,IN);
	
	// give logic one to all the keypad pins
	PORTA = 0xFF;
}

uint8_t Keypad_pressed()
{
	uint8_t key = NOT_pressed;							// variable for the pressed key
	uint8_t flag = 0;									// Flag to indicate that a key was pressed or not
	uint8_t value;										// variable for storing the value of the pin
	for(int rows_cnt = 0; rows_cnt < 4; ++rows_cnt)
	{
		DIO_write(port_A,rows[rows_cnt],LOW);			// give each row pin a low value
		for (int columns_cnt = 0; columns_cnt < 4; ++columns_cnt)
		{
			DIO_read(port_A,columns[columns_cnt],&value);
			if(value == LOW)
			{
				_delay_ms(20);							// for solving the bouncing problem
				
				// Busy wait for long press
				while(value == LOW)
					DIO_read(port_A,columns[columns_cnt],&value);
				
				key = keypad[rows_cnt][columns_cnt];	// get the pressed key
				flag = 1;								// a key was pressed
				break;
			}
		}
		DIO_write(port_A,rows[rows_cnt],HIGH);			// return the pin to high value again
		if(flag)
			break;
	}
	// return the pressed key
	return key;
}