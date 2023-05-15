// @file
// @details Declaration of setup class
// @copyright BlackCultist 2023

#include "setup.h"

SetupControl::SetupControl( uint16_t minLimit, uint16_t maxLimit, uint16_t increment, uint16_t defaultRad ):
minLimit_( minLimit ),
maxLimit_( maxLimit ),
increment_( increment ),
currentWheel_( defaultRad )
{}

uint16_t SetupControl::GetCurrent()
{
    return currentWheel_;
}

uint16_t SetupControl::StepUp()
{
    if (currentWheel_ + increment_ > maxLimit_)
    {
        if ( currentWheel_ == maxLimit_ )
        {
            currentWheel_ = minLimit_;
        }
        else
        {
            currentWheel_ = maxLimit_;
        }
    }
    else
    {
        currentWheel_ += increment_;
    }
    return currentWheel_;
}