#include "can.h"
#include "motor.h"
#include "timer.h"
#include "led.h"
#include "ListPoint.h"
extern volatile uint8_t capteur_counter;
extern volatile bool gInterruptButton;
extern volatile bool amberOn;
extern volatile bool amberCondition;
enum class State
{
    STANDBY,
    SCAN,
    OBJECT_DETECTED,
    REGISTER_OBJECT,
    FIND_OBJECT,
    END
};
class Capteur
{
private:
    can CAN;
    Motor motor;
    Timer timer;
    LED led;

    uint16_t puissance;

    bool objectDetected = false;
    State state = State::SCAN;

    ListPoint list;

    void determinePosition();
    void determineAngle(char, uint8_t);
    void determineDistance(uint16_t);

public:
    uint16_t angle = 0;
    uint8_t distance = 0;
    uint8_t temporary = 0;
    Capteur(){};
    ListPoint getList();
    void start(char);
    ~Capteur(){};
};
