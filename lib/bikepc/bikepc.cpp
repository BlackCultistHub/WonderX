// @file
// @details Declaration of general bikepc class
// @copyright BlackCultist 2023

#include "bikepc.h"

namespace
{
    template< typename T >
    void AddToBuffer( T* buffer, uint16_t size, T newValue )
    {
        if ( AVERAGING_BUFFER_SIZE == 1 )
        {
            buffer[0] = newValue; 
            return;
        }

        for ( int i = 0; i < AVERAGING_BUFFER_SIZE-1; i++ )
        {
            buffer[i] = buffer[i+1];
        }

        buffer[AVERAGING_BUFFER_SIZE-1] = newValue;
        return;
    }

    template< typename T >
    uint32_t GetBufferSummNonZero( T* buffer, uint16_t size )
    {
        uint32_t summary = 0;
        uint16_t elems = 0;
        for ( int i = 0; i < AVERAGING_BUFFER_SIZE; i++ )
        {
            if ( buffer[i] )
            {
                summary += buffer[i];
                elems++;
            }
        }
        return (summary / (!elems?1:elems));
    }

    template< typename T >
    void WipeBuffer( T* buffer, uint16_t size )
    {
        for ( int i = 0; i < AVERAGING_BUFFER_SIZE; i++ )
        {
            buffer[i] = 0;
        }
        return;
    }
}

BikePc::BikePc( uint8_t lcdAddress, uint8_t lcdCols, uint8_t lcdRows, uint16_t wheelRad ):
lcd( lcdAddress, lcdCols, lcdRows ),
wheelRadius( wheelRad )
{
    WipeBuffer( velocityBuffer, AVERAGING_BUFFER_SIZE );
    WipeBuffer( cadenceBuffer, AVERAGING_BUFFER_SIZE );
    WipeBuffer( heartrateBuffer, AVERAGING_BUFFER_SIZE );
}

void BikePc::Init( bool resetOnStart )
{
    lcd.Init();
    if ( resetOnStart )
    {
        HardReset();
    }
    else
    {
        lcd.Welcome();
        delay( 2000 );
        // Read Trip
        trip = eeprom_ops::GetTrip();

        // Read ODO
        odo = eeprom_ops::GetOdo();

        // Start lcd
        lcd.Start( (uint16_t)algorithms::ConvertCmToKm( trip ), (uint16_t)algorithms::ConvertCmToKm( odo ) );
    }
}

int BikePc::HardReset()
{
    // @todo error handling
    lcd.Reset();
    eeprom_flashing::WipeEEPROM();
    delay( 1000 );
    lcd.Start( 0, 0 );
    return 0;
}

int BikePc::ResetTrip()
{
    // @todo error handling
    eeprom_ops::ClearTrip();
    delay( 25 );
    lcd.UpdateTrip( 0 );
    return 0;
}

int BikePc::UpdateSpeed( algorithms::SimpleDoubleTimer speedTimer )
{
    // @todo error handling
    uint16_t velocity = round( algorithms::GetCircleLinearSpeedKmh( speedTimer.GetDiff(), algorithms::ConvertMmToM( wheelRadius ) ) );
    if ( velocity < 0 )
    {
        lcd.UpdateVelocity( 0 );
    }
    else
    {
        lcd.UpdateVelocity( getVelocity( velocity ) );
        updateTripOdo();
    }
    return 0;
}

int BikePc::UpdateCadence( algorithms::SimpleDoubleTimer cadenceTimer )
{
    // @todo error handling
    uint16_t cadenceRpm = algorithms::GetCircleRpm( cadenceTimer.GetDiff() );
    if ( cadenceRpm < 0 )
    {
        lcd.UpdateCadence( 0 );
    }
    else
    {
        lcd.UpdateCadence( getCadence( cadenceRpm ) );
    }
    return 0;
}

int BikePc::UpdateHeartrate( uint8_t heartrate )
{
    // @todo error handling
    if ( heartrate < 0 )
    {
        lcd.UpdateHeartrate( 0 );
    }
    else
    {
        lcd.UpdateHeartrate( getHeartrate( heartrate ) );
    }
    return 0;
}

void BikePc::TimeOutBike()
{
    WipeBuffer( velocityBuffer, AVERAGING_BUFFER_SIZE );
    lcd.UpdateVelocity( 0 );

    WipeBuffer( cadenceBuffer, AVERAGING_BUFFER_SIZE );
    lcd.UpdateCadence( 0 );
}

int BikePc::updateTripOdo()
{
    // @todo error handling
    rideBuffer += 2*PI*wheelRadius; // + distance of wheel in mm
    if ( rideBuffer >= 10 )
    {
        trip += algorithms::ConvertMmToCm( rideBuffer );
        lcd.UpdateTrip( (uint16_t)algorithms::ConvertCmToKm( trip ) );

        // update odo
        odo += algorithms::ConvertMmToCm( rideBuffer );
        lcd.UpdateODO( (uint16_t)algorithms::ConvertCmToKm( odo ) );

        eeprom_ops::WriteTripOdo( trip, odo );
        rideBuffer = rideBuffer - algorithms::ConvertMmToCm( algorithms::ConvertCmToMm( rideBuffer ) ); // calculate what's left
    }
    return 0;
}

uint16_t BikePc::getVelocity( uint16_t newVelocity )
{
    AddToBuffer( velocityBuffer, AVERAGING_BUFFER_SIZE, newVelocity );
    return GetBufferSummNonZero( velocityBuffer, AVERAGING_BUFFER_SIZE );
}

uint16_t BikePc::getCadence( uint16_t newCadence )
{
    AddToBuffer( cadenceBuffer, AVERAGING_BUFFER_SIZE, newCadence );
    return GetBufferSummNonZero( cadenceBuffer, AVERAGING_BUFFER_SIZE );
}

uint8_t BikePc::getHeartrate( uint8_t newHeartrate )
{
    AddToBuffer( heartrateBuffer, AVERAGING_BUFFER_SIZE, newHeartrate );
    return GetBufferSummNonZero( heartrateBuffer, AVERAGING_BUFFER_SIZE );
}