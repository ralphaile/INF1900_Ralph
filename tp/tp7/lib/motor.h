/*
File : ./tp7/lib/motor.h
Section # : SECTION 5
Team # : 121135
Correction : Stefan Cotargasanu, Romain Lebbadi-Breteau
Authors: Ralph Alaile, Ireina Hedad, Justin Boulet et Felix Perreault

Summary of the program: Used to program the motor, making it go forward
straight or turning.

*/


#include <avr/io.h>
// #define F_CPU 8000000

class Motor
{
public:
    // Constructor
    Motor();

    // Destructor
    ~Motor();

    // Function that is used to make the robot go forward or turn, takes 2
    // arguments (uint8_t) to determine speed (maximum speed is 0xFF).
    void motorForward(uint8_t, uint8_t);
};
