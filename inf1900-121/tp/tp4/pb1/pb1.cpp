#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
const int DELAI=30;

volatile uint8_t compteur = 0;

void eteindre() 
{
    PORTA &= ~(PORTA);
}
void allumerRouge()
{
    eteindre();
    PORTA |= (1 << PORTA1);
}

void allumerVert() 
{
    eteindre();
    PORTA |= (1 << PORTA0);
}
void allumerambre(){
    while (PIND & (1<<PIND2))
    {
        _delay_ms(DELAI);
        allumerVert();
        _delay_ms(DELAI);
        allumerRouge();
    }
}
ISR(INT0_vect)
{
    _delay_ms(DELAI);
    compteur++;

    EIFR |= (1<<INTF0);
}

void initialisation()
{
    cli();
    DDRA |= (1 << DDA0) | (1 << DDA1); 
    DDRD &= ~(1 << DDD2);
    EIMSK |= (1 << INT0) ;
    EICRA |= (1<<ISC00) | (0<<ISC01);
    sei();
}

int main()
{ 
    initialisation();
    allumerRouge();
    for (;;)
    {
 switch(compteur){
        case 1: allumerambre();
                break;
        case 2: allumerVert();
                break;
        case 3: allumerRouge();
                break;
        case 4: eteindre();
                break;
        case 5: allumerVert();
                break;
        case 6: allumerRouge();
                compteur=0;
                break;
        }
    }
    return 0;

}
