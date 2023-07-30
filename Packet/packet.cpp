#include "packet.h"

Packet::Packet()
{
    buf[0] = Packet::HEADER1;
    buf[1] = Packet::HEADER2;
}

void Packet::add_chksum()
{
    int len = buf[3] + 5;
    char chksum = 0;
    for(int i=2; i<len-1; i++)
    {
        chksum ^= buf[i];
    }
    buf[len-1] = chksum;
}

int Packet::get_gps_packet(char * packet, GpsData &gps)
{
    buf[2] = MSG_GPS;
    buf[3] = GPS_SIZE;
    
    buf[FIX] = gps.fixType;
    memcpy(buf+LON, &gps.lon, 4);
    memcpy(buf+LAT, &gps.lat, 4);
    memcpy(buf+ALT, &gps.height, 4);
    memcpy(buf+VN, &gps.velN, 4);
    memcpy(buf+VE, &gps.velE, 4);
    memcpy(buf+VD, &gps.velD, 4);
    add_chksum();

    memcpy(packet, buf, GPS_SIZE+5);
    return GPS_SIZE+5;
}

int Packet::get_imu_packet(char * packet, float * acc, float * gyro, float * mag, float * press)
{
    buf[2] = MSG_IMU;
    buf[3] = IMU_SIZE;
    memcpy(buf+AX, acc, 12);
    memcpy(buf+GX, gyro, 12);
    memcpy(buf+MX, mag, 12);
    memcpy(buf+TEMP, press, 12);
    add_chksum();

    memcpy(packet, buf, IMU_SIZE+5);
    return IMU_SIZE+5;
}

int Packet::get_imu_gps_packet(char * packet, float * acc, float * gyro, float * mag, float * press, GpsData &gps) 
{
    buf[2] = MSG_IMU_GPS;
    buf[3] = IMU_GPS_SIZE;

    buf[FIX] = gps.fixType;
    memcpy(buf+AX, acc, 12);
    memcpy(buf+GX, gyro, 12);
    memcpy(buf+MX, mag, 12);
    memcpy(buf+TEMP, press, 12);
    memcpy(buf+LON, &gps.lon, 4);
    memcpy(buf+LAT, &gps.lat, 4);
    memcpy(buf+ALT, &gps.height, 4);
    memcpy(buf+VN, &gps.velN, 4);
    memcpy(buf+VE, &gps.velE, 4);
    memcpy(buf+VD, &gps.velD, 4);
    add_chksum();

    memcpy(packet, buf, IMU_GPS_SIZE+5);
    return IMU_GPS_SIZE+5;
}
