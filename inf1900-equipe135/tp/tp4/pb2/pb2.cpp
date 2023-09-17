/*
Identification:

    Travail : TP4_PROBLEME_1
    Section # : SECTION 5
    Équipe # : 135
    Correcteur : Stefan Cotargasanu, Romain Lebbadi-Breteau

Auteurs: Felix Perreault et Justin Boulet

Description du programme: 
    

Broches I/O:
    IN  <- Port D2
    OUT <- Port A0 et Port A1



 
 */



#include <avr/io.h> 
#include <avr/interrupt.h>
#define F_CPU 8000000
#include <util/delay.h>

volatile uint8_t gEtatBouton = 0; // selon le nom de votre variable
volatile uint8_t gMinuterieExpiree = 0;

volatile uint8_t ledEtat = (0 << DDA0); 

// placer le bon type de signal d'interruption
// à prendre en charge en argument

ISR (TIMER1_COMPA_vect) 
{
gMinuterieExpiree = 1;
}

ISR (INT0_vect) 
{

// Laisser un délai avant de confirmer la réponse du
// bouton-poussoir: environ 30 ms (anti-rebond)
_delay_ms ( 30 );

// se souvenir ici si le bouton est pressé ou relâché
gEtatBouton = 1;

}

void partirMinuterie ( uint16_t duree ) {

gMinuterieExpiree = 0;

// mode CTC du timer 1 avec horloge divisée par 1024
// interruption après la durée spécifiée
TCNT1  = 0x0000;
OCR1A  = duree;
TCCR1A = (0x7C) & (1 << COM1A0);
TCCR1B = (0xED) & ((1 << ICES1) | (1 << WGM12)|(1 << CS12)|(1 << CS10));
TCCR1C = 0;
TIMSK1 =  (0xFA) & ((1 << ICIE1) | (1 << OCIE1A));

}

void initialisation ( void ) {

// cli est une routine qui bloque toutes les interruptions. Il serait bien mauvais d'être interrompu alors que le microcontrôleur n'est pas prêt...

cli ();


// configurer et choisir les ports pour les entrées
// et les sorties. DDRx... Initialisez bien vos variables
DDRA |= (1 << DDA0) | (1 << DDA1); //A0 et A1 en sortie
DDRD &= ~0x04; //D2 en entree



// cette procédure ajuste le registre EIMSK
// de l’ATmega324PA pour permettre les interruptions externes
EIMSK |= (1 << INT0) ;


// il faut sensibiliser les interruptions externes aux
// changements de niveau du bouton-poussoir
// en ajustant le registre EICRA

EICRA |= (1 << ISC00)| (1 << ISC01);


// sei permet de recevoir à nouveau des interruptions.

sei ();

}

int main()
{
    initialisation();
    uint8_t ledAllumeeVert = (0xFE) & (1 << DDA1); //(01 << DDA0); ceci fonctionne aussi, mais est laid
    uint8_t ledAllumeeRouge = (0xFD) & (1 << DDA0); //(10 << DDA0); ceci fonctionne aussi, mais est laid
    uint8_t ledEteint = (0 << DDA0) & (0 << DDA1);

    _delay_ms(10000);
    PORTA = ledAllumeeRouge;
    _delay_ms(100);
    PORTA = ledEteint;

    partirMinuterie(0x1E84); //equivaut a 7812
    do 
    {// attendre qu'une des deux variables soit modifiée
     // par une ou l'autre des interruptions.

    } while ( gMinuterieExpiree == 0 && gEtatBouton == 0 );


    // Une interruption s'est produite. Arrêter toute
    // forme d'interruption. Une seule réponse suffit.
    cli ();

    // Verifier la réponse
    if (gMinuterieExpiree == 1) {
        PORTA = ledAllumeeRouge; 
    }
    else {
        PORTA = ledAllumeeVert;
    }

}