#include <avr/io.h>
#include "capteur.h"
#include <util/delay.h>

#define TIMER_100_MS 871
#define TIMER_250_MS 0x7a1

#define OBJECT_DETECTED_THRESHOLD 0x0060
#define OBJECT_FOUND_THRESHOLD 0x0180
#define ONE_SQUARE_THRESHOLD 0xB1

#define TIME_MS_FOR_COMPLETE_TURN 62
#define DEGREES_PER_SECOND 5.8
#define SCALE 11

#define DELAY_30_MS 30
#define DELAY_100_MS 100
#define DELAY_150_MS 150
#define DELAY_250_MS 250
#define DELAY_300_MS 300
#define DELAY_500_MS 500
#define DELAY_700_MS 700
#define DELAY_2_S 2000

#define RESCAN_SPEED 0x90
#define TURN_SPEED 0x70
#define WHEEL_BOOST 0xff
#define CRUISING_SPEED 0x8f
#define STOP 0

#define SON_AIGU 0x26
#define SON_GRAVE 0x8e

ListPoint Capteur::getList()
{
    return list;
}

void Capteur::determineDistance(uint16_t puissance)
{
    if (puissance >= ONE_SQUARE_THRESHOLD)
        distance = 11;
    else
        distance = 22;

    if (angle % 90 != 0)
        distance = distance * sqrt(2);
}

void Capteur::determineAngle(char initialPosition, uint8_t counter)
{
    if (initialPosition == 'r')
        angle = 90;

    if (initialPosition == 'h')
        angle = 0;

    angle += DEGREES_PER_SECOND * counter;

    if (angle > 315 && initialPosition != 'r')
        angle = 315;

    else if (initialPosition == 'r' && angle > 405 && angle < 449)
        angle = 45;

    // Round the angle to the nearest multiple of 45
    angle = round(angle / 45.0) * 45;

    // If the angle is 360, set it back to 0
    if (angle == 360)
    {
        angle = 0;
    }
}

void Capteur::determinePosition()
{
    double angleRadians = angle * M_PI / 180.0;

    int8_t x = round((distance / SCALE) * sin(angleRadians));
    int8_t y = round((distance / SCALE) * cos(angleRadians));

    list.addRelativePointAndPosition(x, y);
}

void Capteur::start(char position)
{
    timer.timerStartCTC(TIMER_100_MS);

    while (true)
    {
        switch (state)
        {
        case State::STANDBY:
            position = 'h';
            objectDetected = false;
            amberOn = true;
            amberCondition = true;

            timer.timerEnd();
            timer.timerStartCTC(TIMER_250_MS);

            while (gInterruptButton == false)
            {
                while (amberOn && gInterruptButton == false)
                {
                    led.turnAmber();
                }
                led.turnOff();
            }

            amberCondition = false;
            timer.timerStartCTC(TIMER_100_MS);
            led.turnOff();
            gInterruptButton = false;
            capteur_counter = 0;

            state = State::SCAN;
            break;

        case State::SCAN:
            motor.motorForward(WHEEL_BOOST, WHEEL_BOOST);
            _delay_ms(DELAY_100_MS);

            motor.motorForward(TURN_SPEED, STOP);

            while (!objectDetected)
            {
                _delay_ms(DELAY_30_MS);
                puissance = CAN.lecture(PA6);

                if (puissance > OBJECT_DETECTED_THRESHOLD)
                {
                    objectDetected = true;
                    state = State::OBJECT_DETECTED;
                }
                if (capteur_counter > TIME_MS_FOR_COMPLETE_TURN)
                {
                    state = State::END;
                    break;
                }
            }

            determineAngle(position, capteur_counter);
            break;

        case State::OBJECT_DETECTED:

            motor.motorForward(STOP, STOP);
            _delay_ms(DELAY_100_MS);

            state = State::REGISTER_OBJECT;
            break;

        case State::REGISTER_OBJECT:

            determineDistance(puissance);
            determinePosition();
            getList().writeListToMemory();

            state = State::FIND_OBJECT;
            break;

        case State::FIND_OBJECT:
            motor.motorForward(WHEEL_BOOST, WHEEL_BOOST);
            _delay_ms(DELAY_100_MS);

            while (puissance < OBJECT_FOUND_THRESHOLD)
            {
                motor.motorForward(CRUISING_SPEED, CRUISING_SPEED);
                if (puissance < OBJECT_DETECTED_THRESHOLD)
                {
                    motor.motorForward(STOP, STOP);
                    _delay_ms(DELAY_500_MS);

                    motor.motorForward(STOP, 0x8f);
                    _delay_ms(DELAY_700_MS);

                    while (puissance < OBJECT_DETECTED_THRESHOLD)
                    {
                        motor.turnRight(RESCAN_SPEED, RESCAN_SPEED);
                        _delay_ms(DELAY_150_MS);

                        motor.motorForward(STOP, STOP);
                        _delay_ms(DELAY_250_MS);

                        puissance = CAN.lecture(PA6);
                    }
                    motor.turnRight(RESCAN_SPEED, RESCAN_SPEED);
                    _delay_ms(DELAY_150_MS);

                    motor.motorForward(STOP, STOP);
                    _delay_ms(DELAY_250_MS);
                }
                else
                {
                    puissance = CAN.lecture(PA6);
                    _delay_ms(DELAY_30_MS);
                }
            }

            motor.motorForward(STOP, STOP);
            timer.timerEnd();

            for (int i = 0; i < 3; i++)
            {
                timer.timerStartPwmAdjustTop256(SON_AIGU / 2, SON_AIGU / 4);
                _delay_ms(DELAY_300_MS);

                timer.timerEnd();
                _delay_ms(DELAY_300_MS);
            }
            state = State::STANDBY;
            break;

        case State::END:
            motor.motorForward(STOP, STOP);

            timer.timerEnd();
            timer.timerStartPwmAdjustTop256(SON_GRAVE, SON_GRAVE / 2);
            _delay_ms(DELAY_2_S);
            timer.timerEnd();
            return;
        }
    }
}
