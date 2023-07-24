#include "hc12.h"
#include "mbed.h"
// #include <type_traits>

// #define HEADER 0xFF
// #define LEN 6

// char packet[10];


HC12::HC12(PinName TX, PinName RX, PinName set, int baud)
   : hc12(TX, RX, baud), set(set)
   {
    //    transmit_packet();
        // wait_ms(100);

        // set=0;

    //     hc12.printf("AT");
    //     pc.printf("AT\r\n");

    //     while (hc12.readable()) {
    //        pc.putc(hc12.getc());
    //    } 

        // pc.baud(115200);
        wait_ms(100);
        
        // set_default(68);
        set_default();
        wait_ms(100);
        
        // wait_ms(100);

        // set_baudrate(9600); 
        // wait_ms(50);
        
        
        set_tx_power(HC12_CONST::TX_Power_20);
        wait_ms(100);
        
        set_frequency_channel(10);  
        set_transmission_mode(3);
        wait_ms(50);
        set_baudrate(115200);

        
         
        
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

   void HC12::set_default() { //long d
       char defaul[30];

       set = 0;
       sprintf(defaul, "AT+DEFAULT");

       wait_ms(200);

       hc12.printf("%s", defaul);
       pc.printf("%s\r\n", defaul);
       hc12.baud(9600);

       wait_ms(300);

        while (hc12.readable()) {
            pc.putc(hc12.getc());
        } 

       hc12.printf("%s", defaul);
       pc.printf("%s\r\n", defaul);

       wait_ms(300);
    //    pc.printf("set=%d\r\n",set);
       while (hc12.readable()) {
           pc.putc(hc12.getc());
       } 
       set = 1; 
    //    pc.printf("set=%d\r\n",set);
   }

   void HC12::set_tx_power(long x) {
      char txPower[10];

      set = 0;
      sprintf(txPower, "AT+P%lu", x);

      wait_ms(50);

      hc12.printf("%s", txPower);
      pc.printf("%s\r\n", txPower);

      wait_ms(50);

      while(hc12.readable()) {
          pc.putc(hc12.getc());
      }

      set = 1;
      
   }

   void HC12::set_baudrate(long long baud) {
       char baudrate[10];

       set = 0;
       sprintf(baudrate, "AT+B%lu", baud);

       wait_ms(50);

       hc12.printf("%s", baudrate);
       pc.printf("%s\r\n", baudrate);
       hc12.baud(baud);
       wait_ms(50);
       
       while(hc12.readable()) {
           pc.putc(hc12.getc());
       }

       set = 1;
   }

//    void HC12::set_air_baudrate(long a_baud) {
//       //
//    }


    void HC12::set_frequency_channel(int div){
     char channel[10];

      set = 0;

      if(div<100 && div>=10){
          sprintf(channel, "AT+C0%d", div);

          wait_ms(50);
      }
      else if(div<10){
          sprintf(channel, "AT+C00%d", div);
          
          wait_ms(50);
      }
      else{
          sprintf(channel, "AT+C%d", div);

          wait_ms(50);
      }

      hc12.printf("%s", channel);
      pc.printf("%s\r\n", channel);

      wait_ms(50);

      while(hc12.readable()) {
          pc.putc(hc12.getc());
      }

      set = 1;

}

void HC12::set_transmission_mode(int mode)
{
    char tmode[10];

       set = 0;
       sprintf(tmode, "AT+FU%d", mode);

       wait_ms(100);

       hc12.printf("%s", tmode);
       pc.printf("%s\r\n", tmode);

       wait_ms(100);

       while(hc12.readable()) {
           pc.putc(hc12.getc());
       }

       set = 1;
    }   

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

// #include "hc12.h"

// #define HEADER 0xFF
// #define LEN 6

// char packet[10];
// extern Serial pc;

// HC12::HC12(PinName TX, PinName RX, PinName set)
//    : hc12(TX,RX), set(set)
//    {
//     //    transmit_packet();
//         wait_ms(100);
//         set_default(68);
//         // wait_ms(100);
        
//         set_baudrate(9600); 
//         set_tx_power(HC12_CONST::TX_Power_20);
       
//     //    set_air_baudrate();
//    }

//    void HC12::transmit_packet(char *data, int len) {
       
//     //    if (len>MAX_PACKET_SIZE){
//     //        return;
//     //    }
//     //    packet[0]=HEADER;
//     //    packet[1]=HEADER;
//     //    packet[2]=LEN;
//     //    memcpy(packet+3, data, len);

//     //    hc12.write(packet,len+3); 

//        hc12.write(data, len); 
//     }

//    void HC12::set_default(long d) {
//        char defaul[30];

//        set = 0;
//        sprintf(defaul, "AT+%cEFAULT",d);

//        hc12.printf("%s", defaul);
//        pc.printf("%s\r\n", defaul);

//        wait_ms(50);

//        while (hc12.readable()) {
//            pc.putc(hc12.getc());
//        } 
//        set = 1; 
//    }

//    void HC12::set_tx_power(long x) {
//       char txPower[10];

//       set = 0;
//       sprintf(txPower, "AT+P%lu", x);

//       hc12.printf("%s", txPower);
//       pc.printf("%s\r\n", txPower);

//       wait_ms(50);

//       while(hc12.readable()) {
//           pc.putc(hc12.getc());
//       }

//       set = 1;
      
//    }

//    void HC12::set_baudrate(long baud) {
//        char baudrate[10];

//        set = 0;
//        sprintf(baudrate, "AT+B%lu", baud);

//        hc12.printf("%s", baudrate);
//        pc.printf("%s\r\n", baudrate);

//        wait_ms(50);

//        while(hc12.readable()) {
//            pc.putc(hc12.getc());
//        }

//        set = 1;
//    }

// //    void HC12::set_air_baudrate(long a_baud) {
// //       //
// //    }

// bool HC12::readable()
// {
//     return hc12.readable();
// }

// char HC12::getc()
// {
//     return hc12.getc();
// }
// void HC12::putc(char c)
// {
//     hc12.putc(c);
// }
