// @file
// @details Definition of EEPROM manipulations
// @copyright BlackCultist 2023

#ifndef EEPROM_MEMORY_H
#define EEPROM_MEMORY_H

// Target hardware:
//     MC       EEPROM-size     page-size     pages
// ATmega328P    1K bytes        4 bytes       256

// Memory map:
//   Address        Description
//    0-31             trip (32b) (in centimeters)
//    32-47            EMPTY (8b)
//    48-79            ODO (32b) (in centimeters)
//    80-87            EMPTY (8b)
//    88-103           wheel-radius (16b) (in millimeters)

#ifndef EEPROM_SIZE
#define EEPROM_SIZE 1024
#endif

#include <inttypes.h>
#include <EEPROM.h>

namespace eeprom_flashing
{

// @brief Wipes entire EEPROM. USE WITH CAUTION
// @return 0 if success
int WipeEEPROM();

}

namespace eeprom_ops
{

// @brief Writes Trip and ODO data to EEPROM 
// @return 0 if success
int WriteTripOdo( uint32_t trip, uint32_t odo );

// @brief Clears Trip in EEPROM 
// @return 0 if success
int ClearTrip();

// @brief Gets trip data
// @return trip value
uint32_t GetTrip();

// @brief Gets ODO data
// @return ODO value
uint32_t GetOdo();

// @brief Writes wheel radius data to EEPROM 
// @return 0 if success
int WriteWheelRad( uint16_t wheelRadius );

// @brief Gets wheel radius data
// @return wheel radius value
uint16_t GetWheelRadius();

}

#endif // end file guardian