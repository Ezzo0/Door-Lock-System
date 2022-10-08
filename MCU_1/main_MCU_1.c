/*
 * MCU_1.c
 *
 * Created: 10/1/2022 12:40:47 PM
 * Author : 3zz
 */
 #include "ECUAL_1/Keypad_Driver/keypad.h"
 #include "ECUAL_1/LCD_Driver/lcd.h"

uint8_t data[16] = {0};
uint8_t clr[16] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
uint8_t ct =0;
uint8_t temp=0;
int main(void)
{
	Keypad_init();
	LCD_8_bit_init();
	UART_init();

    while (1) 
    {
		temp = Keypad_pressed();
		if( temp == '=')
		{
			UART_transmitString(data);
		}
		else if(temp != 'c')
		{
			data[ct] = temp;
			
			if(data[ct] != NOT_pressed)
			{
				LCD_8_bit_sendChar(data[ct]);
				ct++;
			}
		}else{
			UART_transmitString(clr);
		}
		
    }
}

