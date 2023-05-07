// @file
// @details Declaration of basic algorithm functions
// @copyright BlackCultist 2023

#include "algo.h"
#include <math.h>

namespace algorithms
{

int GetCircleRpm( unsigned long timePrevious, unsigned long timeNow )
{
    return ( round( GetCircleRps( timePrevious, timeNow ) * (double)60 ) );
}

int GetCircleRpm( unsigned long timeOfRound )
{
    return ( round( GetCircleRps( timeOfRound ) * (double)60 ) );
}

double GetCircleRps( unsigned long timePrevious, unsigned long timeNow )
{
    unsigned long timeDiff = timeNow - timePrevious;
    return ( (double)( 1 ) / (double)( (double)timeDiff / (double)1000 ) );
}

double GetCircleRps( unsigned long timeOfRound )
{
    return ( (double)( 1 ) / (double)( (double)timeOfRound / (double)1000 ) );
}

double GetCircleLinearSpeed( double rps, float radius )
{
    double angularSpeed = rps * (double)2 * M_PI; // 2*PI*RPS
    return ( angularSpeed * radius );
}

double GetCircleLinearSpeedKmh( double rps, float radius )
{
    double linearSpeed = GetCircleLinearSpeed( rps, radius );
    return ( linearSpeed * (double)3.6 );
}

double GetCircleLinearSpeedKmh( unsigned long timeOfRound, float radius )
{
    double linearSpeed = GetCircleLinearSpeed( GetCircleRps( timeOfRound ), radius );
    return ( linearSpeed * (double)3.6 );
}

}