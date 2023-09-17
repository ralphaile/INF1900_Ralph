
#include <avr/io.h>
#include <motor.h>

void Motor::motorForward(uint8_t wheelOneSpeed, uint8_t wheelTwoSpeed)
{

    TCNT0 = 0x00;          // Initialize timer0 to 0
    OCR0A = wheelOneSpeed; // threshold for wheel one speed
    OCR0B = wheelTwoSpeed; // threshold for second wheel speed

    TCCR0A |= ((1 << COM0A1) | (1 << COM0B1) | (1 << WGM00)); // PWM phase correct, set on compare
    // match for A and B thresholds when downcounting. Clear when compare match during upcounting.
    // Set to PWM phase correct, 8-bit

    TCCR0B |= (1 << CS01); // Set to clk/8 (from prescaler)

}

Motor::Motor()
{
    DDRB |= (1 << DDB3) | (1 << DDB4); // Set ports for motor
}

Motor::~Motor()
{
}