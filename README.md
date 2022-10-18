# DOOR-LOCKER-Security-System

Door Locker Security System consists of two microcontroller of type ATmega32. 
The first MCU is called HMI MCU which responsible for interfacing with the user LCD and keypad. 
The second MCU is called control MCU which is responsible for the system operations and control. 
The system was implemented wihtin the following drivers Keypad, LCD, Motor, UART, Timer, TWI and External and Internal EEPROM. 

## First MCU
Type : ATmega32 MCU

This Microcontroller is connected to a Liquid Crystal Display screen,LCD, and a Keypad.
LCD is used to display messages to the user and the Keypad is used to enter the password or choose an option.

## Second MCU
Type : ATmega32 MCU

It's connected to a Direct Currentmotor, AT24C512B Electrically Erasable Programmable Read-Only Memory (EEPROM), LED,and Buzzer.
DC motor is used to open or close the door,AT24C512B EEPROM is an external non-volatile memory which is used to store the user password, and buzzer and LED are used as an alarm if the user entered the password 3 consecutive times.

## System Life cycle
At the first time a user use the system, there is a phrase on LCD which is asking the user to enter a new password (which is implemented through a non-volatile flag in the internal EEPROM of MCU_1). 
User can enter a password vary from 4 numbers to 16 numbers via the Keypad. 
After that, the system asks user to choose an option as these options are: 

1- Open the door.

2- Alter password. 


The system is holding the flow of the code until the user choose an option. If the user chose an option, the system asks him to enter the password.
The entered password is sent to the Control_MCU via Universal Asynchronous Receiver Transmitter(UART), then the Control_MCU compare it with the stored password in external EEPROM. 

If the password is matched and user chose to open the door,LCD will display "Opening the door" and the DC motor will rotate clockwise to open the door and hold it for 5 seconds. After that, LCD will display "Closing the door" and motor will rotate in the opposite direction to close the door. 

If the entered Password was wrong for 3 consecutive times, blue LED will plink and Buzzer will shoutout until the right password is entered.

## Simulation


https://user-images.githubusercontent.com/93541012/196055777-d3ab5ece-acd4-4f45-ac0e-0088d3a58f38.mp4

