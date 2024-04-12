# ATMEGA_UART_EEPROM
This is the code for ATMEGA328P,  which recieves a string from the PC via UART, stores in EEPROM and Transmits the same string to the PC from EEPROM via UART. 

# Overview

The PC code is a python script which sends a string, this script also measures the bits per second for Transmission and Receiving. It also checks if the string received is valid

The firmware is written in C.

# The Process

# UART 


#  Initialising the UART
 ![image](https://github.com/sujaysamuels/ATMEGA_UART_EEPROM/assets/91011535/0c7108fb-cd0f-40f1-8e12-9905262d8e0d)
 Set the baud rate for both upper and lower byte
 - Send the upper byte to UBRR0H
 - Send the lower byte to UBRR0L

 ![image](https://github.com/sujaysamuels/ATMEGA_UART_EEPROM/assets/91011535/f0978f24-38f2-46b7-9e06-42efbd235a4e)
 Enabling Transmitter and Reciever
  - set RXEN0 and TXEN0  -> UCSR0B = (1 << RXEN0) | (1 << TXEN0);
 
![image](https://github.com/sujaysamuels/ATMEGA_UART_EEPROM/assets/91011535/3deaf428-45d4-449e-a406-70400b05ca09)
![image](https://github.com/sujaysamuels/ATMEGA_UART_EEPROM/assets/91011535/a016aea9-6f15-436a-9c56-d1c5bd6fd446)
Set the Frame Format ( In this case, 8 bit data, 1 stop bit) in Register UCSR0C,
- so -> UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  (setting UCSZ01 and UCSZ00 )

# Transmitting via UART
![image](https://github.com/sujaysamuels/ATMEGA_UART_EEPROM/assets/91011535/db96e7a7-6077-419a-9c48-3f50bc1d7315)
Wait for the transmit buffer to be empty
 - while (!(UCSR0A & (1 << UDRE0)));

Put the data into the buffer
 - UDR0 = data; 

# Receiving via UART
![image](https://github.com/sujaysamuels/ATMEGA_UART_EEPROM/assets/91011535/66aa3218-7c94-4cbd-9e3a-b0cf8f3ba47c)
Wait for data to be received    
- while (!(UCSR0A & (1 << RXC0)));   

Return the received data from the buffer
 - return UDR0;    
  




# EEPROM


# Writing to EEPROM
![image](https://github.com/sujaysamuels/ATMEGA_UART_EEPROM/assets/91011535/e73ace3e-4e92-4d8a-8dfb-6ba518547147)
![image](https://github.com/sujaysamuels/ATMEGA_UART_EEPROM/assets/91011535/0095b58d-c698-40ea-b3de-c0056592b9ec)

Wait for the previous write to complete
 - while (EECR & (1 << EEPE));

![image](https://github.com/sujaysamuels/ATMEGA_UART_EEPROM/assets/91011535/6f8c6143-5f0d-4b52-9ee8-7881ec07f893)
Set up Data and Address Register

![image](https://github.com/sujaysamuels/ATMEGA_UART_EEPROM/assets/91011535/eaf6cb50-2718-4f2e-8cc0-76446d98face)
Set EEMPE and following that, within 4 clock cycles, start EEPROM Write by setting EEPE
 - EECR |= (1 << EEMPE);   
 - EECR |= (1 << EEPE);   

# Reading From EEPROM

![image](https://github.com/sujaysamuels/ATMEGA_UART_EEPROM/assets/91011535/e73ace3e-4e92-4d8a-8dfb-6ba518547147)
Wait for the previous write to complete
 - while (EECR & (1 << EEPE));

![image](https://github.com/sujaysamuels/ATMEGA_UART_EEPROM/assets/91011535/6f8c6143-5f0d-4b52-9ee8-7881ec07f893)
Set up address register
 - EEAR = EAddress; 

![image](https://github.com/sujaysamuels/ATMEGA_UART_EEPROM/assets/91011535/eaf6cb50-2718-4f2e-8cc0-76446d98face)
Start EEPROM read by writing EEPROM READ ENABLE
 - EECR |= (1 << EERE);

Return data from Data Register
 - return EEDR;



# Main Function

How to calculate UBRRN
![image](https://github.com/sujaysamuels/ATMEGA_UART_EEPROM/assets/91011535/b3b90fc1-91f3-40f5-a299-6a9aac4fb349)

Clock speed of Arduino 16Mhz
Baud rate is set to 2400


Set EEPROM Start Address to 0


Using do-while loops we can 
 - Receive data via UART and and write it to EEPROM
 - Read data from EEPROM and transmit it via UART
   
(can refer the code for this)


# OUTPUTS

![image](https://github.com/sujaysamuels/ATMEGA_UART_EEPROM/assets/91011535/632b1c81-116a-4349-8f29-5d3aef7676ae)

Python Console output(PC side)

![Untitled](https://github.com/sujaysamuels/ATMEGA_UART_EEPROM/assets/91011535/ee3421e0-bf5f-45b5-b79e-22ccfde8e5c5)
![Untitled-1](https://github.com/sujaysamuels/ATMEGA_UART_EEPROM/assets/91011535/059d5619-1567-40a9-ac50-5920c34375e3)

Arduino Transmission and Receiving

# Reference

https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf






