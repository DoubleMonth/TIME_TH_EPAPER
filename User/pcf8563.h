#ifndef __PCF8563_H_
#define __PCF8563_H_
#define PCF8563_I2C I2C1
#define PCF8563_ADDRESS 0XA2
#define PCF8563_READ 0X01
#define PCF8563_WRITE 0X00

//控制和状态寄存器
#define CONTROL_STATUS_1 (unsigned char)0X00    
#define CONTROL_STATUS_2 (unsigned char)0X01

//时间和日期寄存器
#define PCF8563_SECOND_ADDRESS (unsigned char)0X02				//秒地址
#define PCF8563_MINUTE_ADDRESS (unsigned char)0X03				//分地址
#define PCF8563_HOUR_ADDRESS (unsigned char)0X04				//时地址
#define PCF8563_DAY_ADDRESS (unsigned char)0X05				//日地址
#define PCF8563_WEEK_ADDRESS (unsigned char)0X06					//星期地址
#define PCF8563_MONTH_ADDRESS (unsigned char)0X07				//月地址
#define PCF8563_YEAR_ADDRESS (unsigned char)0X08				//年地址

#define PCF8563_MINUTE_ALARM_ADDRESS 0X09				//闹钟分地址
#define PCF8563_HOUR_ALARM_ADDRESS 0X0A				//闹钟时地址
#define PCF8563_DAY_ALARM_ADDRESS 0X0B				//闹钟日地址
#define PCF8563_WEEK_ALARM_ADDRESS 0X0C					//闹钟星期地址

#define PCF8563_CLKOUT_CONTROL 0X0D				//时钟输出控制地址

#define PCF_SDA_IN()  {GPIO_Init(GPIOC, GPIO_Pin_0, GPIO_Mode_In_PU_No_IT);}
#define PCF_SDA_OUT() {GPIO_Init(GPIOC, GPIO_Pin_0, GPIO_Mode_Out_PP_High_Fast);}

#define SET_PCF_IIC_SCL()    {GPIO_SetBits(GPIOC,GPIO_Pin_1);}
#define RESET_PCF_IIC_SCL() 	{GPIO_ResetBits(GPIOC,GPIO_Pin_1);}

#define SET_PCF_IIC_SDA()    {GPIO_SetBits(GPIOC,GPIO_Pin_0);}
#define RESET_PCF_IIC_SDA() {GPIO_ResetBits(GPIOC,GPIO_Pin_0);}


void userIICInit(void);
//uint8_t pcf8563ReadOneByte(uint16_t ReadAddr);

void PCF_IIC_Start(void);
void PCF_IIC_Stop(void);
u8 PCF_IIC_Wait_Ack(void);
void PCF_IIC_Ack(void);
void PCF_IIC_NAck(void);  
void PCF_IIC_Send_Byte(uint8_t txd);    
uint8_t PCF_IIC_Read_Byte(unsigned char ack);
uint8_t PCF8563_ReadOneByte(uint16_t ReadAddr);
void PCF8563_WriteOneByte(u8 WriteAddr,u8 DataToWrite);
void PCF8563_Read_Time(void);


#endif
