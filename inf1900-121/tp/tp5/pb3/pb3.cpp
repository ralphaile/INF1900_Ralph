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
void initialisationUART ( void ) {
// 2400 bauds. Nous vous donnons la valeur des deux
// premiers registres pour vous éviter des complications.
UBRR0H = 0;
UBRR0L = 0xCF;
// permettre la réception et la transmission par le UART0
UCSR0A = 0 ;
UCSR0B = (1<< RXEN0)| (1<< TXEN0) ;
// Format des trames: 8 bits, 1 stop bits, sans parité
UCSR0C = (1<< UCSZ00)|(1<<UCSZ01) ;
}
void transmissionUART ( uint8_t donnee ) {

/* Wait for empty transmit buffer */
while ( !( UCSR0A & (1<<UDRE0)))
        ;
/* Copy 9th bit to TXB8 */
UCSR0B &= ~(1<<TXB80);
if ( donnee & 0x0100 )
    UCSR0B |= (1<<TXB80);
/* Put data into buffer, sends the data */
UDR0 = donnee;

}

int main()
{
    
    initialisation();
    initialisationUART();
    uint8_t mot []= "happyBirthday to me\n";
    Memoire24CXXX memoir;
    memoir.ecriture(0x0000,mot,sizeof(mot)-1);
    _delay_ms(10);
    uint8_t tmp [sizeof(mot)];
    memoir.lecture(0x0000, tmp, sizeof(mot)-1);
    for(int j=0;j<100;j++){
    for(int i=0;i<sizeof(mot)-1;i++){
        transmissionUART ( tmp[i] );
    }}
    return 0;
}
