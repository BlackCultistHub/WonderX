// @file
// @details Declaration of simple timer class
// @copyright BlackCultist 2023

#include "simpleTimer.h"

namespace algorithms
{

SimpleTimer::SimpleTimer()
{
    Reset();
}

void SimpleTimer::Reset()
{
    time = 0;
}

void SimpleTimer::Update()
{
    time = millis();
}

unsigned long SimpleTimer::GetDiff()
{
    return millis() - time;
}


};