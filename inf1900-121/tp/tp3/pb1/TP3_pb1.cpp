/*
 * Nom: compteur 32 bits
 * Copyright (C) 2005 Matthew Khouzam
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description: Ceci est un exemple simple de programme
 * Version: 1.1
 */
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>

int main()
{
  DDRA = (1 << DDA0) | (1 << DDA1);
  PORTA = (1 << PORTA0);
  DDRD &= ~(1 << DDD2);
  const int DELAI =50;
  while(1) // boucle sans fin
  {
    double a=1000;
    double b=1000;
      for(int j=0;j<3000;j++)
      {
        PORTA |= (1 << PORTA0);
        for(int i=0;i<a;i++)
          _delay_us(1);
        PORTA &= ~(PORTA);
        for(int i=0;i<(b-a);i++)
          _delay_us(1);
        a-=1/3;
      }
  }
  return 0;

  }
