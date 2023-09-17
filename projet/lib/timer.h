/*
File : ./tp7/lib/timer.h
Section # : SECTION 5
Team # : 121135
Correction : Stefan Cotargasanu, Romain Lebbadi-Breteau
Authors: Ralph Alaile, Ireina Hedad, Justin Boulet et Felix Perreault

Summary of the program: Used for setting timer1 on the robot, in CTC or
PWM mode. Duration of the timer or thresholds for the PWM must be passed as arguments.

*/

#include <avr/io.h>
// #define F_CPU 8000000

class Timer
{
public:
    // Constructor
    Timer();

    // Destructor
    ~Timer();

    // This function starts the timer1 in CTC mode, the duration of the timer
    // is passed as an argument (uint16_t)(128 microseconds per tic, 0x0001 = 128 microseconds)
    void timerStartCTC(uint16_t);

    void timerStartCTC_B(uint16_t);

    // This function starts timer1 in PWM mode, threshold A and threshold B are passed as
    // arguments (uint8_t)
    void timerStartPWM(uint8_t, uint8_t);
    // New function starts timer1 in PWM mode, first argument is top and threshold is passed as
    // second argument (uint8_t)
    void timerStartPwmAdjustTop64(uint8_t, uint8_t);
    void timerStartPwmAdjustTop256(uint8_t, uint8_t);
    void timerEnd();
};
