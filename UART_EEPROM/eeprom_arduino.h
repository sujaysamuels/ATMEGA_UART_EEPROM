#include <avr/io.h>


void Write_To_EEPROM(unsigned int EAddress, unsigned char EData) {
    
    
    while (EECR & (1 << EEPE));                                     // Wait for Previous Write to Complete
    
    EEAR = EAddress;                                                // Set up address and Data Registers
    EEDR = EData;
    
    EECR |= (1 << EEMPE);                                           // Write logical one to EEMPE, to set EEPE within 4 clock cycles
    
    EECR |= (1 << EEPE);                                            // Start EEPROM write by setting EEPE
}

unsigned char Read_From_EEPROM(unsigned int EAddress) {
    
    
    while (EECR & (1 << EEPE));                                     // Wait for Previous Write to Complete
   
    EEAR = EAddress;                                                // Set up address register

    EECR |= (1 << EERE);                                            // Start EEPROM read by writing EEPROM READ ENABLE

    return EEDR;                                                    // Return data from Data Register
}
