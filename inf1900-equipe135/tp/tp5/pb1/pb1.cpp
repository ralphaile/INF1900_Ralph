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
#include <string.h>
#include "memoire_24.h"



int main()
{
    DDRA |= (1 << DDA0) | (1 << DDA1); // s'assurer d'avoir port DDA0 et DDA1 en sortie par bit
    
    const char* blocEcrit = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";
    uint8_t blocEcritConversion = *blocEcrit;
    uint8_t* ptrBlocEcritConversion = &blocEcritConversion;

    uint16_t adresse = 0x0000;
    
    Memoire24CXXX valeurEcrite;

    valeurEcrite.ecriture(adresse, ptrBlocEcritConversion, strlen(blocEcrit)+1);
    _delay_ms(5);

    char valeurLue[100];
    char* ptrValeurLue = valeurLue;
    uint8_t valeurLueConversion = *ptrValeurLue;
    uint8_t* ptrValeurLueConversion = &valeurLueConversion;

    valeurEcrite.lecture(adresse, ptrValeurLueConversion, strlen(blocEcrit)+1);

    int resultat = strcmp(blocEcrit, ptrValeurLue);

    if (resultat)
    {
        PORTA = 0x01;
    }
    else
    {
        PORTA = 0x00;
    }
    return 0;

}