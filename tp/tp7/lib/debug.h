/*
File : ./tp7/lib/debug.h
Section # : SECTION 5
Team # : 121135
Correction : Stefan Cotargasanu, Romain Lebbadi-Breteau
Authors: Ralph Alaile, Ireina Hedad, Justin Boulet et Felix Perreault

Summary of the program: Used for debugging code. The DEBUG_PRINT function 
is defined only when using "make debug" command, and not other habitual make commands.

*/

#include "rS232.h"

// #define DEBUG // à mettre en commentaire ou non au besoin

// If DEBUG has been defined, DEBUG_PRINT(x) prints on computer terminal
// the value of x. X must be a table of char
#ifdef DEBUG
RS232 rs232;

#define DEBUG_PRINT(x)                           \
    for (unsigned int i = 0; i < sizeof(x); i++) \
    {                                            \
        rs232.USART_Transmit(x[i]);              \
    }

#else

// If DEBUG hasn't been defined, DEBUG_PRINT doesn't do anything (dead code)
#define DEBUG_PRINT(x) \
    do                 \
    {                  \
    } while (0) // code mort

#endif