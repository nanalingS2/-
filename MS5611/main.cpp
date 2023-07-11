#include "mbed.h"
#include "ms5611.h"

Serial pc(USBTX, USBRX);
MS5611 ms(p28, p27);

int main()
{
    pc.baud(9600);

    while (true) {
    //    pc.printf("");
    }
}
