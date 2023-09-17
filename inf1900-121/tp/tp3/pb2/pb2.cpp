#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>

int frequencyOne=60;
int frequencyTwo=400;
double b_one=(1/frequencyTwo)*1000;
double b_two=(1/frequencyTwo)*1000;
const int DELAI=50;

void initialization(){
    DDRB |= (1<<DDB0) | (1<<DDB1);
    PORTB |= (1<<PORTB1);
}


int main(){
    initialization();
    while(1){
        for(int a=0;a<=b_one; a=a+0.25*b_one){
            for(int i=0;i<2000*frequencyOne;i++){
                for(int j=0;i<a/DELAI;j++)
                {
                    PORTB |= (1<<PORTB0);
                    _delay_ms(DELAI);
                }
                for(int k=0;k<(b_one-a)/DELAI;k++){
                    PORTB &=~(PORTB);
                    _delay_ms(DELAI);
                }
            }
        
        }
        for(int a=0;a<=b_two; a=a+0.25*b_two){
            for(int i=0;i<2000*frequencyTwo;i++){
                for(int j=0;i<a/DELAI;j++)
                {
                    PORTB |= (1<<PORTB0);
                    _delay_ms(DELAI);
                }
                for(int k=0;k<(b_two-a)/DELAI;k++){
                    PORTB &=~(PORTB);
                    _delay_ms(DELAI);
                    }
            }
        }
    }
}