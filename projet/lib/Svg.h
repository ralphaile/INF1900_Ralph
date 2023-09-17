#include "ListPoint.h"

class Svg
{
public:
    Svg(){};
    ~Svg(){};
    ListPoint convexHull(ListPoint points);
    
    void constructSVG(ListPoint points, ListPoint pillars);
    //char* getStrSVG() { return strSVG_; }
    uint32_t getCRC(){ return ~crc32;}
   


private:
    uint16_t calculateArea(ListPoint points);
    void calculateCRC(uint8_t* data, uint32_t length);
    uint8_t orientation(Point p, Point q, Point r);
    uint16_t absoluteValue(int16_t value);
    //char strSVG_[2000];
    uint32_t crc32= 0xFFFFFFFF;
};
