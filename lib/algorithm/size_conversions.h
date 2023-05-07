// @file
// @details Definition of basic size conversion algorithm functions
// @copyright BlackCultist 2023

#ifndef SIZECONVERSIONS_H
#define SIZECONVERSIONS_H

#include <inttypes.h>

namespace algorithms
{

uint32_t ConvertCmToKm( uint32_t centimeters );

uint32_t ConvertMmToCm( uint32_t millimeters );

uint32_t ConvertCmToMm( uint32_t centimeters );

float ConvertMmToM( uint32_t millimeters );

}

#endif // end file guardian