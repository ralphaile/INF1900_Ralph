
#include <avr/io.h>
#include "ListPoint.h"
#define F_CPU 8000000UL
#include <util/delay.h>
#include "rS232.h"

ListPoint::ListPoint()
{
    position.x = 0;
    position.y = 0;
}
ListPoint::~ListPoint()
{
}

void ListPoint::addPoint(uint8_t x, uint8_t y)
{
    Point newPoint;
    newPoint.x = x;
    newPoint.y = y;
    arrayPoint[nPoints] = newPoint;
    nPoints++;
}

void ListPoint::addRelativePointAndPosition(uint8_t x, uint8_t y)
{
    uint8_t relativeX = x + position.x;
    uint8_t relativeY = y + position.y;
    
    if (relativeX > 7){relativeX = 7;}
    else if (relativeX < 0){relativeX = 0;}
    else if (relativeY > 3){relativeY = 3;}
    else if (relativeY < 0){relativeY = 0;}
    else{}

    addPoint(relativeX, relativeY);
    changePosition(relativeX, relativeY);
}
// void listPoint::removePoint(uint8_t x, uint8_t y)
// {
//     pointArray[x][y]= 0;
// }

// Point PointArray::getListPoints()
// {
//     uint8_t i = 0;
//     uint8_t j = 0;
//     uint8_t index = 0;
//     Point listPoints[nPoints];
//     for (i;i < 4;i++)
//     {
//         for (j;j < 9;j++)
//         if (pointArray[i][j]=1)
//         {
//             Point newPoint;
//             newPoint.x = i;
//             newPoint.y = j;
//             listPoints[index] = newPoint;
//             index++;
//         }
//         else {}
//     }
//     return listPoints;
// }

void ListPoint::changePosition(uint8_t x, uint8_t y)
{
    position.x = x;
    position.y = y;
}

// Point listPoint::getPosition()
// {
//     return position;
// }

void ListPoint::writeListToMemory()
{
    RS232 rs232;
    Memoire24CXXX memoire;
    uint16_t startingAdr = 0x0000;
    memoire.ecriture(startingAdr, this->nPoints);
    _delay_ms(5);
    startingAdr = startingAdr + 1;

    for (int i = 0; i <= nPoints; i++)
    {
        Point currentPoint = arrayPoint[i];
        memoire.ecriture(startingAdr, currentPoint.x);
        _delay_ms(5);
        memoire.ecriture(startingAdr + 1, currentPoint.y);
        _delay_ms(5);
        startingAdr = startingAdr + 2;
    }
}

void ListPoint::readListFromMemory()
{
    RS232 rs232;
    Memoire24CXXX memoire;
    uint16_t startingAdr = 0x0000;

    uint8_t ptrnPoints[1];
    memoire.lecture(startingAdr, ptrnPoints);
    nPoints = ptrnPoints[0];
    startingAdr = startingAdr + 1;
    uint8_t x[1];
    uint8_t y[1];

    for (int i = 0; i <= nPoints; i++)
    {
        memoire.lecture(startingAdr, x);
        arrayPoint[i].x = x[0];
        _delay_ms(5);
        memoire.lecture(startingAdr + 1, y);
        arrayPoint[i].y = y[0];
        _delay_ms(5);
        startingAdr = startingAdr + 2;
    }
}