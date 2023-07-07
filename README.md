# dotori
## SENSOR
### mbed

**write()** : used to send data to a device.  
**read()** : reads the specified number of bytes from the device at the specified address and stores the received data in the provided 'data' buffer.

*The below code defines enumeration(enum) types, 'GyroRange' within the 'name' namespace.*
<pre>
    <code>
namespace name {  
  enum GyroRange {  
    GYRO_RANGE_250=0,  //
    GYRO_RANGE_500=1,  
    GYRO_RANGE_1000=2,  
    GYRO_RANGE_2000=3  
  };  
}  
    </code>
</pre>
        
### MPU6050

**init value : 0x00** (cf. PWR_MGMT_1, WHO_AM_I)  
PWR_MGMT_1=0x40  
WHO_AM_I=0x68

p8: VLOGIC, Digital I/O supply voltage. VLOGIC must be =< VDD at all times.  
p9: AD0, I2C Slave Address LSB

p23: SCL, I2C serial clock  
p24: SDA, I2C serial data

**Register 28** - Accelerometer Configuration(ACCEL_CONFIG)  

 |AFS_SEL|Full Scale Range|     
 |:---:|:---:|
 |0|+-2g|
 |1|+-4g|
 |2|+-8g|
 |3|+-16g|
 
 AFS_SEL : 2-bit unsigned value. Selects the *full scale range* of accelerometers. 
 
**Register 27** - Gyroscope Configuration(GYRO_CONFIG) 

 |FS_SEL|Full Scale Range|     
 |:---:|:---:|
 |0|+-2g|
 |1|+-4g|
 |2|+-8g|
 |3|+-16g|

*The MPU60X0 alwalys operates as a slave device when communicating to the system processor, which thus acts as the master.*

**The slave adress of the MPU-60X0 is b110100X which is 7 bits long.**  
The LSB bit if the 7 bit address is determined by the logic level on pin AD0.  
This allows two MPU-60X0s to be connected to the same I2C bus.  

When used in this configuration, the adress of the one of the devices/the other should be  
 -> **b1101000(pin AD0 is logic to low): 0x68**  
 -> b1101001(pin AD0 is logic to high)  

|name|content|
|:---:|:---:|
|S|start condition, SDA goes from high to low while SCL is high|
|AD|slave I2C address|
|W|Write bit(0)|
|R|Read bit(1)|
|ACK|Acknowledge: SDA line is low while the SCL line is high at the 9th clock cycle|
|NACK|Not-Acknowledge, SDA line stays high at the 9th cycle|
|RA| MPU-60X0 internal register address|
|DATA|transmit or received data|
|P|stop condition, SDA going from low to high while SCL is high|

<**why we use 'wait_ms()' function in mbed**>
1. **Time Delay** : stable sensor data acquisition
2. **Timers and Periodic Tasks** :  
   useful for implementing tasks  
   that need to be executed periodically with a specific time interval.  
3. **Power Management** :
   can transition the microcontroller into a low-power state,  
   saving energy during the wait period.
4. **Synchronization** :
    relies on the platform and timers to provide accurate time delays.

## C++
### Bitwise operator
| : bit OR  
& : bit AND



## HC-12아두이노 코드
[Hc-12](https://rasino.tistory.com/326)



