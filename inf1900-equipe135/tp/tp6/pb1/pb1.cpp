/*
Identification:

    Travail : TP6_PROBLEME_1
    Section # : SECTION 5
    Équipe # : 135
    Correcteur : Stefan Cotargasanu, Romain Lebbadi-Breteau

Auteurs: Felix Perreault et Justin Boulet

Description du programme: 
    Programme qui change la couleur d'une DEL en fonction d'un bouton-poussoir et 
    d'une minuterie. Plus le bouton est tenu longtemps, plus la DEL va ensuite 
    clignoter de couleur rouge un grand nombre de fois, jusqu'a un maximum de 
    12 secondes ou le bouton peut etre tenu. Le robot revient ensuite a son etat
    original.
    

Broches I/O:
    IN <- Port D2
    OUT <- Port B0 et Port B1
 */

#include <avr/io.h> 
#include <avr/interrupt.h>
#define F_CPU 8000000
#include <util/delay.h>

volatile uint8_t gCompteur = 0; // selon le nom de votre variable
volatile bool gEtatBouton  = false;

// placer le bon type de signal d'interruption
// à prendre en charge en argument
ISR (TIMER1_COMPA_vect) 
{
    gCompteur++;
}


ISR (INT0_vect) 
{
    // Laisser un délai avant de confirmer la réponse du
    // bouton-poussoir: environ 30 ms (anti-rebond)
    _delay_ms (30);

    // se souvenir ici si le bouton est pressé ou relâché
    if (gEtatBouton == false){
        gEtatBouton = true;
    }
    else {
        gEtatBouton = false;
    }

    // Voir la note plus bas pour comprendre cette instruction et son rôle
    EIFR |= (1 << INTF0) ;
}

void partirMinuterie ( uint16_t duree ) {
// mode CTC du timer 1 avec horloge divisée par 1024
// interruption après la durée spécifiée
TCNT1   = 0x0000;
OCR1A   = duree;
TCCR1A |= (1 << COM1A0);
TCCR1B |= (1 << ICES1) | (1 << WGM12)|(1 << CS12)|(1 << CS10);
TCCR1C  = 0;
TIMSK1 |=  ((1 << ICIE1) | (1 << OCIE1A));
}

void initialisation ( void ) {
// cli est une routine qui bloque toutes les interruptions. 
//Il serait bien mauvais d'être interrompu alors que le 
//microcontrôleur n'est pas prêt...
cli ();

// configurer et choisir les ports pour les entrées
// et les sorties. DDRx... Initialisez bien vos variables
DDRB |= (1 << DDB0) | (1 << DDB1); //B0 et B1 en sortie
DDRD &= ~0x04; //D2 en entree

// cette procédure ajuste le registre EIMSK
// de l’ATmega324PA pour permettre les interruptions externes
EIMSK |= (1 << INT0) ;

// il faut sensibiliser les interruptions externes aux
// changements de niveau du bouton-poussoir
// en ajustant le registre EICRA
EICRA |= (1 << ISC00);

// sei permet de recevoir à nouveau des interruptions.
sei ();
}

int main()
{
initialisation();
int valeurClignotant;
while (true)
{
    if (gEtatBouton == true)
    {
        partirMinuterie(0x030D); //781 en hexadecimal, qui correspond a un dixieme de seconde
        while(true)
        {
            if (gCompteur == 120)
            {
                valeurClignotant = gCompteur;
                break;
            }
            else if (gEtatBouton == false)
            {
                valeurClignotant = gCompteur;
                break;
            }
        }
        bool etatLed = true;
        while (gCompteur < (valeurClignotant+5))
        {
            if (etatLed)
            {
                PORTB  |= (1 << PORTB0);
                etatLed = false;
            }
            else
            {
                PORTB  &= (0 << PORTB0);
                etatLed = true;
            }
            _delay_ms(50);
        }
        PORTB &= (0 << PORTB0);
        _delay_ms(2000);
        for (int i = 0; i < (valeurClignotant/2); i++)
        {
            PORTB |= (1 << PORTB1);
            _delay_ms(250);
            PORTB &= (0 << PORTB0);
            _delay_ms(250);
        }
        PORTB |= (1 << PORTB0); 
        _delay_ms(1000);
        PORTB &= (0 << PORTB0);
        gEtatBouton = false;
    }
}

}