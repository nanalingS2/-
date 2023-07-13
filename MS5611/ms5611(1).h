#ifndef __MS5611_H__
#define __MS5611_H__

#include "mbed.h"

namespace MS_Const
{
    enum cmd
    {
        RESET = 0b00011110,
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
    Serial ms;
    DigitalOut ps;

    const char DEV_ADDR = (0x76<<1); //111011C: csb 보정값 = csb inverse?

public:
    MS5611(PinName sda, PinName scl, PinName ps);
    
    void reset(char com);
    void get_atmos_pressure (char com);
    void get_alt();

    bool readable();
    char getc();
    void putc(char c);
};

#endif
