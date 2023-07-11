#ifndef __MS5611_H__
#define __MS5611_H__

#include "mbed.h"

namespace MS_Const
{
    enum cmd
    {
        RESET = 0x1E,
        ADC_READ = 0x00,
        PROM_READ = 0xA0 //0xA0 to 0xAE
    };
    enum ConvertD
    {
        D1_256 = 0x40,
        D1_512 = 0x42,
        D1_1024 = 0x44,
        D1_2048 = 0x46,
        D1_4096 = 0x48,

        D2_256 = 0x50,
        D2_512 = 0x52,
        D2_1024 = 0x54,
        D2_2048 = 0x56,
        D2_4096 = 0x58
    };
}

class MS5611
{
private:
    I2C i2c;

    const char DEV_ADDR = 0b11101100; //111011C0: csb 보정값

public:
    MS5611(PinName sda, PinName scl, PinName csb);
    
    void reset(long reg);
    void get_atmos_pressure ();
    void get_alt();
};

#endif
