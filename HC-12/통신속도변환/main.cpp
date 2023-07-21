#include "mbed.h"
#include "hc12.h"

Serial pc(USBTX, USBRX);
HC12 hc12(p9, p10, p8);

int main()
{
    //통신 속도 설정
    // pc.baud(115200); //
    
    // hc12.baud(9600);
    // hc12.set_tx_power(HC12_CONST::TX_Power_20);

    
    // hc12.printf("Enter a value: ");
   

    while (true) { 
        if (pc.readable()) {
            // hc12.putc(pc.printf("value: "));
            hc12.putc(pc.getc());
        }

        if (hc12.readable()) {
        //    pc.printf("value: ");
            pc.putc(hc12.getc());
        }
                // hc.read();

    }
}

// void set_baudrate() {

// }






// int main() {
//     pc.baud(9600);
//     hc12.baud(9600);
//     hc12.printf("Enter a value: \r\n");

//     while(true) {
//          if (pc.readable()) {
//              int d=pc.getc();
//             hc12.putc(d);
//             // pc.putc(hc12.getc());
//         }
//          if (hc12.readable()) {
//             int d=hc12.getc();
//             pc.putc(d);
//             // pc.putc(hc12.getc());
//          }
//     }
// }
