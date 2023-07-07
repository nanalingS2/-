#include "mbed.h"

Serial pc(USBTX, USBRX);  // 시리얼 모니터용 객체
Serial hc12(D2, D3);     // HC-12 모듈용 객체 (소프트웨어 시리얼 통신 설정)

int main()
{
    pc.baud(9600);         // 시리얼 모니터 통신 속도 설정
    hc12.baud(9600);       // HC-12 모듈 통신 속도 설정

    while (1) {
        if (hc12.readable()) {          // HC-12 모듈로부터 수신된 데이터가 있는 경우
            pc.putc(hc12.getc());       // HC-12 모듈의 데이터를 시리얼 모니터로 전송
        }
        if (pc.readable()) {            // 시리얼 모니터로부터 입력된 데이터가 있는 경우
            hc12.putc(pc.getc());       // 입력된 데이터를 HC-12 모듈로 전송
        }
    }
}
