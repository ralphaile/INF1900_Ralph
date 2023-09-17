/*
File : ./tp9/exec/interpreter.h
Section # : SECTION 5
Team # : 121135
Correction : Stefan Cotargasanu, Romain Lebbadi-Breteau
Authors: Ralph Alaile, Ireina Hedad, Justin Boulet et Felix Perreault

Summary of the program: Used as a dictionary/interpreter for the instructions
encoded in the memory of the robot.

*/
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "debug.h"
#include "motor.h"
#include "interrupt.h"
#include "led.h"
#include "memoire_24.h"
// #include "rS232.h"
#include "timer.h"

enum Instruction
{
    DBT = 0x01,
    ATT = 0x02,
    DAL = 0x44,
    DET = 0x45,
    SGO = 0x48,
    SAR = 0x09,
    MAR1 = 0x60,
    MAR2 = 0x61,
    MAV = 0x62,
    MRE = 0x63,
    TRD = 0x64,
    TRG = 0x65,
    DBC = 0xC0,
    FBC = 0xC1,
    FIN = 0xFF,
};

void runDelayloop(uint8_t &operande)
{
    for (uint8_t i = 0; i < operande; i++)
    {
        _delay_ms(25);
    }
}

class Interpreter
{
private:
    bool isActive = false;
    bool endCommand = false;
    uint16_t index = 0;
    uint16_t maxIndex = 0;
    uint16_t loopIndex = 0;
    uint8_t totalLoops = 0;
    uint8_t loopCounter = 0;
    LED led;
    Motor motor;
    Timer timerSound;
    uint8_t wheelOneSpeed = 0;
    uint8_t wheelTwoSpeed = 0;
    bool isForward = false;

public:
    Interpreter();
    ~Interpreter();
    void startInterpreter();
    void runSwitchCase(uint8_t *, uint8_t *);
};

Interpreter::Interpreter(){};

Interpreter::~Interpreter(){};

