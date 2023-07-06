#ifndef __MPU6050_H__
#define __MPU6050_H__

#include "mbed.h"

namespace MPU_Regi
{
    enum RegiAddr
    {
        SMPLRT_DIV      = 0x19,
        CONFIG          = 0x1A,
        GYRO_CONFIG     = 0x1B,
        ACCEL_CONFIG    = 0x1C,
        ACCEL_XOUT_H    = 0x3B,
        TEMP_OUT_H      = 0x41,
        GYRO_XOUT_H     = 0x43,
        PWR_MGMT_1      = 0x6B,
        PWR_MGMT_2      = 0x6C,
        WHO_AM_I        = 0x75
    };
}

namespace MPU_Const
{
    enum GyroRange
    {
        GYRO_RANGE_250 = 0,
        GYRO_RANGE_500 = 1,
        GYRO_RANGE_1000 = 2,
        GYRO_RANGE_2000 = 3
    };

    enum AccelRange
    {
        ACCEL_RANGE_2G = 0,
        ACCEL_RANGE_4G = 1,
        ACCEL_RANGE_8G = 2,
        ACCEL_RANGE_16G = 3
    };
}

class MPU6050
{
private:
    I2C i2c;

    const char DEV_ADDR = (0x68 << 1);
    float FS_SEL;
    float AFS_SEL;

    void set_config(char reg, char data);
    char get_config(char reg);

public:
    MPU6050(PinName sda, PinName scl);

    void set_sample_rate(char div);
    void set_LPF(char cfg);
    void set_acc_range(char range);
    void set_gyro_range(char range);
    void reset();
    void enable();
    void set_clock(char clk=1);

    void get_acc_gyro_d(int16_t * acc, int16_t * gyro);
    void get_acc_gyro_f(float * acc, float * gyro);

};

#endif