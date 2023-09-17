#define F_CPU 8000000UL
#include <led.h>
#include <avr/io.h>
#include <util/delay.h>
const int DELAI = 10;
// This function is useful because we can't call _delay_ms with a variable as an argument
// so this function calls _delay_ms(1) for the duration we want
void wait(float delay_ms)
{
    for (unsigned int j = 0; j < delay_ms; j++)
        _delay_ms(1);
}
LED::LED()
{
    DDRA |= (1 << DDA0) | (1 << DDA1); // A0 and A1 as output
}
void LED::turnOff()
{
    PORTA &= ~(1 << PORTA0 | 1 << PORTA1); // We set A0 and A1 to 0 while keeping the rest intact
}

void LED::turnRed()
{
    // We turn the LED off first in case it was lit as green before, so setting A1 to 1 would put A0 and A1 at 1
    //  therefore the LED will be off
    turnOff();
    PORTA |= (1 << PORTA1);
}
void LED::turnRed(int duration)
{
    float delay_ms = duration * 1000;
    turnOff();
    PORTA |= (1 << PORTA1);
    wait(delay_ms); // We call the function wait so the LED will be lit for delay_ms milliseconds and its turned off after
    turnOff();
}
void LED::turnGreen()
{
    // We turn the LED off first in case it was lit as red before, so setting A0 to 1 would put A0 and A1 at 1
    //  therefore the LED will be off
    turnOff();
    PORTA |= (1 << PORTA0);
}
void LED::turnGreen(int duration)
{
    float delay_ms = duration * 1000;
    turnOff();
    PORTA |= (1 << PORTA0);
    wait(delay_ms); // We call the function wait so the LED will be lit for delay_ms milliseconds and its turned off after
    turnOff();
}

void LED::turnAmber()
{
    // We alternate quickly between green and red to get the color amber
    while (true)
    {
        _delay_ms(DELAI);
        turnGreen();
        _delay_ms(DELAI);
        turnRed();
    }
}
void LED::dimRedLight()
{
    int delayRatio = 1; // Initialize to 1 the scale used for the duration of the dimming
    int timeOn = 250;   // Begins at the maximum, then goes down by 1 every 12 main
    // loops. Determines time light is on, maximum light level is at 250 until turned off at 0.
    int timeOff = 0; // Opposite of timeOn, goes up 1 every 12 loops of main loop. Determines
    // time light is off
    for (int i = 0; i < 3000; i++)
    {                                    // main loop
        this->turnRed();                 // turn on LED in red
        for (int j = 0; j < timeOn; j++) // Light ON loop
        {
            _delay_us(4);
        }
        this->turnOff();                  // Turns off the light
        for (int j = 0; j < timeOff; j++) // Light OFF loop
        {
            _delay_us(4);
        }
        if (delayRatio == 12) // after 12 main loops, timeOn goes down 1 and timeOff goes up one.
        {
            timeOn--;
            timeOff++;
            delayRatio = 1; // reset to 1 the scale
        }
        else
        {
            delayRatio++; // Not 12 main loops yet, so add 1 to delayRatio
        }
    }
}
void LED::dimGreenLight()
{
    int delayRatio = 1; // Initialize to 1 the scale used for the duration of the dimming
    int timeOn = 250;   // Begins at the maximum, then goes down by 1 every 12 main
    // loops. Determines time light is on, maximum light level is at 250 until turned off at 0.
    int timeOff = 0; // Opposite of timeOn, goes up 1 every 12 loops of main loop. Determines
    // time light is off
    for (int i = 0; i < 3000; i++)
    {                                    // main loop
        this->turnGreen();               // turn on LED in green
        for (int j = 0; j < timeOn; j++) // Light ON loop
        {
            _delay_us(4);
        }
        this->turnOff();                  // Turns off the light
        for (int j = 0; j < timeOff; j++) // Light OFF loop
        {
            _delay_us(4);
        }
        if (delayRatio == 12) // after 12 main loops, timeOn goes down 1 and timeOff goes up one.
        {
            timeOn--;
            timeOff++;
            delayRatio = 1; // reset to 1 the scale
        }
        else
        {
            delayRatio++; // Not 12 main loops yet, so add 1 to delayRatio
        }
    }
}
void LED::blinkRedLight(int duration, float ratePerSecond)
{
    float period = 1 / ratePerSecond;                   // Calculate the period in milliseconds
    unsigned int num_blinks = duration * ratePerSecond; // Calculate the number of blinks based on the duration and period
    float delay_ms = 1000 * period / 2;                 // Calculate the delay between the LED being lit and turned off in milliseconds
    for (unsigned int i = 0; i < num_blinks; i++)
    {
        turnRed();
        wait(delay_ms);
        turnOff();
        wait(delay_ms);
    }
}
void LED::blinkGreenLight(int duration, float ratePerSecond)
{
    float period = 1 / ratePerSecond;                   // Calculate the period in milliseconds
    unsigned int num_blinks = duration * ratePerSecond; // Calculate the number of blinks based on the duration and period
    float delay_ms = 1000 * period / 2;                 // Calculate the delay between the LED being lit and turned off in milliseconds
    for (unsigned int i = 0; i < num_blinks; i++)
    {
        turnGreen();
        wait(delay_ms);
        turnOff();
        wait(delay_ms);
    }
}
LED::~LED() {}
