

#include <avr/io.h> 
#include <TimerStart.h>

void Timer::timerStartCTC( uint16_t duration) 
{
// mode CTC du timer 1 avec horloge divisée par 1024
// interruption après la durée spécifiée
TCNT1  = 0x0000;
OCR1A  = duration;
TCCR1A = 0;
TCCR1B =(1 << ICES1) | (1 << WGM12)|(1 << CS12)|(1 << CS10);
TCCR1C = 0;
TIMSK1 = (1 << ICIE1) | (1 << OCIE1A);
}


void Timer::timerStartPWM(uint8_t threshold)
{
// mise à un des sorties OC1A et OC1B sur comparaison
// réussie en mode PWM 8 bits, phase correcte
// et valeur de TOP fixe à 0xFF (mode #1 de la table 16-5
// page 130 de la description technique du ATmega324PA)
OCR1A = threshold;
OCR1B = threshold;
// division d'horloge par 8 - implique une fréquence de PWM fixe
TCCR1A |= ((1 << COM1A1) | (1 << COM1B1) | (1 << WGM10));
TCCR1B |= (1 << CS11);
TCCR1C = 0;
}

Timer::Timer()
{
}

Timer::~Timer()
{
}
