#include "mbed.h"
#include "ms5611.h"
#include "twi.h"

Serial pc(USBTX, USBRX);
MS5611 ms(p28, p27, p8);

int main()
{
    pc.baud(9600);

    int i;
    int cnt;
    unsigned char n_crc;

    char PROM_READ[8] = {0xA0,0xA2,0xA4,0xA6,0xA8,0xAA,0xAC,0xAE};
    
    // for (i=0;i<8;i++){ C[i]=ms.prom_read(PROM_READ[i]);}
    // n_crc=ms.crc4(C); 

    // for(i=0;i<16;i++) {
    //        ms.get_atmos_pressure(PROM_READ[i]);
    //     // ms.get_alt();
    // }




    while (true) {
       
       for(i=0;i<8;i++) {
           ms.get_atmos_pressure(PROM_READ[i]);
           
        // ms.get_alt();
       }

        wait_ms(1);
    }
}
