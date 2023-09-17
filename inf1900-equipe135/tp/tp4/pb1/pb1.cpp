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
volatile uint8_t ledEtat = (0 << DDA0); 

// placer le bon type de signal d'interruption

// à prendre en charge en argument

ISR (INT0_vect) 
{

// Laisser un délai avant de confirmer la réponse du
// bouton-poussoir: environ 30 ms (anti-rebond)
_delay_ms ( 30 );

// se souvenir ici si le bouton est pressé ou relâché
gEtatBouton = 1;

// changements d'état tels que ceux de la
// semaine précédente
ledEtat = (1 << DDA0); 

// Voir la note plus bas pour comprendre cette instruction et son rôle
EIFR |= (1 << INTF0) ;

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
while (true)
{
    if (gEtatBouton == 1)
    {
        PORTA = ledEtat;
        _delay_ms(2000);
        ledEtat = (0 << DDA0);
        gEtatBouton = 0;
        PORTA = ledEtat;
    }
}

}