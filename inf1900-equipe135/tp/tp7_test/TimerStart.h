
#include <avr/io.h> 
//#define F_CPU 8000000

class Timer
{
public:
    Timer();
    ~Timer();
    void timerStartCTC(uint16_t duration);
    void timerStartPWM(uint8_t threshold);
protected:
private:
};
