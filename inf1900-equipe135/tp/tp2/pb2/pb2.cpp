/*
Identification:

    Travail : TP2_PROBLEME_2
    Section # : SECTION 5
    Équipe # : 135
    Correcteur : Stefan Cotargasanu, Romain Lebbadi-Breteau

Auteurs: Felix Perreault et Justin Boulet

Description du programme: 
    Machine a etat de Moore qui allumera une LED bicolore, en fonction des etats de 
    la machine qui sont dictes par l'appui d'un bouton. Nous utilisons un switch-case afin de representer les etats de la 
    machine.
    
Broches I/O:
    IN  <- Port D2
    OUT <- Port A0 et Port A1

+-------------------+----------------------------+-----------+---------------------------+
| In (boutonEntree) | Etat present (etatPresent) | Out (LED) | Etat futur                |
+-------------------+----------------------------+-----------+---------------------------+
| 0                 | INIT_ROUGE                 | 10        | INIT_ROUGE                |
+-------------------+----------------------------+-----------+---------------------------+
| 1                 | INIT_ROUGE                 | 10        | APPUYER_UNE_FOIS_AMBRE    |
+-------------------+----------------------------+-----------+---------------------------+
| 0                 | APPUYER_UNE_FOIS_AMBRE     | 01/10*    | RELACHER_UNE_FOIS_VERT    |
+-------------------+----------------------------+-----------+---------------------------+
| 1                 | APPUYER_UNE_FOIS_AMBRE     | 01/10*    | APPUYER_UNE_FOIS_AMBRE    |
+-------------------+----------------------------+-----------+---------------------------+
| 0                 | RELACHER_UNE_FOIS_VERT     | 01        | RELACHER_UNE_FOIS_VERT    |
+-------------------+----------------------------+-----------+---------------------------+
| 1                 | RELACHER_UNE_FOIS_VERT     | 01        | APPUYER_DEUX_FOIS_ROUGE   |
+-------------------+----------------------------+-----------+---------------------------+
| 0                 | APPUYER_DEUX_FOIS_ROUGE    | 10        | RELACHER_DEUX_FOIS_ETEINT |
+-------------------+----------------------------+-----------+---------------------------+
| 1                 | APPUYER_DEUX_FOIS_ROUGE    | 10        | APPUYER_DEUX_FOIS_ROUGE   |
+-------------------+----------------------------+-----------+---------------------------+
| 0                 | RELACHER_DEUX_FOIS_ETEINT  | 00        | RELACHER_DEUX_FOIS_ETEINT |
+-------------------+----------------------------+-----------+---------------------------+
| 1                 | RELACHER_DEUX_FOIS_ETEINT  | 00        | APPUYER_TROIS_FOIS_VERT   |
+-------------------+----------------------------+-----------+---------------------------+
| 0                 | APPUYER_TROIS_FOIS_VERT    | 01        | INIT_ROUGE                |
+-------------------+----------------------------+-----------+---------------------------+
| 1                 | APPUYER_TROIS_FOIS_VERT    | 01        | APPUYER_TROIS_FOIS_VERT   |
+-------------------+----------------------------+-----------+---------------------------+
*Alterne entre les deux avec le clock*

*/


#include <avr/io.h> 

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
  
  enum class Etat {INIT_ROUGE, APPUYER_UNE_FOIS_AMBRE, RELACHER_UNE_FOIS_VERT, APPUYER_DEUX_FOIS_ROUGE, RELACHER_DEUX_FOIS_ETEINT, APPUYER_TROIS_FOIS_VERT,};

  DDRA |= (1 << DDA0) | (1 << DDA1); // s'assurer d'avoir port DDA0 et DDA1 en sortie par bit
  DDRD &= ~0x04; // s'assurer d'avoir port DDD2 et DDD2 en entrée par bit

  Etat etatPresent = Etat::INIT_ROUGE;
  
  bool conditionAmbre = true;

  uint8_t ledAllumeeVert = (0xFE) & (1 << DDA1); //(01 << DDA0); ceci fonctionne aussi, mais est laid
  uint8_t ledAllumeeRouge = (0xFD) & (1 << DDA0); //(10 << DDA0); ceci fonctionne aussi, mais est laid
  uint8_t ledEteint = (0 << DDA0) & (0 << DDA1);

  while (true)
  {

    switch(etatPresent)
    {
        case Etat::INIT_ROUGE:
            if (verifierBoutonAppuyee() == true)
            {
                etatPresent = Etat::APPUYER_UNE_FOIS_AMBRE;
            }
            PORTA = ledAllumeeRouge;
            break;
        case Etat::APPUYER_UNE_FOIS_AMBRE:
            if (verifierBoutonAppuyee() == false)
            {
                etatPresent = Etat::RELACHER_UNE_FOIS_VERT;
            }

            if (conditionAmbre == true)
            {
                PORTA = ledAllumeeVert;
                conditionAmbre = false;
            }

            else if (conditionAmbre == false)
            {
                PORTA = ledAllumeeRouge;
                conditionAmbre = true;
            }

            break;
        case Etat::RELACHER_UNE_FOIS_VERT:
            if (verifierBoutonAppuyee() == true)
            {
                etatPresent = Etat::APPUYER_DEUX_FOIS_ROUGE;
            }
            PORTA = ledAllumeeVert;
            break;
        case Etat::APPUYER_DEUX_FOIS_ROUGE:
            if (verifierBoutonAppuyee() == false)
            {
                etatPresent = Etat::RELACHER_DEUX_FOIS_ETEINT;
            }
            PORTA = ledAllumeeRouge;
            break;
        case Etat::RELACHER_DEUX_FOIS_ETEINT:
            if (verifierBoutonAppuyee() == true)
            {
                etatPresent = Etat::APPUYER_TROIS_FOIS_VERT;
            }
            PORTA = ledEteint;
            break;
        case Etat::APPUYER_TROIS_FOIS_VERT:
            if (verifierBoutonAppuyee() == false)
            {
                etatPresent = Etat::INIT_ROUGE;
            }
            PORTA = ledAllumeeVert;
            break;
    }
    
    
  }

  return 0; 
}

