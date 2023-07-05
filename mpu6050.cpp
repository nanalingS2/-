#include "mpu6050.h"

// extern Serial pc;

MPU6050::MPU6050(PinName sda, PinName scl)
    : i2c(sda, scl)
{
    reset();
    wait_ms(1);

    enable();
    wait_ms(1);

    set_clock(1);
    set_sample_rate(1); // 1kHz/(1+1) = 500Hz;
    set_LPF(1);
    set_acc_range(MPU_Const::ACCEL_RANGE_2G);
    set_gyro_range(MPU_Const::GYRO_RANGE_250);

}

void MPU6050::set_config(char reg, char data)
{
    char cmd[2] = {reg, data};
    i2c.write(DEV_ADDR, cmd, 2, 0);
}

char MPU6050::get_config(char reg)
{
    char cmd = reg;
    i2c.write(DEV_ADDR, &cmd, 1, 1);
    i2c.read(DEV_ADDR, &cmd, 1, 0);

    return cmd;
}

void MPU6050::set_sample_rate(char div)
{
    /*
    Sampling Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV)
    Gyroscope Output Rate = 8kHz(DLPF disable(0)) or 1kHz(DLPF enable(1~6))
    */
    set_config(MPU_Regi::SMPLRT_DIV, div);

    // pc.printf("set sample rate: %d\n\r", div);
}

void MPU6050::set_LPF(char cfg)
{
    char config = get_config(MPU_Regi::CONFIG);
    config &= 0b11111000;
    config |= (cfg & 0b00000111);
    set_config(MPU_Regi::ACCEL_CONFIG, config);

    // pc.printf("set LPF: %d\n\r", cfg);
}

void MPU6050::set_acc_range(char range)
{
    char config = get_config(MPU_Regi::ACCEL_CONFIG);
    config &= 0b11100111;
    config |= (range << 3);
    set_config(MPU_Regi::ACCEL_CONFIG, config);

    switch(range)
    {
    case 0: AFS_SEL = 16384.0; break;
    case 1: AFS_SEL = 8192.0; break;
    case 2: AFS_SEL = 4096.0; break;
    case 3: AFS_SEL = 2048.0; break;
    }

    // pc.printf("set acc range: %d\n\r", range);
}


void MPU6050::set_gyro_range(char range)
{
    char config = get_config(MPU_Regi::GYRO_CONFIG);
    config &= 0b11100111;
    config |= (range << 3);
    set_config(MPU_Regi::GYRO_CONFIG, config);

    switch(range)
    {
    case 0: FS_SEL = 131.0; break;
    case 1: FS_SEL = 65.5; break;
    case 2: FS_SEL = 32.8; break;
    case 3: FS_SEL = 16.4; break;
    }

    // pc.printf("set gyro range: %d\n\r", range);
}

void MPU6050::reset()
{
    char config = 0b10000000;
    set_config(MPU_Regi::PWR_MGMT_1, config);

    // pc.printf("reset mpu6050\n\r");
}


void MPU6050::enable()
{
    char config = get_config(MPU_Regi::PWR_MGMT_1);
    config &= 0b10111111;
    set_config(MPU_Regi::PWR_MGMT_1, config);

    // pc.printf("enable\n\r");
}

void MPU6050::set_clock(char clk)
{
    /*
    Recommanded clk = 1,2,3 (gyro ref)
    */
    char config = get_config(MPU_Regi::PWR_MGMT_1);
    config &= 0b11111000;
    config |= (clk & 0b00000111);
    set_config(MPU_Regi::PWR_MGMT_1, config);

    // pc.printf("set clock: %d\n\r", clk);
}

void MPU6050::get_acc_gyro_d(int16_t * acc, int16_t * gyro)
{
    char data[14] = {MPU_Regi::ACCEL_XOUT_H};
    i2c.write(DEV_ADDR, data, 1, 1);
    i2c.read(DEV_ADDR, data, 14, 0);
    
    for(int i=0; i<3; i++){
        acc[i] = (int16_t)(((int16_t)data[i*2] << 8) | data[i*2+1]);
        gyro[i] = (int16_t)(((int16_t)data[i*2+8] << 8) | data[i*2+9]);
    }
}

void MPU6050::get_acc_gyro_f(float * acc, float * gyro)
{
    int16_t acc_d[3], gyro_d[3];
    get_acc_gyro_d(acc_d, gyro_d);

    for(int i=0; i<3; i++){
        acc[i] = acc_d[i]/AFS_SEL;
        gyro[i] = gyro_d[i]/FS_SEL;
    }
}
