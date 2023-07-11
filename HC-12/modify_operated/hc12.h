#ifndef __hc12_H__
#define __hc12_H__

#include "mbed.h"

namespace HC12_CONST
{
    enum TxPower
    {
        TX_Power_inverse_1 = 1,
        TX_Power_2 = 2,
        TX_Power_5 = 3,
        TX_Power_8 = 4,
        TX_Power_11 = 5,
        TX_Power_14 = 6,
        TX_Power_17 = 7,
        TX_Power_20 = 8 
    };
    
    // char MAX_PACKET_SIZE=
}

class HC12 {
private:
    Serial hc12;
    DigitalOut set;

    // const char 
    


public:
    HC12(PinName TX, PinName RX, PinName set);

    void transmit_packet(char*data, int len);
    // void set_default();
    void set_tx_power(long x);
    void set_baudrate(long baud);
    void set_air_baudrate(long a_baud);

    bool readable();
    char getc();
    void putc(char c);

};

#endif
