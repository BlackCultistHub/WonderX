// @file
// @details Declaration of basic size conversion algorithm functions
// @copyright BlackCultist 2023

#include "size_conversions.h"

namespace algorithms
{

uint32_t ConvertCmToKm( uint32_t centimeters )
{
    return ( centimeters / 100000 );
}

uint32_t ConvertMmToCm( uint32_t millimeters )
{
    return ( millimeters / 10 );
}

uint32_t ConvertCmToMm( uint32_t centimeters )
{
    return ( centimeters * 10 );
}

float ConvertMmToM( uint32_t millimeters )
{
    return ( (float)millimeters / (float)1000 );
}

}