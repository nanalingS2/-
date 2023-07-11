#include "hc12.h"

#define HEADER 0xFF
#define LEN 6

char packet[10];
extern Serial pc;

HC12::HC12(PinName TX, PinName RX, PinName set)
   : hc12(TX,RX), set(set)
   {
    //    transmit_packet();
        wait_ms(100);
        set_default(68);
        // wait_ms(100);
        
        set_baudrate(9600); 
        set_tx_power(HC12_CONST::TX_Power_20);
       
    //    set_air_baudrate();
   }

   void HC12::transmit_packet(char *data, int len) {
       
    //    if (len>MAX_PACKET_SIZE){
    //        return;
    //    }
    //    packet[0]=HEADER;
    //    packet[1]=HEADER;
    //    packet[2]=LEN;
    //    memcpy(packet+3, data, len);

    //    hc12.write(packet,len+3); 

       hc12.write(data, len); 
    }

   void HC12::set_default(long d) {
       char defaul[30];

       set = 0;
       sprintf(defaul, "AT+%cEFAULT",d);

       hc12.printf("%s", defaul);
       pc.printf("%s\r\n", defaul);

       wait_ms(50);

       while (hc12.readable()) {
           pc.putc(hc12.getc());
       } 
       set = 1; 
   }

   void HC12::set_tx_power(long x) {
      char txPower[10];

      set = 0;
      sprintf(txPower, "AT+P%lu", x);

      hc12.printf("%s", txPower);
      pc.printf("%s\r\n", txPower);

      wait_ms(50);

      while(hc12.readable()) {
          pc.putc(hc12.getc());
      }

      set = 1;
      
   }

   void HC12::set_baudrate(long baud) {
       char baudrate[10];

       set = 0;
       sprintf(baudrate, "AT+B%lu", baud);

       hc12.printf("%s", baudrate);
       pc.printf("%s\r\n", baudrate);

       wait_ms(50);

       while(hc12.readable()) {
           pc.putc(hc12.getc());
       }

       set = 1;
   }

//    void HC12::set_air_baudrate(long a_baud) {
//       //
//    }

bool HC12::readable()
{
    return hc12.readable();
}

char HC12::getc()
{
    return hc12.getc();
}
void HC12::putc(char c)
{
    hc12.putc(c);
}
