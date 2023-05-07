// @file
// @details Definition of extended LCD class
// @copyright BlackCultist 2023

#ifndef LCDEXTENDED_H
#define LCDEXTENDED_H

#include <LiquidCrystal_I2C.h>

class LcdExtended : private LiquidCrystal_I2C
{
public:
    // @brief Constructor
    // @param[in] lcd_Addr I2C address of LCD
    // @param[in] lcd_cols amount of cols
    // @param[in] lcd_rows amount of rows
    LcdExtended( uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows );

    // @brief Initialized display on bright backlight
    void Init();

    // @brief Runs reset
    void Reset();

    // @brief Runs Welcome
    void Welcome();

    // @brief Starts display with values draw
    void Start( uint16_t trip, uint16_t odo );

    // @brief Enables backlight
    void Bright();

    // @brief Disables backlight
    void Dimm();
    
    // @brief Updates onscreen velocity value
    // @param[in] velocity velocity value (0-999)
    void UpdateVelocity( uint8_t velocity );

    // @brief Updates onscreen heartrate value
    // @param[in] heartrate heartrate value (0-999)
    void UpdateHeartrate( uint8_t heartrate );

    // @brief Updates onscreen cadence value
    // @param[in] cadence cadence value (0-999)
    void UpdateCadence( uint16_t cadence );

    // @brief Updates onscreen trip value
    // @param[in] trip trip value (0-999)
    void UpdateTrip( uint16_t trip );

    // @brief Updates onscreen odo value
    // @param[in] odo odo value (0-999)
    void UpdateODO( uint16_t odo );

private:
    // @brief draws init screen
    void drawInit();

    // @brief draws reset screen
    void drawReset();

    // @brief draws basic interface
    void drawBase();

    // @brief draws number with size control (0-999)
    void drawControlledNumber( uint16_t number, uint8_t basicCol, uint8_t row );
};

#endif // end file guardian