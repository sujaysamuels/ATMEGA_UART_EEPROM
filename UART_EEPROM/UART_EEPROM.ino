#include <stdio.h>
#include <stdint.h>
#include "eeprom_arduino.h"
#include "UART_arduino.h"


#define CLOCK_SPEED     16000000UL
#define BAUD_RATE       2400
#define MYUBRR          CLOCK_SPEED/16/BAUD_RATE-1


#define EEPROM_START_ADDRESS 0


int main(void) {

  USART_Init(MYUBRR);                                     //Initialising the UART 

  unsigned int EEPROM_address ;                           // EEPROM_START_ADDRESS;

  char data;
                                          
  while (1) {                                             // LOOP Always
        
    EEPROM_address = EEPROM_START_ADDRESS;                // Start from 0th address
        
    int count = 0;

    do{
          
       data = USART_RX();                                 // Recieve data from UART
       Write_To_EEPROM(EEPROM_address++, data);           // WRITE to EEPROM      
            
       count++;
            
    }while(data != '\n');
        
        
    EEPROM_address=EEPROM_START_ADDRESS;
    do{
        data = Read_From_EEPROM(EEPROM_address++);        //Read from EEPROM
        USART_TX(data);                                   // Transmit the read data via UART
      
    }while(--count);
  
  
  }
    
  return 0;
}
