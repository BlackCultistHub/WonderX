// @file
// @details Definition of simple double timer class
// @copyright BlackCultist 2023

#ifndef SIMPLEDOUBLETIMER_H
#define SIMPLEDOUBLETIMER_H

#include <Arduino.h>

namespace algorithms
{

class SimpleDoubleTimer
{
public:
    // @brief Default constructor, timer1=0 timer2=max
    SimpleDoubleTimer();

    // @brief Constructor
    // @param[in] zeroBoth if true both timers init with 0
    SimpleDoubleTimer( bool zeroBoth );

    // @brief Resets timer1 and timer 2
    void Reset();

    // @brief updates timer and cycles timers 1 and 2
    void Update();

    // @brief Gets diff of timers
    // @return timer2 - timer1
    unsigned long GetDiff();

private:
    bool zeroTimers;
    unsigned long time1;
    unsigned long time2;
};

}

#endif // end file guardian