#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <debug.h>
#include <motor.h>
#include <interrupt.h>
#include <led.h>
#include <memoire_24.h>
//#include <rS232.h>
#include <timer.h>
#include <interpreter.h>


Interpreter::Interpreter(){};

Interpreter::~Interpreter(){};

enum Instruction{
    DBT=0x01,
    ATT=0x02,
    DAL=0x44,
    DET=0x45,
    SGO=0x48,
    SAR=0x09,
    MAR1=0x60,
    MAR2=0x61,
    MAV=0x62,
    MRE=0x63,
    TRD=0x64,
    TRG=0x65,
    DBC=0xC0,
    FBC=0xC1,
    FIN=0xFF,
};


void runDelayloop(uint8_t& operande)
{
    for (uint8_t i = 0; i < operande; i++)
    {
        _delay_ms(25);
    }
}
void runSwitchCase(uint8_t* instruction, uint8_t* operande, bool& isActive,bool& endInstructions)
{
    switch (*instruction)
    {
        case(DBT):
            isActive = true;
            break;
        case(ATT):
            if (isActive){
                runDelayloop(*operande);
            }
            break;
        case(DAL):
            if (isActive)
            {
                // if (operande == 0)
                // {
                    
                // }
                LED led;
                if (*operande == 0x01)
                {
                    led.turnGreen();
                }
                else if (*operande == 0x02)
                {
                    led.turnRed();
                }
                else{}
            }
            break;
        case(DET):

            if (isActive)
                {
                    LED led;
                    led.turnOff();
                }
            break;
        
        case(SGO):
            if (isActive)
            {
                Timer timerSound;
                {
                    if(*operande == 0x2d)
                    {
                        uint8_t period = 0x47;
                        timerSound.timerStartPwmAdjustTop1024(period,period/2);
                    }
                    else if(*operande == 0x2e)
                    {
                        uint8_t period = 0x43;
                        timerSound.timerStartPwmAdjustTop1024(period,period/2);
                    }
                    else if(*operande == 0x2f)
                    {
                        uint8_t period = 0x3f;
                        timerSound.timerStartPwmAdjustTop1024(period,period/2);
                    }
                    else if(*operande == 0x30)
                    {
                        uint8_t period = 0x3b;
                        timerSound.timerStartPwmAdjustTop1024(period,period/2);
                    }
                    else if(*operande == 0x31)
                    {
                        uint8_t period = 0x38;
                        timerSound.timerStartPwmAdjustTop1024(period,period/2);
                    }
                    else if(*operande == 0x32)
                    {
                        uint8_t period = 0x35;
                        timerSound.timerStartPwmAdjustTop1024(period,period/2);
                    }
                    else if(*operande == 0x33)
                    {
                        uint8_t period = 0x32;
                        timerSound.timerStartPwmAdjustTop1024(period,period/2);
                    }
                    else if(*operande == 0x34)
                    {
                        uint8_t period = 0x2f;
                        timerSound.timerStartPwmAdjustTop1024(period,period/2);
                    }
                    else if(*operande == 0x35)
                    {
                        uint8_t period = 0x2c;
                        timerSound.timerStartPwmAdjustTop1024(period,period/2);
                    }
                    else if(*operande == 0x36)
                    {
                        uint8_t period = 0x2a;
                        timerSound.timerStartPwmAdjustTop1024(period,period/2);
                    }
                    else if(*operande == 0x37)
                    {
                        uint8_t period = 0x27;
                        timerSound.timerStartPwmAdjustTop1024(period,period/2);
                    }
                    else if(*operande == 0x38)
                    {
                        uint8_t period = 0x25;
                        timerSound.timerStartPwmAdjustTop1024(period,period/2);
                    }
                    else if(*operande == 0x39)
                    {
                        uint8_t period = 0x23;
                        timerSound.timerStartPwmAdjustTop1024(period,period/2);
                    }
                    else if(*operande == 0x3a)
                    {
                        uint8_t period = 0x86;
                        timerSound.timerStartPwmAdjustTop256(period,period/2);
                    }
                    else if(*operande == 0x3b)
                    {
                        uint8_t period = 0x7f;
                        timerSound.timerStartPwmAdjustTop256(period,period/2);
                    }
                    else if(*operande == 0x3c)
                    {
                        uint8_t period = 0x77;
                        timerSound.timerStartPwmAdjustTop256(period,period/2);
                    }
                    else if(*operande == 0x3d)
                    {
                        uint8_t period = 0x71;
                        timerSound.timerStartPwmAdjustTop256(period,period/2);
                    }
                    else if(*operande == 0x3e)
                    {
                        uint8_t period = 0x6b;
                        timerSound.timerStartPwmAdjustTop256(period,period/2);
                    }
                    else if(*operande == 0x3f)
                    {
                        uint8_t period = 0x64;
                        timerSound.timerStartPwmAdjustTop256(period,period/2);
                    }
                    else if(*operande == 0x40)
                    {
                        uint8_t period = 0x5e;
                        timerSound.timerStartPwmAdjustTop256(period,period/2);
                    }
                    else if(*operande == 0x41)
                    {
                        uint8_t period = 0x59;
                        timerSound.timerStartPwmAdjustTop256(period,period/2);
                    }
                    else if(*operande == 0x42)
                    {
                        uint8_t period = 0x54;
                        timerSound.timerStartPwmAdjustTop256(period,period/2);
                    }
                    else if(*operande == 0x43)
                    {
                        uint8_t period = 0x50;
                        timerSound.timerStartPwmAdjustTop256(period,period/2);
                    }
                    else if(*operande == 0x44)
                    {
                        uint8_t period = 0x4b;
                        timerSound.timerStartPwmAdjustTop256(period,period/2);
                    }
                    else if(*operande == 0x45)
                    {
                        uint8_t period = 0x46;
                        timerSound.timerStartPwmAdjustTop256(period,period/2);
                    }
                    else if(*operande == 0x46)
                    {
                        uint8_t period = 0x;
                        timerSound.timerStartPwmAdjustTop256(period,period/2);
                    }
                }
            }
            break;



        case(FIN):
            endInstructions = true;
            isActive = false;
            break;
    }
}



void Interpreter::startInterpreter()
{
    uint8_t adr = 0x00;
    uint8_t* instruction=0;
    uint8_t* operande=0;
    bool isActive = false;
    bool endInstructions = false;
    LED led;

    while (true)
    {
        
        Memoire24CXXX memory;
        memory.lecture(adr, instruction);
        adr++;
        memory.lecture(adr, operande);
        adr++;

        runSwitchCase(instruction, operande,isActive,endInstructions); 
        if (endInstructions){break;}
        else{}
    }
}