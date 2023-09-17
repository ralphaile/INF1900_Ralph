/*
Travail : TP6_PROBLEME_1
Section # : SECTION 5
Équipe # : 121
Correcteur : Stefan Cotargasanu, Romain Lebbadi-Breteau
Auteurs: Ralph Alaile et Ireina Hedad

Description programme:  Lorsque l'on enfonce le bouton, un compteur qui incrémente 10 fois par seconde est activé.
Quand le bouton est relâché ou lorsque le compteur atteint 120, la lumière clignote vert pendant 1/2 seconde. 
Ensuite, la carte mère ne fait rien pendant deux secondes. 
Ensuite, la lumière rouge s'allume et clignotee (compteur / 2) fois au rythme de 2 fois par seconde. 
Ensuite, la lumière tourne au vert pendant une seconde et s'éteint pour revenir attendre la prochaine fois 
que l'on actionne le bouton poussoir.

Broches I/O:
    IN <- Port D2
    OUT <- Port B0 et Port B1

Port D2 est utilisé pour lire l'état du bouton poussoir
Port B0 et B1 sont utilisés pour allumer la DEL
*/
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#define MINUTERIE_1S 7813 // La fréquence de notre robot est 8Mhz et avec un prescalar de 1024, apres environ 7813 cycles 1 seconde s'écoule
const int DELAI=30;
volatile bool gBoutonPoussoir=false;
volatile bool gMinuterieExpiree = false;

void eteindre() 
{
    PORTB &= ~(PORTB);
}
void allumerRouge()
{
    eteindre();
    PORTB |= (1 << PORTB1);
}

void allumerVert() 
{
    eteindre();
    PORTB |= (1 << PORTB0);
}

void partirMinuterie ( uint16_t  duree ) {

// mode CTC du timer 1 avec horloge divisée par 1024
// interruption après la durée spécifiée
// nous mettons gMinuterieExpiree a false pour qu'elle soit changée a true lors de l'interruption 
gMinuterieExpiree=false;
TCNT1 = 0 ;
OCR1A = duree;
TCCR1A = 0 ;
TCCR1B |= (1<<CS12) | (0<<CS11) | (1<<CS10) ;
TCCR1C = 0;
TIMSK1 = (1<<OCIE1A) ;
}


ISR(TIMER1_COMPA_vect) {
    gMinuterieExpiree = true;
}

ISR(INT0_vect) {
    _delay_ms(DELAI);
    if(PIND & (1<<PIND2))
        gBoutonPoussoir = true;
    else
        gBoutonPoussoir = false;
    EIFR |= (1 << INTF0) ;
}


void initialisation()
{
    cli();
    DDRB |= (1 << DDB0) | (1 << DDB1); 
    DDRD &= ~(1 << DDD2);
    EIMSK |= (1 << INT0) ;
    EICRA |= (1<<ISC00);
    sei();
}
void attendreMinuterie(){
    while(gMinuterieExpiree==false){}
}

int main() {
    initialisation();
    while (true) {
        int counter=0;
        // Attente de l'appui sur le bouton-poussoir
        while (gBoutonPoussoir==false) {}

        // Compteur qui incrémente 10 fois par seconde
        while (counter < 120 && gBoutonPoussoir==true) {
            partirMinuterie(MINUTERIE_1S / 10); //Delai de 100ms
            attendreMinuterie();
            counter++;
        }
        // Clignotement vert pendant 1/2 seconde
        for(int i=0; i<10; i++) {
            allumerVert();
            partirMinuterie(MINUTERIE_1S / 40);//Delai de 25ms
            attendreMinuterie();
            eteindre();
            partirMinuterie(MINUTERIE_1S / 40);
            attendreMinuterie();
        }  

        // Attente de 2 secondes
        partirMinuterie(MINUTERIE_1S * 2);
        attendreMinuterie();

        // Clignotement rouge (compteur / 2) fois au rythme de 2 fois par seconde
        for (int i = 0; i < counter / 2; ++i) {
            allumerRouge();
            partirMinuterie(MINUTERIE_1S / 4);//Delai de 250ms
            attendreMinuterie();
            eteindre();
            partirMinuterie(MINUTERIE_1S / 4);
            attendreMinuterie();
        }

        // Lumière verte pendant 1 seconde
        allumerVert();
        partirMinuterie(MINUTERIE_1S);
        attendreMinuterie();
        eteindre();
        gMinuterieExpiree=false;
        gBoutonPoussoir=false;
    }

        return 0;
}
