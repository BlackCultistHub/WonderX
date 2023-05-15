// @file
// @details Definition of heartrate RX class
// @copyright BlackCultist 2023

#ifndef HEARTRATE_H
#define HEARTRATE_H

#include <RH_ASK.h>
#include <SPI.h>
#include <inttypes.h>

#define PACKET_SIZE 2
#define SIGN_BYTE 0x9D
class HRSensor
{
public:
    HRSensor();

    void Init();

    void Reset();

    bool CheckHeartRate();

    uint8_t GetHeartRate();

private:
    bool rxData();

    bool checkHeartRate();

    bool checkSign();

    bool checkValue();

private:
    RH_ASK radio_rx;
    bool rxFlag = false;
    bool checkFlag = false;
    uint8_t heartrateBuff[PACKET_SIZE] = {};
};

#endif // end file guardian