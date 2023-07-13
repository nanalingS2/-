#include "mbed.h"
#include "ms5611.h"

Serial pc(USBTX, USBRX);
MS5611 ms(p28, p27, p8);

int main()
{
    pc.baud(9600);
    
    while (true) {
       
        ms.get_atmos_pressure();
        ms.get_alt();

        wait_ms(1);
    }
}