void Interpreter::runSwitchCase(uint8_t *instruction, uint8_t *operande)
{
    // float frequency;
    // for(int i=0;i<20;i++){
    //     DEBUG_PRINT("\nINSTRUCTION: ");
    //     DEBUG_PRINT_INT(*instruction);
    //     DEBUG_PRINT("\nOPERANDE: ");
    //     DEBUG_PRINT_INT(*operande);
    // }
    if (*instruction == Instruction::DBT)
    {
        isActive = true;
        led.blinkGreenLight(2, 2);
    }
    if (isActive)
    {
        switch (*instruction)
        {
        case (Instruction::ATT):
            runDelayloop(*operande);
            break;

        case (Instruction::DAL):
            if (*operande == 0x01)
            {
                led.turnGreen();
            }
            else if (*operande == 0x02)
            {
                led.turnRed();
            }
            break;

        case (Instruction::DET):
            led.turnOff();
            break;

        case (Instruction::SGO):

            if (*operande == 0x2d)
            {
                uint8_t period = 0x8e;
                timerSound.timerStartPwmAdjustTop256(period, period / 2);
            }
            else if (*operande == 0x2e)
            {
                uint8_t period = 0x86;
                timerSound.timerStartPwmAdjustTop256(period, period / 2);
            }
            else if (*operande == 0x2f)
            {
                uint8_t period = 0x7e;
                timerSound.timerStartPwmAdjustTop256(period, period / 2);
            }
            else if (*operande == 0x30)
            {
                uint8_t period = 0xef;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else if (*operande == 0x31)
            {
                uint8_t period = 0xe2;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else if (*operande == 0x32)
            {
                uint8_t period = 0xd5;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else if (*operande == 0x33)
            {
                uint8_t period = 0xc9;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else if (*operande == 0x34)
            {
                uint8_t period = 0xbe;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else if (*operande == 0x35)
            {
                uint8_t period = 0xb3;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else if (*operande == 0x36)
            {
                uint8_t period = 0xa9;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else if (*operande == 0x37)
            {
                uint8_t period = 0x9f;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else if (*operande == 0x38)
            {
                uint8_t period = 0x96;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else if (*operande == 0x39)
            {
                uint8_t period = 0x8e;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else if (*operande == 0x3a)
            {
                uint8_t period = 0x86;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else if (*operande == 0x3b)
            {
                uint8_t period = 0x7f;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else if (*operande == 0x3c)
            {
                uint8_t period = 0x77;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else if (*operande == 0x3d)
            {
                uint8_t period = 0x71;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else if (*operande == 0x3e)
            {
                uint8_t period = 0x6b;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else if (*operande == 0x3f)
            {
                uint8_t period = 0x64;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else if (*operande == 0x40)
            {
                uint8_t period = 0x5e;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else if (*operande == 0x41)
            {
                uint8_t period = 0x59;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else if (*operande == 0x42)
            {
                uint8_t period = 0x54;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else if (*operande == 0x43)
            {
                uint8_t period = 0x50;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else if (*operande == 0x44)
            {
                uint8_t period = 0x4b;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else if (*operande == 0x45)
            {
                uint8_t period = 0x46;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else if (*operande == 0x46)
            {
                uint8_t period = 0x43;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else if (*operande == 0x47)
            {
                uint8_t period = 0x3f;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else if (*operande == 0x48)
            {
                uint8_t period = 0x3c;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else if (*operande == 0x49)
            {
                uint8_t period = 0x38;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else if (*operande == 0x4a)
            {
                uint8_t period = 0x35;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else if (*operande == 0x4b)
            {
                uint8_t period = 0x32;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else if (*operande == 0x4c)
            {
                uint8_t period = 0x2f;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else if (*operande == 0x4d)
            {
                uint8_t period = 0x2d;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else if (*operande == 0x4e)
            {
                uint8_t period = 0x2a;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else if (*operande == 0x4f)
            {
                uint8_t period = 0x28;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else if (*operande == 0x50)
            {
                uint8_t period = 0x26;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else if (*operande == 0x51)
            {
                uint8_t period = 0x24;
                timerSound.timerStartPwmAdjustTop256(period / 2, period / 4);
            }
            else
            {
            }

            break;

        case (Instruction::SAR): // TODO: Arreter sonorite
            timerSound.timerEnd();
            break;

        case (Instruction::MAR1):
            *instruction = Instruction::MAR2;

        case (Instruction::MAR2): // TODO: Arreter les moteurs
            wheelOneSpeed = wheelTwoSpeed = 0;
            motor.motorForward(wheelOneSpeed, wheelTwoSpeed);
            break;

        case (Instruction::MAV): // TODO: Avancer
            wheelOneSpeed = wheelTwoSpeed = *operande;
            motor.motorForward(wheelOneSpeed, wheelTwoSpeed);
            isForward = true;
            break;

        case (Instruction::MRE): // TODO: Reculer
            wheelOneSpeed = wheelTwoSpeed = *operande;
            motor.motorBackward(wheelOneSpeed, wheelTwoSpeed);
            isForward = false;
            break;

        case (Instruction::TRD): // TODO: Tourner droite: on peut arreter une roue et faire marche l'autre
            motor.motorForward(0, 0);
            _delay_ms(800);
            motor.motorForward(0x80, 0x00);
            _delay_ms(1500);
            motor.motorForward(0, 0);
            _delay_ms(800);
            if (isForward)
                motor.motorForward(wheelOneSpeed, wheelTwoSpeed);
            else
                motor.motorBackward(wheelOneSpeed, wheelTwoSpeed);
            break;

        case (Instruction::TRG): // TODO: Tourner gauche, meme principe que droite
            motor.motorForward(0, 0);
            _delay_ms(800);
            motor.motorForward(0x00, 0x80);
            _delay_ms(1800);
            motor.motorForward(0, 0);
            _delay_ms(800);
            if (isForward)
                motor.motorForward(wheelOneSpeed, wheelTwoSpeed);
            else
                motor.motorBackward(wheelOneSpeed, wheelTwoSpeed);
            break;

        case (Instruction::DBC): // TODO: Debut boucle
            loopIndex = index;
            totalLoops = *operande;
            break;

        case (Instruction::FBC): // TODO: Fin boucle
            if (loopCounter < totalLoops)
            {
                index = loopIndex;
                loopCounter++;
            }
            break;

        case (Instruction::FIN):
            wheelOneSpeed = wheelTwoSpeed = 0;
            motor.motorForward(wheelOneSpeed, wheelTwoSpeed);
            led.turnOff();
            timerSound.timerEnd();
            endCommand = true;
            isActive = false;
            led.blinkRedLight(2, 4);
            break;
        }
    }
}

void Interpreter::startInterpreter()
{
    Memoire24CXXX memory;
    uint16_t adr = 0x0000;
    uint8_t nbBytes[2];
    memory.lecture(adr, nbBytes, 2);
    maxIndex = ((static_cast<uint16_t>(nbBytes[0]) << 8 | static_cast<uint16_t>(nbBytes[1])) - sizeof(nbBytes));
    adr += 2;
    uint8_t instruction[1];
    uint8_t operande[1];
    index = 0;
    while (true)
    {
        memory.lecture(adr + index, instruction);
        memory.lecture(adr + index + 1, operande);
        runSwitchCase(instruction, operande);
        index += 2;
        if (endCommand)
            break;
    }
}

int main()
{
    Interpreter interpret;
    interpret.startInterpreter();
    return 0;
}