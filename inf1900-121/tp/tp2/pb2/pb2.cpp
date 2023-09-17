
/*
 *   Ireina Hedad
 *   Ralph Aile
 *   
 *   Ce programme permet de faire varier la LED du robot entre le rouge, le vert, l'ambre
 *   et la "couleur" éteint selon un certain ordre. Nous avons utiliser un switchcase pour 
 *   pouvoir decrire les états un par un et avons également ajouté des délais à certains 
 *   endroits pour s'assurer de voir à l'oeil les changements de couleurs.
 *
 *   Table des état:
 *   +--------+---+--------+--------+
 *   |   COULEUR_ROUGE     | 0 |   COULEUR_ROUGE | rouge |
 *   +--------+---+--------+--------+
 *   |                     | 1 |   COULEUR_VERT  | ambre |
 *   +--------+---+--------+--------+
 *   |    COULEUR_VERT     | 0 |   COULEUR_VERT  | vert  |
 *   +--------+---+--------+--------+
 *   |                     | 1 | COULEUR_ ETEINT | rouge |
 *   +--------+---+--------+--------+
 *   |   COULEUR_ ETEINT   | 0 | COULEUR_ ETEINT | éteint|
 *   +--------+---+--------+--------+
 *   |                     | 1 |   COULEUR_ROUGE | vert  |
 *
 *
 *
 * Nom: compteur 32 bits
 * Copyright (C) 2005 Matthew Khouzam
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description: Ceci est un exemple simple de programme
 * Version: 1.1
 */
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
const int DELAI=10;
enum class Etat { COULEUR_ETEINT, COULEUR_ROUGE, COULEUR_VERT };

void eteindre() {
    PORTA &= ~(PORTA);
}
void allumerRouge(){
    eteindre();
    PORTA |= (1 << PORTA1);
}

void allumerVert() {
    eteindre();
    PORTA |= (1 << PORTA0);
}
void allumerAmbre(){
    _delay_ms(DELAI);
    allumerVert();
    _delay_ms(DELAI);
    allumerRouge();
}
int main()
{

    DDRA |= (1 << DDA0) | (1 << DDA1); 
    DDRD &= ~(1 << DDD2);
    Etat etat = Etat::COULEUR_ROUGE; 

    while(true)
    {

        switch (etat) {
            case Etat::COULEUR_ROUGE:
                allumerRouge();
                while ((PIND & (1 << PIND2)))//Tant que le boutton est appuyé la couleur est ambre, quand il est relaché c'est vert
                {
                    allumerAmbre();
                    if (!(PIND & (1 << PIND2)))
                        etat = Etat::COULEUR_VERT;
                }
                break;
            case Etat::COULEUR_VERT:
                allumerVert();
                while ((PIND & (1 << PIND2)))//Tant que le boutton est appuyé la couleur est rouge, quand il est relaché c'est eteint
                {
                    _delay_ms(DELAI);
                    allumerRouge();
                    if (!(PIND & (1 << PIND2)))
                        etat = Etat::COULEUR_ETEINT;
                }
                break;
            case Etat::COULEUR_ETEINT:
                eteindre();
                while ((PIND & (1 << PIND2)))//Tant que le boutton est appuyé la couleur est verte, quand il est relaché c'est rouge
                {
                    _delay_ms(DELAI);
                    allumerVert();
                    if (!(PIND & (1 << PIND2)))
                        etat = Etat::COULEUR_ROUGE;
                }
                break;
        }
    }
    return 0;

}

