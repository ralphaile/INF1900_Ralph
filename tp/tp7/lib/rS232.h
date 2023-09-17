/*
File : ./tp7/lib/rs232.h
Section # : SECTION 5
Team # : 121135
Correction : Stefan Cotargasanu, Romain Lebbadi-Breteau
Authors: Ralph Alaile, Ireina Hedad, Justin Boulet et Felix Perreault

Summary of the program: This program is used to communicate with the 
Atmega chip, the chip receiving unsigned char or transmitting them to the PC.

*/

class RS232
{
public:
    // Constructor
    RS232();

    // Destructor
    ~RS232();

    // Function that transmits unsigned char from the ATMEGA chip to the PC
    void USART_Transmit(unsigned char);

    // Function that sends an unsigned char from the PC to the ATMEGA chip
    unsigned char USART_Receive();
};