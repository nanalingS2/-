#include "hc12.h"

#define HEADER 0xFF
#define LEN 6

char packet[10];

HC12::HC12(PinName TX, PinName RX)
   : hc12(TX,RX)
   {
    //    transmit_packet();
    //    set_default();
       set_tx_power(HC12_CONST::TX_Power_8);
       set_baudrate(9600); 
    //    set_air_baudrate();
   }

   void HC12::transmit_packet(char *data, int len) {
       
    //    if (len>MAX_PACKET_SIZE){
    //        return;
    //    }
       packet[0]=HEADER;
       packet[1]=HEADER;
       packet[2]=LEN;
       memcpy(packet+3, data, len);

       hc12.write(packet,len+3);  
    }

//    void HC12::set_default() {
//        //
//    }

   void HC12::set_tx_power(long x) {
      char txPower[10];
      sprintf(txPower, "AT+P%lu", x);

      hc12.printf("%s\r\n", txPower);

      void wait_ms(int n=100);

      while(hc12.readable()) {
          hc12.getc();
      }
      
   }

   void HC12::set_baudrate(long baud) {
       char baudrate[10];
       sprintf(baudrate, "AT+B%lu", baud);

       hc12.printf("%s\r\n", baudrate);

       void wait_ms(int n=100);

       while(hc12.readable()) {
           hc12.getc();
       }
   }

//    void HC12::set_air_baudrate(long a_baud) {
//       //
//    }
