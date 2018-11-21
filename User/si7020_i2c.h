#ifndef __SI7020_I2C_H
#define __SI7020_I2C_H

#define SI7020_I2C I2C1
#define SI7020_ADDRESS 0X80
#define SI7020_READ 0X01
#define SI7020_WRITE 0X00

#define SI7020_TEMPERATURE  0xE3
#define SI7020_HUMIDITY     0xE5
#define SI7020_THERMISTOR   0xEE
#define SI7020_SOFT_RESET   0xFE

struct SI7020_DATA
{
    int temperature;
    int humidity;
};
void si7020_read(int *temperature_);
#endif
