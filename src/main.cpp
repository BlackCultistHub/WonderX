// @file
// @details main functions
// @copyright BlackCultist 2023

#include <Arduino.h>

#include <bikepc.h>
#include <heartrate.h>
#include <simpleTimer.h>

#include <pinout.h>
#include <settings.h>

// === Globals ===
// @brief speed timer
algorithms::SimpleDoubleTimer spdTmr;
// @brief cadence timer
algorithms::SimpleDoubleTimer cadTmr;
// @brief update timer
algorithms::SimpleTimer timeoutTmr;
// ISR triggers
volatile bool updateSpeed = false;
volatile bool updateCadence = false;
bool updateHeartrate = false;
// control object
BikePc bpc(LCD_ADDR, LCD_COLS, LCD_ROWS, 250); // CHANGE WHEEL RADIUS ========= TEMPORARY
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
void setup() 
{
  //DEBUG
  Serial.begin(9600); //DBG

  pinMode(RESET_PIN, INPUT_PULLUP);
  bool reset = false;
  if ( digitalRead(RESET_PIN) == LOW )
  {
    reset = true;
  }

  // init main controlling object
  bpc.Init( reset );

  // Speed ISR
  pinMode(SPEED_PIN, INPUT_PULLUP);
  attachInterrupt( digitalPinToInterrupt(SPEED_PIN), SpeedISR, FALLING );

  // Cadence ISR
  pinMode(CADENCE_PIN, INPUT_PULLUP);
  attachInterrupt( digitalPinToInterrupt(CADENCE_PIN), CadenceISR, FALLING );

  Serial.println("setup done"); //DBG
}

void loop() 
{
  {
    if ( timeoutTmr.GetDiff() >= TIMEOUT_TIME_MS )
    {
      timeoutTmr.Update();
      bpc.TimeOutBike();
    }
  }
  {
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
  }
  if ( updateCadence )
  {
    delay( 100 );
    updateCadence = false;
    bpc.UpdateCadence( cadTmr );
    cadTmr.Update();
    timeoutTmr.Update();
  }
  if ( updateHeartrate )
  {
    delay( 100 );
    updateHeartrate = false;
    //bpc.UpdateHeartrate( heartrate );
  }
}