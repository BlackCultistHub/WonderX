// @file
// @details Definition of setup class
// @copyright BlackCultist 2023

#ifndef SETUP_H
#define SETUP_H

#include <inttypes.h>

#include "defaults.h"

class SetupControl
{
public:
    SetupControl( uint16_t minLimit, uint16_t maxLimit, uint16_t increment, uint16_t defaultRad );

    uint16_t GetCurrent();

    uint16_t StepUp();
private:
    uint16_t minLimit_; //mm
    uint16_t maxLimit_; //mm
    uint16_t increment_; //mm
    uint16_t currentWheel_; //mm
};

#endif // end file guardian