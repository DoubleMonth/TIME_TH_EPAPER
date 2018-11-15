#include <stm8l15x.h>
#include "stm8l15x_i2c.h"
#include "user_iic.h"
#include "stdio.h"


void userIICInit(void)
{
    I2C_DeInit(I2C1);
    CLK_PeripheralClockConfig(CLK_Peripheral_I2C1, ENABLE);

    /*!< Configure LM75_I2C pins: SCL */
    GPIO_Init(GPIOC, GPIO_Pin_1, GPIO_Mode_In_PU_No_IT);

    /*!< Configure LM75_I2C pins: SDA */
    GPIO_Init(GPIOC, GPIO_Pin_0, GPIO_Mode_In_PU_No_IT);

    I2C_Init(I2C1,100000,0XA0,I2C_Mode_SMBusHost,I2C_DutyCycle_2,I2C_Ack_Enable,I2C_AcknowledgedAddress_7bit);
    I2C_ITConfig(I2C1, (I2C_IT_TypeDef)(I2C_IT_EVT | I2C_IT_BUF) , ENABLE);
    enableInterrupts();
    
}