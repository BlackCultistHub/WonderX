// @file
// @details Definition of basic algorithm functions
// @copyright BlackCultist 2023

#ifndef ALGO_H
#define ALGO_H

namespace algorithms
{

// @brief Returns RPM based on the time of previous and current triggering. SINGLE trigger point.
// @param[in] timePrevious time of previous trigger in millis
// @param[in] timeNow time of current trigger in millis
// @return RPM of circle
int GetCircleRpm( unsigned long timePrevious, unsigned long timeNow );

// @brief Returns RPM based on the time of previous and current triggering. SINGLE trigger point.
// @param[in] timeOfRound time of single round
// @return RPM of circle
int GetCircleRpm( unsigned long timeOfRound );

// @brief Returns RPS based on the time of previous and current triggering. SINGLE trigger point.
// @param[in] timePrevious time of previous trigger in millis
// @param[in] timeNow time of current trigger in millis
// @return RPS of circle
double GetCircleRps( unsigned long timePrevious, unsigned long timeNow );

// @brief Returns RPS based on the time of previous and current triggering. SINGLE trigger point.
// @param[in] timeOfRound time of single round in millis
// @return RPS of circle
double GetCircleRps( unsigned long timeOfRound );

// @brief Returns linear speed of circle based on it's RPS. SINGLE trigger point.
// @param[in] rps RPS of circle
// @param[in] radius radius of circle in meters
// @return linear speed of circle in m/s
double GetCircleLinearSpeed( double rps, float radius );

// @brief Returns linear speed of circle based on it's RPS. SINGLE trigger point.
// @param[in] rps RPS of circle
// @param[in] radius radius of circle in meters
// @return linear speed of circle in km/h
double GetCircleLinearSpeedKmh( double rps, float radius );

// @brief Returns linear speed of circle based on it's time of round. SINGLE trigger point.
// @param[in] timeOfRound time of single round in millis
// @param[in] radius radius of circle in meters
// @return linear speed of circle in km/h
double GetCircleLinearSpeedKmh( unsigned long timeOfRound, float radius );

}

#endif // end file guardian