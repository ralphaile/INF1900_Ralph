
#include <avr/io.h>
#include <motor.h>


Motor::Motor()
{
    DDRB |= (1<<DDB2)|(1 << DDB3) | (1 << DDB4)  |(1<<DDB5); // Set ports for motor
}

void Motor::motorForward(uint8_t wheelOneSpeed, uint8_t wheelTwoSpeed)
{
    PORTB &= ~(1 << PB2);
    PORTB &= ~(1 << PB5);
    TCNT0 = 0x00;          // Initialize timer0 to 0
    OCR0A = wheelOneSpeed; // threshold for wheel one speed
    OCR0B = wheelTwoSpeed*0.96; // threshold for second wheel speed

    TCCR0A |= ((1 << COM0A1) | (1 << COM0B1) | (1 << WGM00)); // PWM phase correct, set on compare
    // match for A and B thresholds when downcounting. Clear when compare match during upcounting.
    // Set to PWM phase correct, 8-bit

    TCCR0B |= (1 << CS01); // Set to clk/8 (from prescaler)

}
void Motor::motorBackward(uint8_t wheelOneSpeed, uint8_t wheelTwoSpeed)
{
    PORTB |= (1 << PB2);
    PORTB |= (1 << PB5);
    TCNT0 = 0x00;          // Initialize timer0 to 0
    OCR0A = wheelOneSpeed; // threshold for wheel one speed, with inverted polarity (ROUE GAUCHE)
    OCR0B = wheelTwoSpeed*0.96; // threshold for second wheel speed, with inverted polarity (ROUE DROITE)

    TCCR0A |= ((1 << COM0A1) | (1 << COM0B1) | (1 << WGM00)); // PWM phase correct, clear on compare match
    // for A and B thresholds when upcounting. Set when compare match during downcounting.
    // Set to PWM phase correct, 8-bit

    TCCR0B |= (1 << CS01); // Set to clk/8 (from prescaler)
}

Motor::~Motor()
{
}