// @file
// @details main functions
// @copyright BlackCultist 2023

#include <Arduino.h>

#include <bikepc.h>
#include <heartrate.h>
#include <simpleTimer.h>

#include <pinout.h>
#include <settings.h>

#include <setup.h>
#include <power.h>

// === Globals ===
// @brief speed timer
algorithms::SimpleDoubleTimer spdTmr;
// @brief cadence timer
algorithms::SimpleDoubleTimer cadTmr;
// @brief update timer
algorithms::SimpleTimer timeoutTmr;
// @brief trip reset timer
algorithms::SimpleTimer tripTmr;
// @brief screen sleep timer
algorithms::SimpleTimer screenTmr;

// @brief control pin flag
bool controlPinPressedBefore = false;

// ISR triggers
volatile bool updateSpeed = false;
volatile bool updateCadence = false;
bool updateHeartrate = false;
// control object
BikePc bpc( LCD_ADDR, LCD_COLS, LCD_ROWS, SETUP_WHEEL_RADIUS_DEFAULT );
// heartrate buffer
uint8_t heartrate = 0;

// === ISRs ===
// ISR Speed
void SpeedISR()
{
  updateSpeed = true;
}
// ISR Cadence
void CadenceISR()
{
  updateCadence = true;
}

// === Main ===
void SetupMenu();

void setup() 
{
  //DEBUG
  Serial.begin(9600); //DBG

  // RESET registering
  pinMode( RESET_PIN, INPUT_PULLUP );
  bool reset = false;
  if ( digitalRead( RESET_PIN ) == LOW )
  {
    reset = true;
  }

  // Control pin init
  pinMode( CONTROL_PIN, INPUT_PULLUP );
  bool wheelSetup = false;
  if ( digitalRead( CONTROL_PIN ) == LOW )
  {
    wheelSetup = true;
  }

  // init main controlling object
  bpc.Init( reset, wheelSetup );

  if ( !reset && wheelSetup )
  {
    SetupMenu();
  }

  // Speed ISR
  pinMode( SPEED_PIN, INPUT_PULLUP );
  attachInterrupt( digitalPinToInterrupt( SPEED_PIN ), SpeedISR, FALLING );

  // Cadence ISR
  pinMode( CADENCE_PIN, INPUT_PULLUP );
  attachInterrupt( digitalPinToInterrupt( CADENCE_PIN ), CadenceISR, FALLING );

  Serial.println("setup done"); //DBG

}

void loop() 
{
  { // control button processing
    if ( digitalRead( CONTROL_PIN ) == LOW && !controlPinPressedBefore )
    {
      controlPinPressedBefore = true;
      tripTmr.Update();
    }
    else if ( digitalRead( CONTROL_PIN ) == HIGH && controlPinPressedBefore )
    {
      controlPinPressedBefore = false;
      tripTmr.Reset();
    }
  }
  { // trip reset
    if ( tripTmr.GetDiff() >= TRIP_RESET_TIME_MS && controlPinPressedBefore )
    {
      bpc.ResetTrip();
      tripTmr.Reset();
    }
  }
  { // Timeout speed && cad
    if ( timeoutTmr.GetDiff() >= TIMEOUT_TIME_MS )
    {
      timeoutTmr.Update();
      bpc.TimeOutBike();
    }
  }
  { // Timeout screen
    if ( screenTmr.GetDiff() >= SCREEN_POWEROFF_TIMEOUT_MIN * 60 * 1000 )
    {
      screenTmr.Update();
      bpc.LightPowerSave();
    }
  }
  { // RF Heartrate
    // recieve && read signature
    // sign = OK -> updateHeartrate = true
  }
  if ( updateSpeed )
  {
    delay( 100 );
    updateSpeed = false;
    bpc.UpdateSpeed( spdTmr );
    spdTmr.Update();
    timeoutTmr.Update();

    // power saving
    screenTmr.Update();
    bpc.QuitPowerSave();
  }
  if ( updateCadence )
  {
    delay( 100 );
    updateCadence = false;
    bpc.UpdateCadence( cadTmr );
    cadTmr.Update();
    timeoutTmr.Update();

    // power saving
    screenTmr.Update();
    bpc.QuitPowerSave();
  }
  if ( updateHeartrate )
  {
    delay( 100 );
    updateHeartrate = false;
    //bpc.UpdateHeartrate( heartrate );
  }
}

void SetupMenu()
{
  algorithms::SimpleTimer holdButtonTmr;
  SetupControl stpCtrl( SETUP_WHEEL_MIN, SETUP_WHEEL_MAX, SETUP_WHEEL_STEP, SETUP_WHEEL_RADIUS_DEFAULT );
  uint16_t currentRadius = SETUP_WHEEL_RADIUS_DEFAULT;
  // menu body
  while ( true )
  {
    if ( digitalRead( CONTROL_PIN ) == LOW && !controlPinPressedBefore )
    {
      controlPinPressedBefore = true;
      holdButtonTmr.Update();
    }
    else if ( digitalRead( CONTROL_PIN ) == HIGH && controlPinPressedBefore )
    {
      controlPinPressedBefore = false;

      if ( holdButtonTmr.GetDiff() <= SETUP_HOLD_TIME )
      {
        currentRadius = stpCtrl.StepUp();
        bpc.UpdateWheel( &currentRadius, false );
      }

      holdButtonTmr.Reset();
    }
    if ( holdButtonTmr.GetDiff() > SETUP_HOLD_TIME && controlPinPressedBefore )
    {
      bpc.UpdateWheel( &currentRadius, true );
      delay( 250 ); // delay for waiting EEPROM write
      bpc.EndSetup();
      delay( SETUP_END_WAIT_TIME );
      pwr::resetFunc();
    }
  }
}