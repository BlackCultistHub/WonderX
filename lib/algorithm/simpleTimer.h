// @file
// @details Definition of simple timer class
// @copyright BlackCultist 2023

#ifndef SIMPLETIMER_H
#define SIMPLETIMER_H

#include <Arduino.h>

namespace algorithms
{

class SimpleTimer
{
public:
    // @brief Default constructor, timer1=0 timer2=max
    SimpleTimer();

    // @brief Resets timer
    void Reset();

    // @brief updates timer
    void Update();

    // @brief Gets diff of timer and current time
    // @return current - timer
    unsigned long GetDiff();

private:
    unsigned long time;
};

}

#endif // end file guardian