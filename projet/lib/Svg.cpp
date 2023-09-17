#include "Svg.h"
#include "rS232.h"
#include "stdlib.h"
#include "string.h"
// Convex Hull using Jarvis’ Algorithm or Wrapping
// https://www.geeksforgeeks.org/convex-hull-using-jarvis-algorithm-or-wrapping/
// Modifié par Justin Boulet le 31/03/2023
// A C++ program to find convex hull of a set of points. Refer
// https://www.geeksforgeeks.org/orientation-3-ordered-points/
// for explanation of orientation()
  
// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
#define CRC32_POLYNOMIAL 0xEDB88320L
void Svg::calculateCRC(uint8_t* data, uint32_t length)
{
    for (uint32_t i = 0; i < length; i++) {
        crc32 = crc32 ^ data[i];
        for (uint8_t j = 0; j < 8; j++) {
            if (crc32 & 1) {
                crc32 = (crc32 >> 1) ^ CRC32_POLYNOMIAL;
            } else {
                crc32 = crc32 >> 1;
            }
        }
    }
}
uint8_t Svg::orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
  
    if (val == 0) return 0;  // collinear
    if (val > 0) return 1; // clock or counterclock wise
    else return 2;
}
// Prints convex hull of a set of n points.
ListPoint Svg::convexHull(ListPoint points)
{
    // Initialize Result
    ListPoint hull; 
  
    // Find the leftmost point
    uint8_t l = 0;
    for (uint8_t i = 1; i < points.nPoints; i++)
        if (points.arrayPoint[i].x < points.arrayPoint[l].x)
            l = i;
  
    // Start from leftmost point, keep moving counterclockwise
    // until reach the start point again.  This loop runs O(h)
    // times where h is number of points in result or output.
    uint8_t p = l, q;
    do
    {
        // Add current point to result
        hull.addPoint(points.arrayPoint[p].x, points.arrayPoint[p].y);
  
        // Search for a point 'q' such that orientation(p, q,
        // x) is counterclockwise for all points 'x'. The idea
        // is to keep track of last visited most counterclock-
        // wise point in q. If any point 'i' is more counterclock-
        // wise than q, then update q.
        q = (p+1) % points.nPoints;
        for (uint8_t i = 0; i < points.nPoints; i++)
        {
           // If i is more counterclockwise than current q, then
           // update q
           if (orientation(points.arrayPoint[p], points.arrayPoint[i], points.arrayPoint[q]) == 2)
               q = i;
        }
  
        // Now q is the most counterclockwise with respect to p
        // Set p as q for next iteration, so that q is added to
        // result 'hull'
        p = q;
  
    } while (p != l);  // While we don't come to first point
  
    return hull;
}
uint16_t Svg::absoluteValue(int16_t value) {
    if (value < 0) {
        return -value;
    }
    else {
        return value;
    }
}
// baser sur la formule du shoelace
uint16_t Svg::calculateArea(ListPoint points) {
    int16_t area = 0;
    uint8_t n = points.nPoints;
    for (uint8_t j = 0; j < n; j++) {
        points.arrayPoint[j].x *= 11;
        points.arrayPoint[j].y *= 11;
    }
    for (uint8_t i = 0; i < n; ++i) {
        area += points.arrayPoint[i].x * points.arrayPoint[(i+1) % n].y - points.arrayPoint[i].y * points.arrayPoint[(i+1) % n].x;
    }
    return absoluteValue(area/2);
}
void Svg::constructSVG(ListPoint points, ListPoint pillars)
{
    RS232 rs232;
    char startSVG[] = "<svg width=\"100%\" height=\"100%\" xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 1152 576\">\n\t<rect xmlns=\"http://www.w3.org/2000/svg\" x=\"96\" y=\"48\"  width=\"960\" height=\"480\" stroke=\"black\" stroke-width=\"1\" fill=\"white\"/>\n\t<polygon points=\"";
    
    for (uint8_t i = 0; i < strlen(startSVG); i++)
    {
        rs232.USART_Transmit(startSVG[i]);
    }
    calculateCRC((uint8_t*)startSVG, strlen(startSVG));
    char pointsCoordonateSVG [points.nPoints * 6]; // car chaque points est 6 char exemple le point 1,1 est 301, 233
    uint8_t indexPointsCoordonateSVG = 0;
    
    for (uint8_t i = 0; i < points.nPoints; i++)
    {
        uint16_t valueX = points.arrayPoint[i].x;
        uint16_t valueY = points.arrayPoint[i].y;
        valueX = 195 + valueX * 110;
        valueY = 458 - valueY * 110;
        uint16_t valueXHundred = valueX - (valueX % 100);
        uint16_t valueXFirst = valueXHundred / 100;
        uint16_t valueXTenAndUnit = valueX - valueXHundred;
        uint16_t valueXTen = valueXTenAndUnit - (valueXTenAndUnit % 10);
        uint16_t valueXSecond = valueXTen / 10;
        uint16_t valueXThird = valueXTenAndUnit - valueXTen;
        uint16_t valueYHundred = valueY - (valueY % 100);
        uint16_t valueYFirst = valueYHundred / 100;
        uint16_t valueYTenAndUnit = valueY - valueYHundred;
        uint16_t valueYTen = valueYTenAndUnit - (valueYTenAndUnit % 10);
        uint16_t valueYSecond = valueYTen / 10;
        uint16_t valueYThird = valueYTenAndUnit - valueYTen;        
        pointsCoordonateSVG[indexPointsCoordonateSVG++] = '0' + valueXFirst;
        pointsCoordonateSVG[indexPointsCoordonateSVG++] = '0' + valueXSecond;
        pointsCoordonateSVG[indexPointsCoordonateSVG++] = '0' + valueXThird;
        pointsCoordonateSVG[indexPointsCoordonateSVG++] = '0' + valueYFirst;
        pointsCoordonateSVG[indexPointsCoordonateSVG++] = '0' + valueYSecond;
        pointsCoordonateSVG[indexPointsCoordonateSVG++] = '0' + valueYThird;
    }
    char space[]=" ";
    char virgule[]=",";
    for(uint8_t i = 0; i < sizeof(pointsCoordonateSVG); i = i+6)
    {
        rs232.USART_Transmit(pointsCoordonateSVG[i]);
        rs232.USART_Transmit(pointsCoordonateSVG[i+1]);
        rs232.USART_Transmit(pointsCoordonateSVG[i+2]);

        calculateCRC((uint8_t*)(pointsCoordonateSVG+i), 3);
        rs232.USART_Transmit(virgule[0]);
        calculateCRC((uint8_t*)virgule, strlen(virgule));
        rs232.USART_Transmit(pointsCoordonateSVG[i+3]);
        rs232.USART_Transmit(pointsCoordonateSVG[i+4]);
        rs232.USART_Transmit(pointsCoordonateSVG[i+5]);
        calculateCRC((uint8_t*)(pointsCoordonateSVG+i+3), 3);
        rs232.USART_Transmit(space[0]);
        calculateCRC((uint8_t*)space, strlen(space));
    }
    char endSVGPolygon[] = "\" fill=\"green\" stroke=\"black\" stroke-width=\"1\" />\n\t";
    for(uint8_t i = 0; i < strlen(endSVGPolygon); i++)
    {
        rs232.USART_Transmit(endSVGPolygon[i]);
    }
    calculateCRC((uint8_t*)endSVGPolygon, strlen(endSVGPolygon));
    char startSVGPoints[] = "<rect xmlns=\"http://www.w3.org/2000/svg\" x=\"";
    char midSVGPoints[] = "\" y=\"";
    char endSVGPoints[] = "\" width=\"8\" height=\"8\" stroke=\"black\" stroke-width=\"1\" fill=\"black\" />\n\t";
    char markCoordonateSVG [192]; // car chaque points est 6 char exemple le point 1,1 est 301, 233
    uint8_t indexMarkCoordonateSVG = 0;
    
   
    for (uint8_t x = 0; x < 8; x++)
    {
        for(uint8_t y = 0; y < 4; y++) {
            uint16_t valueX = 191 + x * 110;
            uint16_t valueY = 123 + y * 110;
            uint16_t valueXHundred = valueX - (valueX % 100);
            uint16_t valueXFirst = valueXHundred / 100;
            uint16_t valueXTenAndUnit = valueX - valueXHundred;
            uint16_t valueXTen = valueXTenAndUnit - (valueXTenAndUnit % 10);
            uint16_t valueXSecond = valueXTen / 10;
            uint16_t valueXThird = valueXTenAndUnit - valueXTen;
            uint16_t valueYHundred = valueY - (valueY % 100);
            uint16_t valueYFirst = valueYHundred / 100;
            uint16_t valueYTenAndUnit = valueY - valueYHundred;
            uint16_t valueYTen = valueYTenAndUnit - (valueYTenAndUnit % 10);
            uint16_t valueYSecond = valueYTen / 10;
            uint16_t valueYThird = valueYTenAndUnit - valueYTen;        
            markCoordonateSVG[indexMarkCoordonateSVG++] = '0' + valueXFirst;
            markCoordonateSVG[indexMarkCoordonateSVG++] = '0' + valueXSecond;
            markCoordonateSVG[indexMarkCoordonateSVG++] = '0' + valueXThird;
            markCoordonateSVG[indexMarkCoordonateSVG++] = '0' + valueYFirst;
            markCoordonateSVG[indexMarkCoordonateSVG++] = '0' + valueYSecond;
            markCoordonateSVG[indexMarkCoordonateSVG++] = '0' + valueYThird;
        }
    }
    
    for (uint8_t i = 0; i < sizeof(markCoordonateSVG); i = i + 6)
    {
        for (uint8_t j = 0; j < strlen(startSVGPoints); j++)
        {
            rs232.USART_Transmit(startSVGPoints[j]);
        }
        calculateCRC((uint8_t*)startSVGPoints, strlen(startSVGPoints));
        rs232.USART_Transmit(markCoordonateSVG[i]);
        rs232.USART_Transmit(markCoordonateSVG[i+1]);
        rs232.USART_Transmit(markCoordonateSVG[i+2]);
        calculateCRC((uint8_t*)(markCoordonateSVG+i), 3);
        for (uint8_t j = 0; j < strlen(midSVGPoints); j++)
        {   rs232.USART_Transmit(midSVGPoints[j]);
        }
        calculateCRC((uint8_t*)midSVGPoints, strlen(midSVGPoints));
        rs232.USART_Transmit(markCoordonateSVG[i+3]);
        rs232.USART_Transmit(markCoordonateSVG[i+4]);
        rs232.USART_Transmit(markCoordonateSVG[i+5]);
        calculateCRC((uint8_t*)(markCoordonateSVG+i+3), 3);
        for (uint8_t j = 0; j < strlen(endSVGPoints); j++)
        {  
            rs232.USART_Transmit(endSVGPoints[j]);
        }
        calculateCRC((uint8_t*)endSVGPoints, strlen(endSVGPoints));
    }
    char startPillarSVG[] = "<circle cx=\"";
    char midPillarSVG[] = "\" cy=\"";
    char endPillarSVG[] = "\" r=\"16\" stroke=\"black\" stroke-width=\"2\" fill=\"gray\" />\n\t";
    char pillarsCoordonateSVG [pillars.nPoints * 6]; // car chaque points est 6 char exemple le point 1,1 est 301, 233
    
    uint8_t indexPillarsCoordonateSVG = 0;
    for (uint8_t i = 0; i < pillars.nPoints; i++)
    {
        uint16_t valueX = pillars.arrayPoint[i].x;
        uint16_t valueY = pillars.arrayPoint[i].y;
        valueX = 195 + valueX * 110;
        valueY = 458 - valueY * 110;
        uint16_t valueXHundred = valueX - (valueX % 100);
        uint16_t valueXFirst = valueXHundred / 100;
        uint16_t valueXTenAndUnit = valueX - valueXHundred;
        uint16_t valueXTen = valueXTenAndUnit - (valueXTenAndUnit % 10);
        uint16_t valueXSecond = valueXTen / 10;
        uint16_t valueXThird = valueXTenAndUnit - valueXTen;
        uint16_t valueYHundred = valueY - (valueY % 100);
        uint16_t valueYFirst = valueYHundred / 100;
        uint16_t valueYTenAndUnit = valueY - valueYHundred;
        uint16_t valueYTen = valueYTenAndUnit - (valueYTenAndUnit % 10);
        uint16_t valueYSecond = valueYTen / 10;
        uint16_t valueYThird = valueYTenAndUnit - valueYTen;        
        pillarsCoordonateSVG[indexPillarsCoordonateSVG++] = '0' + valueXFirst;
        pillarsCoordonateSVG[indexPillarsCoordonateSVG++] = '0' + valueXSecond;
        pillarsCoordonateSVG[indexPillarsCoordonateSVG++] = '0' + valueXThird;
        pillarsCoordonateSVG[indexPillarsCoordonateSVG++] = '0' + valueYFirst;
        pillarsCoordonateSVG[indexPillarsCoordonateSVG++] = '0' + valueYSecond;
        pillarsCoordonateSVG[indexPillarsCoordonateSVG++] = '0' + valueYThird;
    }
    
    
    for (uint8_t i = 0; i < sizeof(pillarsCoordonateSVG); i = i + 6)
    {
        for (uint8_t j = 0; j < strlen(startPillarSVG); j++)
        {
            rs232.USART_Transmit(startPillarSVG[j]);
        }
        calculateCRC((uint8_t*)startPillarSVG, strlen(startPillarSVG));
        rs232.USART_Transmit(pillarsCoordonateSVG[i]);
        rs232.USART_Transmit(pillarsCoordonateSVG[i+1]);
        rs232.USART_Transmit(pillarsCoordonateSVG[i+2]);
        calculateCRC((uint8_t*)(pillarsCoordonateSVG+i), 3);
        for (uint8_t j = 0; j < strlen(midPillarSVG); j++)
        {   rs232.USART_Transmit(midPillarSVG[j]);
        }
        calculateCRC((uint8_t*)midPillarSVG, strlen(midPillarSVG));
        rs232.USART_Transmit(pillarsCoordonateSVG[i+3]);
        rs232.USART_Transmit(pillarsCoordonateSVG[i+4]);
        rs232.USART_Transmit(pillarsCoordonateSVG[i+5]);
        calculateCRC((uint8_t*)(pillarsCoordonateSVG+i+3), 3);
        for (uint8_t j = 0; j < strlen(endPillarSVG); j++)
        {   rs232.USART_Transmit(endPillarSVG[j]);
        }
        calculateCRC((uint8_t*)endPillarSVG, strlen(endPillarSVG));
    }

    char headerTextSVG[] = "<text x=\"96\" y=\"36\" font-family=\"arial\" font-size=\"20\" fill=\"blue\">INF1900 - Section 05 - 121135 - Xenith</text>\n\t";
    
    for (uint8_t i = 0; i < strlen(headerTextSVG); i++)
    {
        rs232.USART_Transmit(headerTextSVG[i]);
    }
    calculateCRC((uint8_t*)headerTextSVG, strlen(headerTextSVG));
    char startAreaTextSVG[] = "<text x=\"96\" y=\"550\" font-family=\"arial\" font-size=\"20\" fill=\"blue\">AIRE: ";
    for (uint8_t i = 0; i < strlen(startAreaTextSVG); i++)
    {   
        rs232.USART_Transmit(startAreaTextSVG[i]);
    }
    calculateCRC((uint8_t*)startAreaTextSVG, strlen(startAreaTextSVG));
    char endAreaTextSVG[] = " pouces carres</text>\n</svg>";
    
    uint16_t valueArea = calculateArea(points);
    char valueAreaSVG [4];
    uint16_t valueAreaThousand = valueArea - (valueArea % 1000);
    uint16_t valueAreaFirst = valueAreaThousand / 1000;
    uint16_t valueAreaHundred = (valueArea - valueAreaThousand) - (valueArea % 100);
    uint16_t valueAreaSecond = valueAreaHundred / 100;
    uint16_t valueAreaTenAndUnit = valueArea - valueAreaHundred - valueAreaThousand;
    uint16_t valueAreaTen = valueAreaTenAndUnit - (valueAreaTenAndUnit % 10);
    uint16_t valueAreaThird = valueAreaTen / 10;
    uint16_t valueAreaForth = valueAreaTenAndUnit - valueAreaTen;
    valueAreaSVG[0] = '0' + valueAreaFirst;
    valueAreaSVG[1] = '0' + valueAreaSecond;
    valueAreaSVG[2] = '0' + valueAreaThird;
    valueAreaSVG[3] = '0' + valueAreaForth;
    for(uint8_t i = 0; i < sizeof(valueAreaSVG); i++)
    {
        rs232.USART_Transmit(valueAreaSVG[i]);
    }
    calculateCRC((uint8_t*)valueAreaSVG, sizeof(valueAreaSVG));
    for(uint8_t i = 0; i < strlen(endAreaTextSVG); i++)
    {
        rs232.USART_Transmit(endAreaTextSVG[i]);
    }
    calculateCRC((uint8_t*)endAreaTextSVG, strlen(endAreaTextSVG));
    
}
