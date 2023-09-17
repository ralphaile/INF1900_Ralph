/*
File : ./tp7/exec/main.cpp
Section # : SECTION 5
Team # : 121135
Correction : Stefan Cotargasanu, Romain Lebbadi-Breteau
Authors: Ralph Alaile, Ireina Hedad, Justin Boulet et Felix Perreault

Summary of the program: Main executable of the program, using the library.

*/

#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "debug.h"
#include "motor.cpp"
#include "interrupt.cpp"

// enum class Etat{ INIT, PREMIER_CLICK, SECOND_CLICK };
// const int DELAI=20;
// const int TEMPS_ALLUMER=2000;
// void attendreClick(){
//     while(!(PIND & (1 << PIND2))){
//             _delay_ms(DELAI);
//     }
// }
// void attendreRelache(Etat etat){//On attend que le bouton est relache, mais si l'etat apres le click est l'etat initial donc on doit allumer la DEL pour 2 secondes.
//     if(etat== Etat::INIT){
//         DEBUG_PRINT("ALLUMER LED\n");
//         PORTA |= (1 << PORTA0);
//         _delay_ms(TEMPS_ALLUMER);
//         PORTA &= ~(1 << PORTA0);
//     }
//     while((PIND & (1 << PIND2))){
//             _delay_ms(DELAI);
//     }
// }
int main()
{
    // DDRA |= (1 << DDA0)|(1<<DDA1);
    // DDRD &= ~(1 << DDD2);
    // Etat etat = Etat::INIT;
    // while(true) // boucle sans fin
    // {
    //     switch (etat)
    //     {
    //     case Etat::INIT:
    //         DEBUG_PRINT("INIT\n");
    //         PORTA &= ~(PORTA);
    //         attendreClick();
    //         etat = Etat::PREMIER_CLICK;
    //         attendreRelache(etat);
    //         break;
    //     case Etat::PREMIER_CLICK:
    //         DEBUG_PRINT("PREMIER_CLICK\n");
    //         attendreClick();
    //         etat = Etat::SECOND_CLICK;
    //         attendreRelache(etat);
    //         break;
    //     case Etat::SECOND_CLICK:
    //         DEBUG_PRINT("SECOND_CLICK\n");
    //         attendreClick();
    //         etat = Etat::INIT;
    //         attendreRelache(etat);
    //         break;
    //     }
    // }
    // return 0;

    // Motor motor;
    // motor.motorForward(0xFF,0xFF);

    // Interrupt interrupt;
    // interrupt.initializeFallingEdge();

    // if (yoyo == true)
    // {
    //     PORTA = 0x01;
    // }
    // else
    // {
    //     PORTA = 0x00;
    // }
}