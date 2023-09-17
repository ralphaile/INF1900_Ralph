/*
Identification:

    Travail : TP3_PROBLEME_1
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

#define F_CPU 8000000
#include <util/delay.h>

int main()
{

  DDRA |= (1 << DDA0) | (1 << DDA1); // s'assurer d'avoir port DDA0 et DDA1 en sortie par bit
  DDRD &= ~0x04; // s'assurer d'avoir port DDD2 et DDD2 en entrée par bit

  //double delaiLedAllumee = 3000; // en ms
  //double conversionBoucle = delaiLedAllumee/0.05; // 0 .05 en ms = 50 us 

  uint8_t ledAllumeeRouge = 0x01;//1 << DDA0;
  uint8_t ledAllumeeVert = 0x02;
  uint8_t ledEteinte = 0 << DDA0;
  int tempsAllume = 250;
  int tempsEteinte = 0;
  bool ledRougeVrai = true;
  int delaiRatio = 1;

    while (true)
    {
        for (int i = 0; i < 3000; i++)
        {
            if (ledRougeVrai){
                PORTA = ledAllumeeRouge;
            }
            else {
                PORTA = ledAllumeeVert;
            }
            for(int j = 0; j < tempsAllume; j++)
            {
                _delay_us(4);
            }

            PORTA = ledEteinte;
            for(int j = 0; j < tempsEteinte; j++)
            {
                _delay_us(4);
            }

            if (delaiRatio == 12)
            {
                tempsAllume--;
                tempsEteinte++;
                delaiRatio = 1;
            }
            else
            {
                delaiRatio++;
            }

        }
        tempsAllume = 250;
        tempsEteinte = 0;

        if (ledRougeVrai == true)
        {
            ledRougeVrai = false;
        }
        else {
            ledRougeVrai = true;
        }

    }

}