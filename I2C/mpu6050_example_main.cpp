#include "mbed.h"
#include "mpu6050.h"

Serial pc(USBTX, USBRX);
MPU6050 mpu(p28, p27);

float acc[3], gyro[3];
// int16_t acc_d[3], gyro_d[3];

int main()
{
    pc.baud(9600);
    
    while (true) {
        mpu.get_acc_gyro_f(acc, gyro);
        pc.printf("[Acc] \t%f \t%f \t%f \t/ [Gyro] \t%f \t%f \t%f\n\r", acc[0], acc[1], acc[2], gyro[0], gyro[1], gyro[2]);

        // mpu.get_acc_gyro_d(acc_d, gyro_d);
        // pc.printf("[Acc] \t%d \t%d \t%d \t/ [Gyro] \t%d \t%d \t%d\n\r", acc_d[0], acc_d[1], acc_d[2], gyro_d[0], gyro_d[1], gyro_d[2]);

        wait(0.01);
    }
}
