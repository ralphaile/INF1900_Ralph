#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "interrupt.h"
#include "capteur.h"
#include "debug.h"
#include "Svg.h"
#include <stdio.h>
#include <string.h>

#define TURN_LIGHT_2_SECONDS 2
#define MINUTERIE_1S 7813 // La fréquence de notre robot est 8Mhz et avec un prescalar de 1024, apres environ 7813 cycles 1 seconde s'écoule
#define MINUTERIE_50_MS 0x186

const int DELAY_30_MS = 30;
volatile bool gInterruptButton = false;
volatile bool gWhiteButton = false;
volatile bool clignoteVert = false;

volatile uint8_t capteur_counter = 0;
volatile bool timerLedTransmit = false;
volatile bool detectionDone = false;
volatile bool amberOn = false;
volatile bool amberCondition;

LED led1;

uint32_t transmission()
{
    ListPoint listePoints;
    ListPoint newList;
    Svg svg;
    RS232 rs232;

    listePoints.readListFromMemory();

    newList = svg.convexHull(listePoints);
    svg.constructSVG(newList, listePoints);
    uint32_t crc32 = svg.getCRC();

    return crc32;
}

ISR(INT0_vect)
{
    _delay_ms(DELAY_30_MS);

    if (PIND & (1 << PIND2))
        gInterruptButton = true;

    EIFR |= (1 << INTF0);
}

ISR(INT1_vect)
{
    _delay_ms(DELAY_30_MS);

    if (!(PIND & (1 << PIND3)))
        gWhiteButton = true;
    else
        gWhiteButton = false;

    EIFR |= (1 << INTF0);
}

ISR(TIMER1_COMPA_vect)
{
    if (detectionDone == false && amberCondition == false)
    {
        capteur_counter++;
    }

    else if (amberCondition)
    {
        if (amberOn)
        {
            amberOn = false;
        }
        else
        {
            amberOn = true;
        }
    }
    else
    {
        if (timerLedTransmit == false)
        {
            led1.turnGreen();
            timerLedTransmit = true;
        }
        else
        {
            led1.turnOff();
            timerLedTransmit = false;
        }
    }
}
void initialisationWhiteButton()
{
    cli();
    DDRD &= ~(1 << DDD3);
    EIMSK |= (1 << INT1);
    EICRA |= (1 << ISC11);
    sei();
}

int main()
{
    initialisationWhiteButton();
    can CAN;
    Interrupt interruptButton;
    LED led;

    interruptButton.initializeRisingEdge();

    while (gInterruptButton == false && gWhiteButton == false)
    {
    }
    if (gInterruptButton == true)
    { // Mode detection
        //////////////////////////////////////

        //////////////////////////////////////
        Capteur capteur;
        gInterruptButton = false;
        char position;

        while (gInterruptButton == false && gWhiteButton == false)
        {
            led.turnAmber();
        }

        if (gInterruptButton == true) // pointe vers le haut
        {
            led.turnGreen(TURN_LIGHT_2_SECONDS);
            position = 'h';
            gInterruptButton = false;
        }

        if (gWhiteButton == true) // pointe a droite
        {
            led.turnRed(TURN_LIGHT_2_SECONDS);
            position = 'r';
            gWhiteButton = false;
        }

        capteur.start(position);

        led.blinkRedLight(50, 2);
    }
    else if (gWhiteButton == true)
    { // mode transmission

        //////////////////////////////////////

        //////////////////////////////////////
        led.turnGreen(TURN_LIGHT_2_SECONDS);

        detectionDone = true;
        Timer time;
        RS232 rs232;

        time.timerEnd();
        time.timerStartCTC(MINUTERIE_50_MS);
        
        uint8_t startTransmission = 0x02;
        uint8_t endText = 0x03;
        uint8_t endTransmission = 0x04;

        rs232.USART_Transmit(startTransmission);
        uint32_t crc32 = transmission();
        rs232.USART_Transmit(endText);

        _delay_ms(DELAY_30_MS);

        char crc32_char[9];
        sprintf(crc32_char, "%08lx", crc32);
        for (unsigned int i = 0; i < sizeof(crc32_char); i++)
        {
            rs232.USART_Transmit(crc32_char[i]);
        }

        rs232.USART_Transmit(endTransmission);
        
        led.turnOff();
        time.timerEnd();
    }

    return 0;
}
