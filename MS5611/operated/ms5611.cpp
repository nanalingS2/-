#include "ms5611.h"
#include "twi.h"

extern Serial pc;

MS5611::MS5611(PinName sda, PinName scl, PinName ps)
    : ms(sda,scl), ps(ps) 
    {
        wait_ms(100);
        reset(MS_Const::RESET);
        wait_ms(1);

        // get_atmos_pressure (MS_Const::PROM_READ); //주소 000을 읽기 위한 것 
        // get_alt();
    }

void MS5611::reset(char com)
{
    ps = 1;
    wait_ms(10);
    
    pc.printf("%s\r\n", "start condition1");

    char cmd = com;
    ms.write(DEV_ADDR,&cmd,1,0);
    // ms.write(&cmd,1);

    pc.printf("%s\r\n", "stop condition1");

    // while(ms.readable()) {
    //     pc.putc(ms.getc());
    // }
    ps = 0;

}

// void MS5611::prom_read(char com)
// {
//     ps = 1;
//     pc.printf("%s\r\n", "start condition2");
    
//     char cmd = com;
//     char data[2];

//     //읽기 모드로 전환
//     ms.write(&DEV_ADDR,1);
//     ms.write(&cmd,1);

//     pc.printf("%s\r\n", "stop condition2");
// }

int MS5611::get_atmos_pressure (char com)
{
    ps = 1;
    pc.printf("%s\r\n", "start condition2");
    
    char cmd = com;
    char data[2];

    //읽기 모드로 전환
    ms.write(DEV_ADDR,&cmd, 1, 1);
    // ms.write(&cmd,1);

    pc.printf("%s\r\n", "stop condition2");

    // prom_read();

    //데이터 받아오기
    // ms.write(&DEV_ADDR,1);
    ms.read(DEV_ADDR, data, 2, 0);
    // ms.read(&data[1], 1);

    short atmos_pressure = (data[0] << 8) | data[1];

    pc.printf("atmos_pressure: %d\r\n", atmos_pressure);
    return atmos_pressure;
    // while(ms.readable()) {
    //     pc.putc(ms.getc());
    // }
    ps=0;
}

void MS5611::get_alt()
{
    ps = 1;
    pc.printf("%s\r\n", "start condition\r\n");
    
    //

    pc.printf("%s\r\n", "stop condition\r\n");
    
    // while(ms.readable()) {
    //     pc.putc(ms.getc());
    // }

}

unsigned char MS5611::crc4(unsigned int n_prom[])
{
    int cnt; // simple counter
    unsigned int n_rem; // crc reminder
    unsigned int crc_read; // original value of the crc
    unsigned char n_bit;

    n_rem = 0x00;
    crc_read=n_prom[7]; //save read CRC
    n_prom[7]=(0xFF00 & (n_prom[7])); //CRC byte is replaced by 0
    
    for (cnt = 0; cnt < 16; cnt++) // operation is performed on bytes
    {// choose LSB or MSB
        if (cnt%2==1) n_rem ^= (unsigned short) ((n_prom[cnt>>1]) & 0x00FF);
        else n_rem ^= (unsigned short) (n_prom[cnt>>1]>>8);
    
        for (n_bit = 8; n_bit > 0; n_bit--)
        {
            if (n_rem & (0x8000))
            {
                n_rem = (n_rem << 1) ^ 0x3000;
            }
            else
            {
                n_rem = (n_rem << 1);
            }
        }
    }

    n_rem= (0x000F & (n_rem >> 12)); // final 4-bit reminder is CRC code
    n_prom[7]=crc_read; // restore the crc_read to its original place
    
    return (n_rem ^ 0x0);
} 

// bool MS5611::readable()
// {
//     return ms.readable();
// }

// char MS5611::getc()
// {
//     return ms.getc();
// }

// void MS5611::putc(char c)
// {
//     ms.putc(c);
// }
