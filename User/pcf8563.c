#include <stm8l15x.h>
#include "stm8l15x_i2c.h"
#include "pcf8563.h"
#include "stdio.h"

unsigned char time_buf[8];
unsigned char time_buf1[8];


void userIICInit(void)
{
//	I2C_Cmd(PCF8563_I2C, ENABLE);

//	I2C_DeInit(PCF8563_I2C);
//    CLK_PeripheralClockConfig(CLK_Peripheral_I2C1, ENABLE);

//    I2C_Init(PCF8563_I2C,100000,0XA0,I2C_Mode_SMBusHost,I2C_DutyCycle_2,I2C_Ack_Enable,I2C_AcknowledgedAddress_7bit);
//    I2C_ITConfig(PCF8563_I2C, (I2C_IT_TypeDef)(I2C_IT_EVT | I2C_IT_BUF) , ENABLE);
//    enableInterrupts();

//	GPIO_Init(GPIOC, GPIO_Pin_0|GPIO_Pin_1, GPIO_Mode_Out_PP_High_Fast);

    
}
//uint8_t pcf8563ReadOneByte(uint16_t ReadAddr)
//{
//	uint8_t temp=0;
//	I2C_GenerateSTART(PCF8563_I2C, ENABLE);
//	I2C_SendData(PCF8563_I2C, (uint8_t)PCF8563_ADDRESS);
//	while (!I2C_CheckEvent(PCF8563_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
//	{}
//	I2C_SendData(PCF8563_I2C, (uint8_t)(ReadAddr));
//	while (!I2C_CheckEvent(PCF8563_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
//	{}
//	
//	I2C_GenerateSTART(PCF8563_I2C, ENABLE);
//	I2C_SendData(PCF8563_I2C, PCF8563_ADDRESS|PCF8563_READ);
//	while (!I2C_CheckEvent(PCF8563_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
//	{}
//	temp = I2C_ReceiveData(PCF8563_I2C);
//	I2C_GenerateSTOP(PCF8563_I2C, ENABLE);
//	
//}
void delay_us(uint32_t time)
{
	uint32_t i,j;
	for(i=0;i<time;i++)
	{
		for(j=0;j<10;j++)
			;
	}
}
void delay_ms(uint32_t time)
{
	delay_us(1000*time);
}
void PCF_IIC_Start(void)
{
	PCF_SDA_OUT();     //sda线输出
	SET_PCF_IIC_SDA();	  	  
	SET_PCF_IIC_SCL();
	delay_us(4);
 	RESET_PCF_IIC_SDA();//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	RESET_PCF_IIC_SCL();//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void PCF_IIC_Stop(void)
{
	PCF_SDA_OUT();//sda线输出
	RESET_PCF_IIC_SCL();
	RESET_PCF_IIC_SDA();//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	SET_PCF_IIC_SCL(); 
	SET_PCF_IIC_SDA();//发送I2C总线结束信号
	delay_us(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 PCF_IIC_Wait_Ack(void)
{
	uint32_t ucErrTime=0;
	SET_PCF_IIC_SDA();
	PCF_SDA_IN();      //SDA设置为输入  
	
	delay_us(2);	   
	SET_PCF_IIC_SCL();
	delay_us(2);	 
	while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0))
	{
		ucErrTime++;
		if(ucErrTime>2500)
		{
			PCF_IIC_Stop();
			return 1;
		}
	}
	RESET_PCF_IIC_SCL();//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void PCF_IIC_Ack(void)
{
	RESET_PCF_IIC_SCL();
	PCF_SDA_OUT();
	RESET_PCF_IIC_SDA();
	delay_us(2);
	SET_PCF_IIC_SCL();
	delay_us(2);
	RESET_PCF_IIC_SCL();
}
//不产生ACK应答		    
void PCF_IIC_NAck(void)
{
	RESET_PCF_IIC_SCL();
	PCF_SDA_OUT();
	SET_PCF_IIC_SDA();
	delay_us(2);
	SET_PCF_IIC_SCL();
	delay_us(2);
	RESET_PCF_IIC_SCL();
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void PCF_IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
	PCF_SDA_OUT(); 	    
    RESET_PCF_IIC_SCL();//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
		if (txd&0x80)
			{
			SET_PCF_IIC_SDA();
			}
		else
			{
			RESET_PCF_IIC_SDA();
			}
        txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		SET_PCF_IIC_SCL();
		delay_us(2); 
		RESET_PCF_IIC_SCL();	
		delay_us(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
uint8_t PCF_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	PCF_SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        RESET_PCF_IIC_SCL(); 
        delay_us(2);
		SET_PCF_IIC_SCL();
        receive<<=1;
        if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0))receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        PCF_IIC_NAck();//发送nACK
    else
        PCF_IIC_Ack(); //发送ACK   
    return receive;
}

uint8_t PCF8563_ReadOneByte(uint16_t ReadAddr)
{				  
        uint8_t i;	
        uint8_t temp=0;
	PCF_IIC_Start();  //开始
	PCF_IIC_Send_Byte(PCF8563_ADDRESS);//发送器件地址
	i=PCF_IIC_Wait_Ack();	//等待应答
	PCF_IIC_Send_Byte(ReadAddr);//发送寄存器地址
	PCF_IIC_Wait_Ack();//等待应答
	PCF_IIC_Start();  //开始
	PCF_IIC_Send_Byte(PCF8563_ADDRESS|PCF8563_READ);//发送器件地址
	PCF_IIC_Wait_Ack();//等待应答
	temp=PCF_IIC_Read_Byte(0);		   
    PCF_IIC_Stop();//产生一个停止条件	    
	return temp;
}
//在PCF8563指定地址写入一个数据
//WriteAddr  :写入数据的目的地址    
//DataToWrite:要写入的数据
void PCF8563_WriteOneByte(u8 WriteAddr,u8 DataToWrite)
{				   	  	    																 
    PCF_IIC_Start();  //开始
	PCF_IIC_Send_Byte(PCF8563_ADDRESS);//发送器件地址
	PCF_IIC_Wait_Ack();	//等待应答
	PCF_IIC_Send_Byte(WriteAddr);//发送寄存器地址
	PCF_IIC_Wait_Ack();//等待应答
	PCF_IIC_Send_Byte(DataToWrite);     //发送字节	
	PCF_IIC_Wait_Ack();//等待应答
	PCF_IIC_Stop();//产生一个停止条件 
	delay_ms(10);	 
}
void PCF8563_Read_Time(void)
{
	uint8_t i,temp;
	time_buf[1]=PCF8563_ReadOneByte(PCF8563_YEAR_ADDRESS)&0XFF;
	time_buf[2]=PCF8563_ReadOneByte(PCF8563_MONTH_ADDRESS)&0X1F;
	time_buf[3]=PCF8563_ReadOneByte(PCF8563_DAY_ADDRESS)&0X3F;
	time_buf[4]=PCF8563_ReadOneByte(PCF8563_HOUR_ADDRESS)&0X3F;
	time_buf[5]=PCF8563_ReadOneByte(PCF8563_MINUTE_ADDRESS)&0X7F;
	time_buf[6]=PCF8563_ReadOneByte(PCF8563_SECOND_ADDRESS)&0X7F;
	time_buf[7]=PCF8563_ReadOneByte(PCF8563_WEEK_ADDRESS)&0X07;
	for(i=0;i<8;i++)
	{
		temp=time_buf[i]/16;
		time_buf1[i]=time_buf[i]%16;
		time_buf1[i]=time_buf1[i]+temp*10;
	}
}



