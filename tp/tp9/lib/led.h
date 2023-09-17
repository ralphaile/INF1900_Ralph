/*
File : ./tp7/lib/led.h
Section # : SECTION 5
Team # : 121135
Correction : Stefan Cotargasanu, Romain Lebbadi-Breteau
Authors: Ralph Alaile, Ireina Hedad, Justin Boulet et Felix Perreault

Summary of the program: Used to turn on lights in green, red or amber. 
Also used to turn them off, make them blink, or dim them slowly.

*/


#include <avr/io.h>
// La DEL dans notre cas est toujours connecte a PORTA et plus specifiquement a A0 et A1
class LED
{
public:
    // Constructor in which we set PORTA0 and PORTA1 as outputs to control the LED
    LED();

    // Destructor
    ~LED();

    // Turns off the LED
    void turnOff();

    // Turns on the LED in red indefinitely
    void turnRed();

    // Turns on the LED in red for a specific duration passed to the function in seconds
    void turnRed(int);

    // Turns on the LED in green indefinitely
    void turnGreen();

    // Turns on the LED in green for a specific duration passed to the function in seconds
    void turnGreen(int);

    // Turns on the LED in Amber indefinitely
    void turnAmber();

    // Dims the red Light until the LED is off
    void dimRedLight();

    // Dims the Green Light until the LED is off
    void dimGreenLight();

    // Blinks the red light for a certain duration in seconds with a rate of blinks per second
    void blinkRedLight(int, float);

    // Blinks the green light for a certain duration in seconds with a rate of blinks per second
    void blinkGreenLight(int, float);
};