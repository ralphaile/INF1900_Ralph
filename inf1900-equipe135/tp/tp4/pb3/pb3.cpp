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

volatile uint8_t gEtatMoteur = 0; // selon le nom de votre variable

ISR(TIMER1_COMPA_vect)
{
    if (gEtatMoteur == 0)
    {
        gEtatMoteur = 1;
        PORTD = 0x00;
    }
    else
    {
        gEtatMoteur = 0;
        PORTD = 1 << DDD4;
    }
}

void partirMinuterie()
{
    TCNT1 = 0x0000;
}
void ajustementPwm(uint8_t seuilAjustable)
{
    // mise à un des sorties OC1A et OC1B sur comparaison
    // réussie en mode PWM 8 bits, phase correcte
    // et valeur de TOP fixe à 0xFF (mode #1 de la table 16-5
    // page 130 de la description technique du ATmega324PA)
    OCR1A = seuilAjustable;
    OCR1B = seuilAjustable;

    // division d'horloge par 8 - implique une fréquence de PWM fixe
    TCCR1A |= ((1 << COM1A1) | (1 << COM1B1) | (1 << WGM10));
    TCCR1B |= (1 << CS11);
    TCCR1C = 0;
}

void initialisation(void)
{

    // cli est une routine qui bloque toutes les interruptions. Il serait
    // bien mauvais d'être interrompu alors que le microcontrôleur n'est pas prêt...
    cli();

    // configurer et choisir les ports pour les entrées
    // et les sorties. DDRx... Initialisez bien vos variables
    DDRD |= (1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7); // A0 et A1 en sortie
    DDRA |= (1 << DDA0) | (1 << DDA1);

    sei();
}

int main()
{
    initialisation();
    partirMinuterie();

    while (true)
    {
        ajustementPwm(0x0000);
        _delay_ms(2000);
        ajustementPwm(0x003F);
        _delay_ms(2000);
        ajustementPwm(0x007F);
        _delay_ms(2000);
        ajustementPwm(0x00BF);
        _delay_ms(2000);
        ajustementPwm(0x00FE);
        _delay_ms(2000);
    }
}