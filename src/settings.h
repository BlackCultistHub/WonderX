// @file
// @details Settings
// @copyright BlackCultist 2023

#ifndef SETTINGS_H
#define SETTINGS_H

// ========== RESPONSIVENESS ==========

// values update time interval
#define UPDATE_TIME_MS 1000

// trip resets after control button pressed more then this value
#define TRIP_RESET_TIME_MS 5000

// time interval before values on screen are reset
#define TIMEOUT_TIME_MS 10000

// time after which setup value is confirmed
#define SETUP_HOLD_TIME 5000

// time after which setup value is confirmed
#define SETUP_END_WAIT_TIME 1500

// ========== LCD ==========

// LCD I2C Address
#define LCD_ADDR 0x27

// LCD Cols
#define LCD_COLS 16

// LCD Rows
#define LCD_ROWS 2

// ========== SETUP ==========

// Minimal value of wheel setup, mm
#define SETUP_WHEEL_MIN 150

// Maximum value of wheel setup, mm
#define SETUP_WHEEL_MAX 380

// Step value of wheel setup, mm
#define SETUP_WHEEL_STEP 10

// Default starting value of radius
#define SETUP_WHEEL_RADIUS_DEFAULT 300

// ========== POWER ==========

#define SCREEN_POWEROFF_TIMEOUT_MIN 3

#endif // end file guardian