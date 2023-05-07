// @file
// @details Declaration of EEPROM manipulations
// @copyright BlackCultist 2023

#include "eeprom_memory.h"

namespace eeprom_flashing
{

int WipeEEPROM()
{
    // @todo error handling
    for (size_t i = 0; i < EEPROM.length(); i++)
    {
        // using update to not to wear EEPROM too much
        EEPROM.update(i, 0);
    }
    return 0;
}

}

namespace eeprom_ops
{

// @todo CRC for values

int WriteTripOdo( uint32_t trip, uint32_t odo )
{
    // @todo error handling
    EEPROM.put( 0, trip );
    EEPROM.put( 48, odo );
    return 0;
}

int ClearTrip()
{
    // @todo error handling
    for (size_t i = 0; i < 32; i++)
    {
        // using update to not to wear EEPROM too much
        EEPROM.update(i, 0);
    }
    return 0;
}

uint32_t GetTrip()
{
    // @todo error handling
    uint32_t trip = 0;
    EEPROM.get(0, trip);
    return trip;
}

uint32_t GetOdo()
{
    // @todo error handling
    uint32_t odo = 0;
    EEPROM.get(48, odo);
    return odo;
}

int WriteWheelRad( uint16_t wheelRadius )
{
    // @todo error handling
    EEPROM.put( 88, wheelRadius );
    return 0;
}

uint16_t GetWheelRadius()
{
    // @todo error handling
    uint16_t wheelrad = 0;
    EEPROM.get( 88, wheelrad );
    return wheelrad;
}

}