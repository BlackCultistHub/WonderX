// @file
// @details Declaration of simple double timer class
// @copyright BlackCultist 2023

#include "simpleDoubleTimer.h"

namespace algorithms
{

SimpleDoubleTimer::SimpleDoubleTimer()
{
    zeroTimers = false;
    Reset();
}

SimpleDoubleTimer::SimpleDoubleTimer( bool zeroBoth ):
zeroTimers( zeroBoth )
{
    Reset();
}

void SimpleDoubleTimer::Reset()
{
    time1 = 0;
    time2 = zeroTimers?0:__UINT64_MAX__;
}

void SimpleDoubleTimer::Update()
{
    time1 = time2;
    time2 = millis();
}

unsigned long SimpleDoubleTimer::GetDiff()
{
    return time2 - time1;
}


};