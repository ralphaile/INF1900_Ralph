#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
const int DELAI=30;

volatile uint8_t gMinuterieExpiree;

volatile uint8_t gBoutonPoussoir;


void eteindre() 
{
    PORTA &= ~(PORTA);
}
void allumerRouge()
{
    eteindre();
    PORTA |= (1 << PORTA1);
}

void allumerVert() 
{
    eteindre();
    PORTA |= (1 << PORTA0);
}


ISR(TIMER1_COMPA_vect) {
gMinuterieExpiree = 1;
}


ISR (INT0_vect ) {
gBoutonPoussoir = 1;
// anti-rebond
_delay_ms(DELAI);
}

void partirMinuterie ( uint16_t duree ) {

gMinuterieExpiree = 0;
// mode CTC du timer 1 avec horloge divisée par 1024
// interruption après la durée spécifiée
TCNT1 = 0 ;
OCR1A = duree;
TCCR1A = 0 ;
TCCR1B |= (1<<CS12) | (0<<CS11) | (1<<CS10) ;
TCCR1C = 0;
TIMSK1 = (1<<OCIE1A) ;
}



void initialisation()
{
    cli();
    DDRA |= (1 << DDA0) | (1 << DDA1); 
    DDRD &= ~(1 << DDD2);
    EIMSK |= (1 << INT0) ;
    EICRA |= (1<<ISC00) | (1<<ISC01);
    sei();
}

int main()
{ 
    initialisation();
    for (int i = 0; i < 50; i++) {
        // Blink red light for 1/10th of a second
        allumerRouge(); // turn on red light
        _delay_ms(100);
        eteindre(); // turn off red light
        _delay_ms(100);
  }
partirMinuterie(7813);
    do {
// attendre qu'une des deux variables soit modifiée
// par une ou l'autre des interruptions.
} while ( gMinuterieExpiree == 0 && gBoutonPoussoir == 0 );
// Une interruption s'est produite. Arrêter toute
// forme d'interruption. Une seule réponse suffit.
cli ();
// Verifier la réponse
if(gMinuterieExpiree==1)
    allumerRouge();
else
    allumerVert();
while(1){
}
return 0;

}

