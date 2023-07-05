# dotori
## SENSOR
### MPU6050_I2C

p8: VLOGIC, Digital I/O supply voltage. VLOGIC must be =< VDD at all times.  
p9: AD0, I2C Slave Address LSB

p23: SCL, I2C serial clock  
p24: SDA, I2C serial data

The MPU60X0 alwalys operates as a slave device when communicating to the system processor, which thus acts as the master.

The slave adress of the MPU-60X0 is b110100X which is 7 bits long.  
The LSB bit if the 7 bit address is determined by the logic level on pin AD0.  
This allows two MPU-60X0s to be connected to the same I2C bus.  

When used in this configuration, the adress of the one of the devices/the other should be  
 -> b1101000(pin AD0 is logic to low): 0x68  
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




