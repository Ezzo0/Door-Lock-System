/*
 * MCU_1.c
 *
 * Created: 10/1/2022 12:40:47 PM
 * Author : 3zz
 */
 #include "ECUAL_1/Keypad_Driver/keypad.h"
 #include "ECUAL_1/LCD_Driver/lcd.h"

uint8_t data;
int main(void)
{
	Keypad_init();
	LCD_8_bit_init();
	DIO_init(port_B,PIN_0,OUT);
	DIO_init(port_B,PIN_1,OUT);
	DIO_init(port_B,PIN_2,OUT);
    while (1) 
    {
		data = Keypad_pressed();
		if(data == '0')
			DIO_write(port_B,PIN_0,HIGH);
		else if(data == '1')
			DIO_write(port_B,PIN_1,HIGH);
		else if(data == '2')
			DIO_write(port_B,PIN_2,HIGH);
		if(data != NOT_pressed)
		{
			LCD_8_bit_sendChar(data);
		}
    }
}

