#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <interrupt.h>
const int DELAI = 50;

Interrupt::Interrupt()
{
    // Disabling interruptions for the initialization
    cli();
    // Setting PORTD2 as an entry PIN
    DDRD &= ~(1 << DDD2);
    // Reenabling interruptions
    sei();
}

Interrupt::~Interrupt() {}

void Interrupt::initializeFallingEdge()
{
    cli();
    EICRA |= (1 << ISC01) | (0 << ISC00); // Changing iterruption mode to falling edge
    // Enabling external interruptions
    EIMSK |= (1 << INT0);
    sei();
}

void Interrupt::initializeRisingEdge()
{
    cli();
    EICRA |= (1 << ISC01) | (1 << ISC00); // Changing iterruption mode to rising edge
    // Enabling external interruptions
    EIMSK |= (1 << INT0);
    sei();
}

void Interrupt::initializeAnyEdge()
{
    cli();
    EICRA |= (0 << ISC01) | (1 << ISC00); // Changing iterruption mode to any edge
    // Enabling external interruptions
    EIMSK |= (1 << INT0);
    sei();
}

bool Interrupt::isButtonPressed()
{
    _delay_ms(DELAI);             // Debounce
    return (PIND & (1 << PIND2)); // Returns true if button pressed and false otherwise
}

void Interrupt::waitButtonPress()
{
    while (!(PIND & (1 << PIND2)))
    {                     // Stays in a loop while the button is not pressed
        _delay_ms(DELAI); // Debounce
    }
}

void Interrupt::waitButtonRelease()
{
    while ((PIND & (1 << PIND2)))
    {                     // Stays in the loop as long as the button is pressed
        _delay_ms(DELAI); // Debounce
    }
}