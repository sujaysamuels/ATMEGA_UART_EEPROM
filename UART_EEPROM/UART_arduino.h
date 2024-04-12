#include <avr/io.h>



void USART_Init(unsigned int baud) {
    
    UBRR0H = (unsigned char)(baud >> 8);                        // Set baud rate Upper Byte
    UBRR0L = (unsigned char)baud;                               // Set baud rate Lower Byte

   
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);                       // Enable receiver and transmitter

    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);                     // Set the frame format: 8data, 1stop bit
}

void USART_TX(unsigned char data) {
    
   
    while (!(UCSR0A & (1 << UDRE0)));                           // Wait for the transmit buffer to be empty 
    
    UDR0 = data;                                                // Put data into buffer, sends the data
}

unsigned char USART_RX(void) {
    
    
    while (!(UCSR0A & (1 << RXC0)));                            // Wait for data to be received 
    
    return UDR0;                                                // Get and return received data from buffer 
}