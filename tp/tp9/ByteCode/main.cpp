#include <stdio.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "led.h"
#include "interrupt.h"
#include "motor.h"
#include "memoire_24.h"
#include "debug.h"
int main()
{
    LED led;
    RS232 rs232;
    Memoire24CXXX memoire;
    uint16_t startingAdr = 0x0000;
    uint8_t instruction;
    uint16_t nbBytes = rs232.USART_Receive() << 8;
    nbBytes += rs232.USART_Receive();
    DEBUG_PRINT_INT(nbBytes);
    uint16_t tmp1 = (nbBytes >> 8) | (nbBytes << 8);
    memoire.ecriture(startingAdr, reinterpret_cast<uint8_t *>(&(tmp1)), 2);
    for (int i = 2; i < nbBytes; i++)
    {
        instruction = rs232.USART_Receive();
        memoire.ecriture(startingAdr + i, instruction);
        DEBUG_PRINT_INT(instruction);
    }
    DEBUG_PRINT("\nEcriture fini\n");
    uint8_t *tmp2 = 0;
    for (int i = 0; i < nbBytes; i++)
    {
        memoire.lecture(startingAdr + i, tmp2);
        DEBUG_PRINT_INT(*tmp2);
    }
    DEBUG_PRINT("\nLecture fini");
    led.blinkGreenLight(2, 2);
}