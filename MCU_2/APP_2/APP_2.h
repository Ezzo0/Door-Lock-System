/*
 * APP.h
 *
 * Created: 10/1/2022 8:32:49 AM
 *  Author: mosta
 */ 


#ifndef APP_H_
#define APP_H_

#include "../MCAL_2/DIO_Driver_2/DIO_2.h"
#include "../MCAL_2/UART_Driver_2/UART_2.h"
#include "../ECUAL_2/EEPROM/EEPROM.h"

#define Matched 1
#define No_Match 0

void app_init();
void app_start();


#endif /* APP_H_ */