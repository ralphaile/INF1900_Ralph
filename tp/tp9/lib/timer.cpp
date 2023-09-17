
#include <avr/io.h>
#include <timer.h>

void Timer::timerStartCTC(uint16_t duration)
{
    TCNT1 = 0x0000;                                                    // timer starts at 0
    OCR1A = duration;                                                  // duration of timer
    TCCR1A = 0;                                                        // Normal port operation, OC1A and OC1B disconnected
    TCCR1B |= (1 << ICES1) | (1 << WGM12) | (1 << CS12) | (1 << CS10); // Set for rising edge capture, CTC mode, clk/1024(from prescaler)
    TCCR1C = 0;                                                        // Not used
    TIMSK1 |= (1 << ICIE1) | (1 << OCIE1A);                            // Enable input capture interruption, set to output compare match A
}

void Timer::timerStartPWM(uint8_t thresholdOne = 0x00FE, uint8_t thresholdTwo = 0x00FE)
{
    OCR1A = thresholdOne; // threshold A
    OCR1B = thresholdTwo; // threshold B

    TCNT1 = 0x0000; // Set timer1 to 0

    TCCR1A |= ((1 << COM1A1) | (1 << COM1B1) | (1 << WGM10)); // Set to clear on compare match for A
    // and B thresholds, and set output to low level. Set to PWM phase correct, 8-bit
    TCCR1B |= (1 << CS11); // Set to clk#8 (from prescaler)
    TCCR1C = 0;            // Not used
    TIMSK1 = 0;            // Reset, not used for PWM
}
void Timer::timerStartPwmAdjustTop64(uint8_t top = 0x00FE, uint8_t threshold = 0x00FE)
{
    OCR1A = top;       // threshold A
    OCR1B = threshold; // threshold B

    TCNT1 = 0x0000; // Set timer1 to 0

    TCCR1A |= (1 << COM1A1) | (1 << COM1A0) | (1 << COM1B0) | (1 << COM1B1) | (1 << WGM10) | (1 << WGM11); 
    TCCR1B |= ((1 << CS10) | (1 << CS11) | (1 << WGM13)); // Set to clk#64 (from prescaler)
    TCCR1C = 0;                                           // Not used
    TIMSK1 = 0;                                           // Reset, not used for PWM
}
void Timer::timerStartPwmAdjustTop256(uint8_t top = 0x00FE, uint8_t threshold = 0x00FE)
{
    OCR1A = top;       // threshold A
    OCR1B = threshold; // threshold B

    TCNT1 = 0x0000; // Set timer1 to 0

    TCCR1A |= (1 << COM1A1) | (1 << COM1A0) | (1 << COM1B0) | (1 << COM1B1) | (1 << WGM10) | (1 << WGM11); 
    TCCR1B |= (1 << CS12) | (1 << WGM13); // Set to clk#256 (from prescaler
    TCCR1C = 0;                           // Not used
    TIMSK1 = 0;                           // Reset, not used for PWM
}
void Timer::timerEnd()
{
    OCR1A = 0;
    OCR1B = 0;

    TCNT1 = 0x0000;

    TCCR1A = 0;
    TCCR1B = 0;
    TCCR1C = 0;
    TIMSK1 = 0;
}

Timer::Timer()
{
    DDRD |= (1 << DDD4) | (1 << DDD5);
}

Timer::~Timer()
{
}
