/*
Identification:

    Travail : TP2_PROBLEME_1
    Section # : SECTION 5
    Équipe # : 135
    Correcteur : Stefan Cotargasanu, Romain Lebbadi-Breteau

Auteurs: Felix Perreault et Justin Boulet

Description du programme: 
    Machine a etat de Moore qui allume une LED verte apres que le bouton ait 
    ete appuye puis relache 3 fois. Au moment ou le bouton est relache une 
    3eme fois, la LED s'allume pour une duree de 2 secondes. Nous avons utilise un
    switch-case ainsi qu'une classe "Etat" pour definir les etats de la machine.

Broches I/O:
    IN  <- Port D2
    OUT <- Port A0 et Port A1


+-------------------+----------------------------+----------------+---------------------+
| In (boutonEntree) | Etat present (etatPresent) | Out (LED vert) | Etat futur          |
+-------------------+----------------------------+----------------+---------------------+
| 0                 | INIT                       | 0              | INIT                |
+-------------------+----------------------------+----------------+---------------------+
| 1                 | INIT                       | 0              | APPUYER_UNE_FOIS    |
+-------------------+----------------------------+----------------+---------------------+
| 0                 | APPUYER_UNE_FOIS           | 0              | RELACHER_UNE_FOIS   |
+-------------------+----------------------------+----------------+---------------------+
| 1                 | APPUYER_UNE_FOIS           | 0              | APPUYER_UNE_FOIS    |
+-------------------+----------------------------+----------------+---------------------+
| 0                 | RELACHER_UNE_FOIS          | 0              | RELACHER_UNE_FOIS   |
+-------------------+----------------------------+----------------+---------------------+
| 1                 | RELACHER_UNE_FOIS          | 0              | APPUYER_DEUX_FOIS   |
+-------------------+----------------------------+----------------+---------------------+
| 0                 | APPUYER_DEUX_FOIS          | 0              | RELACHER_DEUX_FOIS  |
+-------------------+----------------------------+----------------+---------------------+
| 1                 | APPUYER_DEUX_FOIS          | 0              | APPUYER_DEUX_FOIS   |
+-------------------+----------------------------+----------------+---------------------+
| 0                 | RELACHER_DEUX_FOIS         | 0              | RELACHER_DEUX_FOIS  |
+-------------------+----------------------------+----------------+---------------------+
| 1                 | RELACHER_DEUX_FOIS         | 0              | APPUYER_TROIS_FOIS  |
+-------------------+----------------------------+----------------+---------------------+
| 0                 | APPUYER_TROIS_FOIS         | 0              | RELACHER_TROIS_FOIS |
+-------------------+----------------------------+----------------+---------------------+
| 1                 | APPUYER_TROIS_FOIS         | 0              | APPUYER_TROIS_FOIS  |
+-------------------+----------------------------+----------------+---------------------+
| 0                 | RELACHER_TROIS_FOIS        | 1              | INIT                |
+-------------------+----------------------------+----------------+---------------------+
| 1                 | RELACHER_TROIS_FOIS        | 1              | INIT                |
+-------------------+----------------------------+----------------+---------------------+
 
 */



#include <avr/io.h> 

#define F_CPU 8000000
#include <util/delay.h>


bool verifierBoutonAppuyee() 
{
    uint8_t boutonAppuyee = 1 << DDA2;
    uint8_t boutonEntree = PIND & boutonAppuyee;

    if (boutonEntree == boutonAppuyee)
    {
        return true;
    }
    else
    {
        return false;
    }
}


int main()
{
  
  enum class Etat {INIT, APPUYER_UNE_FOIS, RELACHER_UNE_FOIS, APPUYER_DEUX_FOIS, RELACHER_DEUX_FOIS, APPUYER_TROIS_FOIS, RELACHER_TROIS_FOIS};


  DDRA |= (1 << DDA0) | (1 << DDA1); // s'assurer d'avoir port DDA0 et DDA1 en sortie par bit
  DDRD &= ~0x04; // s'assurer d'avoir port DDD2 et DDD2 en entrée par bit

  int delaiLedAllumee = 2000; // Inserer ici la duree ou la LED est allumee

  Etat etatPresent = Etat::INIT;

  uint8_t ledAllumee = 1 << DDA0;
  uint8_t ledEteinte = 0 << DDA0;
  
  

  while(true) 
  {
    switch(etatPresent)
    {
        case Etat::INIT:
            if (verifierBoutonAppuyee() == true)
            {
                etatPresent = Etat::APPUYER_UNE_FOIS;
            }
            break;
        case Etat::APPUYER_UNE_FOIS:
            if (verifierBoutonAppuyee() == false)
            {
                etatPresent = Etat::RELACHER_UNE_FOIS;
            }
            break;
        case Etat::RELACHER_UNE_FOIS:
            if (verifierBoutonAppuyee() == true)
            {
                etatPresent = Etat::APPUYER_DEUX_FOIS;
            }
            break;
        case Etat::APPUYER_DEUX_FOIS:
            if (verifierBoutonAppuyee() == false)
            {
                etatPresent = Etat::RELACHER_DEUX_FOIS;
            }
            break;
        case Etat::RELACHER_DEUX_FOIS:
            if (verifierBoutonAppuyee() == true)
            {
                etatPresent = Etat::APPUYER_TROIS_FOIS;
            }
            break;
        case Etat::APPUYER_TROIS_FOIS:
            if (verifierBoutonAppuyee() == false)
            {
                etatPresent = Etat::RELACHER_TROIS_FOIS;
            }
            break;
        case Etat::RELACHER_TROIS_FOIS:
            PORTA = ledAllumee;
            _delay_ms(delaiLedAllumee);
            PORTA = ledEteinte;
            etatPresent = Etat::INIT;
            break;
    }
    
    
  }

  return 0; 
}

