#include "ms5611.h"

extern Serial pc;

MS5611::MS5611(PinName sda, PinName scl, PinName ps)
    : ms(sda,scl), ps(ps) 
    {
        reset();
        wait_ms(1);

        get_atmos_pressure ();
        get_alt();
    }

void MS5611::reset()
{
    ps = 1;
    pc.printf("%s\r\n", 'start condition');

    char cmd[8] = {0,0,0,1,1,1,1,0};
    ms.write(DEV_ADDR, cmd, 8, 0); // 너무 많은 값 불러와서 오류...?

    pc.printf("%s\r\n", 'stop condition');

    while(ms.readable()) {
        pc.putc(ms.getc());
    }

}

    void MS5611::get_alt()
{
    ps = 1;
    pc.printf("%s\r\n", 'start condition');
    
    //

    pc.printf("%s\r\n", 'stop condition');
    
    while(ms.readable()) {
        pc.putc(ms.getc());
    }

}

void MS5611::get_atmos_pressure ()
{
    ps = 1;
    pc.printf("%s\r\n", 'start condition');
    
    //

    pc.printf("%s\r\n", 'stop condition');

    while(ms.readable()) {
        pc.putc(ms.getc());
    }

}

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
