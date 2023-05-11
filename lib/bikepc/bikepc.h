// @file
// @details Definition of general bikepc class
// @copyright BlackCultist 2023

#ifndef BIKEPC_H
#define BIKEPC_H

#include <Arduino.h>
#include <math.h>

#include <LcdExtended.h>
#include <eeprom_memory.h>
#include <algo.h>
#include <size_conversions.h>
#include <simpleDoubleTimer.h>

#define AVERAGING_BUFFER_SIZE 2

class BikePc
{

public:
    // @brief Constructor
    // @param[in] lcdAddress I2C address of LCD
    // @param[in] lcdCols amount of cols
    // @param[in] lcdRows amount of rows
    // @param[in] wheelRad radius of the wheel in mm
    BikePc( uint8_t lcdAddress, uint8_t lcdCols, uint8_t lcdRows, uint16_t wheelRad );

    // @brief Inits bikepc
    // @param[in] resetOnStart true if hard reset is needed
    void Init( bool resetOnStart = false );

    // @brief Triggers hard reset
    int HardReset();

    // @brief Triggers trip reset
    int ResetTrip();

    // @brief Updates speed with trip and odo value
    // @param[in] speedTimer speed timer object
    int UpdateSpeed( algorithms::SimpleDoubleTimer speedTimer );

    // @brief Updates cadence value
    // @param[in] cadenceTimer cadence timer object
    int UpdateCadence( algorithms::SimpleDoubleTimer cadenceTimer );

    // @brief Updates heartrate value
    // @param[in] heartrate heartrate value
    int UpdateHeartrate( uint8_t heartrate );


private:
    // @brief updates trip and odo
    int updateTripOdo();

    uint16_t getVelocity( uint16_t newVelocity );

    uint16_t getCadence( uint16_t newCadence );

    uint8_t getHeartrate( uint8_t newHeartrate );

private:
    LcdExtended lcd;

    uint16_t velocityBuffer[AVERAGING_BUFFER_SIZE];
    uint16_t cadenceBuffer[AVERAGING_BUFFER_SIZE];
    uint8_t heartrateBuffer[AVERAGING_BUFFER_SIZE];

    // @brief radius of the wheel in mm
    uint16_t wheelRadius = 0;

    uint32_t rideBuffer = 0; //buffer in mm
    uint32_t trip = 0; // cm
    uint32_t odo = 0; // cm
};


#endif // end file guardian