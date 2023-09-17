#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <memoire_24.h>

void initialisation()
{
    DDRA |= (1<<DDA0) | (1<<DDA1);
}

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

int main()
{
    
    initialisation();
    uint8_t mot []= "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";
    Memoire24CXXX memoir;
    memoir.ecriture(0x0000,mot,sizeof(mot)-1);
    _delay_ms(10);
    uint8_t tmp [sizeof(mot)];
    memoir.lecture(0x0000, tmp, sizeof(mot)-1);
    for(int i=0;i<sizeof(mot)-1;i++){
        if(tmp[i]!=mot[i]){
            allumerRouge();
            return 0;
        }
    }
    allumerVert();
    return 0;
}
