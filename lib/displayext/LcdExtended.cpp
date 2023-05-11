// @file
// @details Declaration of extended LCD class
// @copyright BlackCultist 2023

#include "LcdExtended.h"

LcdExtended::LcdExtended( uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows ):
    LiquidCrystal_I2C( lcd_Addr, lcd_cols, lcd_rows )
{
}

void LcdExtended::Init()
{
    init();
    Bright();
}

void LcdExtended::Reset()
{
    drawReset();
}

void LcdExtended::Welcome()
{
    drawInit();
}

void LcdExtended::Start( uint16_t trip, uint16_t odo )
{
    drawBase();

    // zero all values
    UpdateVelocity( 0 );
    UpdateHeartrate( 0 );
    UpdateCadence( 0 );
    UpdateTrip( trip );
    UpdateODO( odo );
}

void LcdExtended::Bright()
{
    backlight();
}

void LcdExtended::Dimm()
{
    noBacklight();
}

void LcdExtended::UpdateVelocity( uint8_t velocity )
{
    if ( velocity > 999 )
    {
        velocity = 999;
    }
    drawControlledNumber( velocity, 1, 0 );
}

void LcdExtended::UpdateHeartrate( uint8_t heartrate )
{
    if ( heartrate > 999 )
    {
        heartrate = 999;
    }
    drawControlledNumber( heartrate, 10, 0 );
}

void LcdExtended::UpdateCadence( uint16_t cadence )
{
    if ( cadence > 999 )
    {
        cadence = 999;
    }
    drawControlledNumber( cadence, 1, 1 );
}

void LcdExtended::UpdateTrip( uint16_t trip )
{
    drawControlledNumber( trip, 7, 1 );
}

void LcdExtended::UpdateODO( uint16_t odo )
{
    drawControlledNumber( odo, 11, 1 );
}

void LcdExtended::drawInit()
{
    clear();
    // ________________ (ref)
    //      BikePC      
    //    Loading...   
    setCursor( 5, 0 );
    print("BikePC");
    setCursor( 3, 1 );
    print("Loading...");
}

void LcdExtended::drawReset()
{
    clear();
    // ________________ (ref)
    // ___Resetting____
    // __to factory..__
    setCursor( 3, 0 );
    print("Resetting");
    setCursor( 2, 1 );
    print("to factory..");
}

void LcdExtended::drawBase()
{
    clear();
    // V___kmh H___bpm
    // C___rpm __/___km // p.s. Trip/ODO
    //
    // Velocity
    setCursor( 0, 0 );
    print("V");
    setCursor( 4, 0 );
    print("kmh");

    // Heartrate
    setCursor( 9, 0 );
    print("H");
    setCursor( 13, 0 );
    print("bpm");

    // Cadence
    setCursor( 0, 1 );
    print("C");
    setCursor( 4, 1 );
    print("rpm");

    // Trip
    setCursor( 10, 1 );
    print("/");
    setCursor( 14, 1 );
    print("km");
}

void LcdExtended::drawControlledNumber( uint16_t number, uint8_t basicCol, uint8_t row )
{
    uint8_t clrPrev = 0;
    uint8_t col = basicCol;
    if ( number < 100 )
    {
        col++;
        clrPrev++;
    }
    if ( number < 10 )
    {
        col++;
        clrPrev++;
    }

    // clear spaces
    String clrString = "";
    for (int i = 0; i < clrPrev; i++)
    {
        clrString += " ";
    }
    setCursor( basicCol, row );
    print( clrString );

    setCursor( col, row );
    print( number );
}