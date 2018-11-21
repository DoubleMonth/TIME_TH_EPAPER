#include "si7020_i2c.h"
#include <stm8l15x.h>
#include "stm8l15x_i2c.h"
#include "stdio.h"

void si7020_delay(uint32_t time)
{
    uint32_t i,j;
    for(i=0;i<time;i++)
    {
        for(j=0;j<1000;j++)
        ;   
    }    
}

void si7020_read(int *temperature_)
{
    double temp;
    uint8_t data[2] = {0};
    uint16_t value=0;
    int  temp_int = 0;
//    I2C_GenerateSTOP(SI7020_I2C, ENABLE);
    while (I2C_GetFlagStatus(SI7020_I2C, I2C_FLAG_BUSY))
    {}
    I2C_GenerateSTART(SI7020_I2C, ENABLE);
    while(!I2C_CheckEvent(SI7020_I2C, I2C_EVENT_MASTER_MODE_SELECT))
    {}
    I2C_Send7bitAddress(SI7020_I2C, (uint8_t)SI7020_ADDRESS,I2C_Direction_Transmitter);
    while (!I2C_CheckEvent(SI7020_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
 	{}
    I2C_SendData(SI7020_I2C, SI7020_TEMPERATURE);
	while (!I2C_CheckEvent(SI7020_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED ))
	{}
    //Reception Phase 
	I2C_GenerateSTART(SI7020_I2C, ENABLE);
    while(!I2C_CheckEvent(SI7020_I2C, I2C_EVENT_MASTER_MODE_SELECT))
    {}
	I2C_Send7bitAddress(SI7020_I2C, (SI7020_ADDRESS | SI7020_READ), I2C_Direction_Receiver);
	while (!I2C_CheckEvent(SI7020_I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
    {}
    while (!I2C_CheckEvent(SI7020_I2C, I2C_EVENT_MASTER_BYTE_RECEIVED))
    {}
 //   si7020_delay(5);
	data[1] = I2C_ReceiveData(SI7020_I2C);
    I2C_AcknowledgeConfig(SI7020_I2C, ENABLE);
    while (I2C_GetFlagStatus(SI7020_I2C, I2C_FLAG_RXNE) == RESET)
    {}

	data[0] = I2C_ReceiveData(SI7020_I2C);
    I2C_AcknowledgeConfig(SI7020_I2C, ENABLE);
    I2C_AcknowledgeConfig(SI7020_I2C, DISABLE);
    I2C_GenerateSTOP(SI7020_I2C, ENABLE);
    value = data[0]|(data[1] << 8);
	temp          = (double)value;
    temp          = (temp / 65536.0f) * 175.72f - 46.85f;
    
    temp_int = (int) (temp *10);
    *temperature_ = temp_int;
    // printf("Now temperature is %d%d.%d\r\n",temp_int/100,(temp_int%100)/10,(temp_int)%10);
}