#ifndef LISTPOINT_H
#define LISTPOINT_H

#include <avr/io.h>
#include "memoire_24.h"
// #define F_CPU 8000000

typedef struct
{
    uint8_t x;
    uint8_t y;
} Point;

class ListPoint
{
public:
    // Constructor
    ListPoint();
    // Destructor
    ~ListPoint();

    void addPoint(uint8_t, uint8_t); // add a new point to the array
    // void removePoint(uint8_t,uint8_t); //remove a point from the array
    void addRelativePointAndPosition(uint8_t, uint8_t); // add point using relative to position coordinates, between -2 and 2)
    // void getListPoints(); //display points in the array in a list
    void changePosition(uint8_t, uint8_t);
    void writeListToMemory();
    void readListFromMemory();
    Point getPosition();

    Point arrayPoint[8];

    Point position;

    uint8_t nPoints = 0;

private:
};
#endif // LISTPOINT_H