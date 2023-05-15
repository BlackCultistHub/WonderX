// @file
// @details Declaration of heartrate RX class
// @copyright BlackCultist 2023

#include "heartrate.h"

HRSensor::HRSensor():
radio_rx() 
{}

void HRSensor::Init() 
{
    radio_rx.init();
}

void HRSensor::Reset()
{
    rxFlag = false;
    checkFlag = false;
    for ( int i = 0; i < PACKET_SIZE; i++ )
    {
        heartrateBuff[i] = 0;
    }
}

bool HRSensor::CheckHeartRate()
{
    rxFlag = rxData();
    checkFlag = checkHeartRate();
    return checkFlag;
}

uint8_t HRSensor::GetHeartRate()
{
    if ( checkFlag )
    {
        return heartrateBuff[1];
    }
    else
    {
        return 0;
    }
}

bool HRSensor::rxData()
{
    rxFlag = false;
    checkFlag = false;
    uint8_t buflen = sizeof(heartrateBuff);
    if ( radio_rx.recv(heartrateBuff, &buflen) )
    {
        return true;
    }
    return false;
}

bool HRSensor::checkHeartRate()
{
    return checkSign() && checkValue();
}

bool HRSensor::checkSign()
{
    if ( !rxFlag )
    {
        return false;
    }

    if ( heartrateBuff[0] != SIGN_BYTE )
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool HRSensor::checkValue()
{
    if ( !rxFlag )
    {
        return false;
    }

    if ( heartrateBuff[1] > 225 || heartrateBuff[1] < 30 )
    {
        return false;
    }
    else
    {
        return true;
    }
}