#include "ms5611.h"

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
    
    pc.printf("%s\r\n", "start condition");

    char cmd = com;
    ms.write(&DEV_ADDR,1);
    ms.write(&cmd,1);

    pc.printf("%s\r\n", "stop condition");

    while(ms.readable()) {
        pc.putc(ms.getc());
    }
    // ps = 0;

}

void MS5611::get_atmos_pressure (char com)
{
    ps = 1;
    pc.printf("%s\r\n", "start condition");
    
    char cmd = com;
    char data[2];

    //읽기 모드로 전환
    ms.write(&DEV_ADDR,1);
    ms.write(&cmd,1);

    pc.printf("%s\r\n", "stop condition");

    //데이터 받아오기
    ms.write(&DEV_ADDR,1);
    ms.read(&data[0], 1);
    ms.read(&data[1], 1);

    unsigned short atmos_pressure = (data[0] << 8) | data[1];

    pc.printf("atmos_pressure: %d\r\n", atmos_pressure);

    while(ms.readable()) {
        pc.putc(ms.getc());
    }

}

//     void MS5611::get_alt()
// {
//     ps = 1;
//     pc.printf("%s\r\n", "start condition\r\n");
    
//     //

//     pc.printf("%s\r\n", "stop condition\r\n");
    
//     while(ms.readable()) {
//         pc.putc(ms.getc());
//     }

// }


bool MS5611::readable()
{
    return ms.readable();
}

char MS5611::getc()
{
    return ms.getc();
}

void MS5611::putc(char c)
{
    ms.putc(c);
}
