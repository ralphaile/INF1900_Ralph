#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
uint8_t top = 0xff;
    uint8_t highPeriod=0;


void ajustementPwm ( uint8_t top,uint8_t highPeriod ) {

// mise à un des sorties OC1A et OC1B sur comparaison
// réussie en mode PWM 8 bits, phase correcte
// et valeur de TOP fixe à 0xFF (mode #1 de la table 16-5
// page 130 de la description technique du ATmega324PA)
OCR1A = top ;
OCR1B = highPeriod ;
// division d'horloge par 8 - implique une fréquence de PWM fixe
TCCR1A |= (1<<WGM10) | (1<<COM1A1);
TCCR1B |=  (1<<CS11) |(1<<WGM12) ;
TCCR1C = 0;
if(highPeriod<top)
    highPeriod+=0.25*top;
_delay_ms(2000);
}


void initialisation()
{
    DDRD |= (1<<DDD4) | (1<<DDD5);
    PORTD |= (0<<PORTD4);
}

int main()
{
    
    initialisation();
    while(1){
    ajustementPwm(top,highPeriod);
    }
return 0;
}
