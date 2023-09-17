/*
File : ./tp7/lib/interrupt.h
Section # : SECTION 5
Team # : 121135
Correction : Stefan Cotargasanu, Romain Lebbadi-Breteau
Authors: Ralph Alaile, Ireina Hedad, Justin Boulet et Felix Perreault

Summary of the program: Used for setting interruption, with different parameters such as 
rising edge, falling edge or any edge. Also used for interruption when button is pressed or released.

*/


#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
class Interrupt
{
public:
    // Constructor in which we set the PIND2 as entry and enabling external interrupts using EIMSK
    Interrupt();

    // Destructor
    ~Interrupt();

    // function to set the interruption mode to falling edge
    void initializeFallingEdge();

    // function to set the interruption mode to rising edge
    void initializeRisingEdge();

    // function to set the interruption mode to any edge
    void initializeAnyEdge();

    // function to check if the button is pressed and returns a boolean depending on the result
    bool isButtonPressed();

    // This function waits for the button to be pressed. If it is called before the button press,
    // we stay in an infinite loop all while checking if the button has been pressed so we can return
    // to the program
    void waitButtonPress();

    // This function waits for the button to be released.
    void waitButtonRelease();
};