#ifndef __MS5611_H__
#define __MS5611_H__

#include "mbed.h"

// namespace MS_Regi
// {
//     char PROM_READ[8] = {0xA0,0xA2,0xA4,0xA6,0xA8,0xAA,0xAC,0xAE};
// }

namespace MS_Const
{
    enum cmd
    {
        RESET = 0b00011110,
        ADC_READ = 0x00,
        // PROM_READ[16] = {0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE}; //0xA0 to 0xAE
    };
    enum ConvertD
    {
        D1_256 = 0x40,  //D1: Digital pressure value
        D1_512 = 0x42,
        D1_1024 = 0x44,
        D1_2048 = 0x46,
        D1_4096 = 0x48,

        D2_256 = 0x50,  //D2: Digital temperature value
        D2_512 = 0x52,
        D2_1024 = 0x54,
        D2_2048 = 0x56,
        D2_4096 = 0x58
    };
    enum Pressure
    {
        Base_pressure =993380
    };
}

class MS5611
{
private:
    I2C ms;
    DigitalOut ps;

    const char DEV_ADDR = (0x76<<1); //111011C: csb 보정값 = csb inverse?
    const char PROM_READ[8] = {0xA0,0xA2,0xA4,0xA6,0xA8,0xAA,0xAC,0xAE};

public:
    MS5611(PinName sda, PinName scl, PinName ps);
    
    void reset(char com);
    int get_d(char com);
    unsigned int get_cali_data(char com);
    void get_alt(int d1, int d2);

    int calculate(int d1,int d2);

    // unsigned char crc4(unsigned int n_prom[]);

    

    // bool readable();
    // char getc();
    // void putc(char c);
};

#endif
