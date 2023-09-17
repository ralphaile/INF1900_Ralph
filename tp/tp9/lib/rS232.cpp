#include <avr/io.h>
#include <rS232.h>
RS232::RS232()
{
    // 2400 bauds.
    UBRR0H = 0;
    UBRR0L = 0xCF;
    // Enabling transmission and reception by UART0
    UCSR0A = 0;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    // Format: 8 bits, 1 stop bits, no parity
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
}

RS232::~RS232() {}

void RS232::USART_Transmit(unsigned char data)
{
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    /* Put data into buffer, sends the data */
    UDR0 = data;
}

unsigned char RS232::USART_Receive()
{
    /* Wait for data to be received */
    while (!(UCSR0A & (1 << RXC0)))
        ;
    /* Get and return received data from buffer */
    return UDR0;
}
