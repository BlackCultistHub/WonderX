// @file
// @details Declaration of general bikepc class
// @copyright BlackCultist 2023

#include "bikepc.h"

BikePc::BikePc( uint8_t lcdAddress, uint8_t lcdCols, uint8_t lcdRows, uint16_t wheelRad):
lcd( lcdAddress, lcdCols, lcdRows ),
wheelRadius( wheelRad )
{
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
    uint8_t velocity = round( algorithms::GetCircleLinearSpeedKmh( speedTimer.GetDiff(), algorithms::ConvertMmToM( wheelRadius ) ) );
    if ( velocity < 0 )
    {
        lcd.UpdateVelocity( 0 );
    }
    else
    {
        lcd.UpdateVelocity( velocity );
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
        lcd.UpdateCadence( cadenceRpm );
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
        lcd.UpdateHeartrate( heartrate );
    }
    return 0;
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