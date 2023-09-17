/*
Identification:

    Travail : TP6_PROBLEME_2
    Section # : SECTION 5
    Équipe # : 135
    Correcteur : Stefan Cotargasanu, Romain Lebbadi-Breteau

Auteurs: Felix Perreault et Justin Boulet

Description du programme: 
    Programme qui change la couleur d'une DEL en fonction de la lumiere ambiante 
    captee par une photoresistance. La DEL allume en vert lorsque la lumiere 
    ambiante est faible, puis ambre lorsque la lumiere est moyenne et enfin rouge 
    lorsque la lumiere captee est forte.
    

Broches I/O:
    IN <- Port A0 et Port A1
    OUT <- Port B0 et Port B1
 */



#include <avr/io.h> 
#include <avr/interrupt.h>
#include <can.h>
#define SHIFT_UN 1
#define SHIFT_DEUX 2
#define SHIFT_ZERO 0



int main()
{
    DDRB |= (1 << DDB0) | (1 << DDB1);
    DDRA &= ~0x03; 

    can convertisseur;
    uint8_t ledVerte    = 1 << SHIFT_ZERO;
    uint8_t ledRouge    = 1 << SHIFT_UN;
    uint8_t indiceAmbre = false;

    while (true)
    {
        uint8_t etatCapteur                  = PINA & (1 << PINA0);
        uint16_t lectureConvertisseur        = convertisseur.lecture(etatCapteur); // convertisseur.lecture est 10 bits
        uint8_t lectureConvertisseurHuitBits = (lectureConvertisseur >> SHIFT_DEUX); // passer le 10 bits en 8 bits en shiftant 2 fois

        if (lectureConvertisseurHuitBits >= 0x00 && lectureConvertisseurHuitBits < 0xB0)
        {
            
            PORTB = ledVerte;
        }
        else if (lectureConvertisseurHuitBits >= 0xF0)
        {
            PORTB = ledRouge;
        }
        else if (lectureConvertisseurHuitBits >= 0xB0 && lectureConvertisseurHuitBits < 0xF0)
        {
            if (indiceAmbre == false)
            {
                PORTB       = ledVerte;
                indiceAmbre = true;
            }
            else 
            {
                PORTB       = ledRouge;
                indiceAmbre = false;
            }
        }
    }
}