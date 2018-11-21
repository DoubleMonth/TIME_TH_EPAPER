#include "stm8l15x.h"
#include "user_usart.h"
#include "stdio.h"
#include "pcf8563_i2c.h"
#include "epdhardware.h"
#include "epdif.h"
#include "epd2in13.h"
#include "epdpaint.h"
#include "imagedata.h"

#define LED_GPIO_PORT  GPIOD
#define LED_GPIO_PINS  (GPIO_Pin_4 | GPIO_Pin_1)
extern uint8_t time_buf1[8];
unsigned char frame_buffer[1024] = {0};
char time_string[] = {'0', '0', ':', '0', '0', '\0'};
/* Private variables ---------------------------------------------------------*/
#define COLORED      0
#define UNCOLORED    1
void delay(uint32_t time)
{
    uint32_t i,j;
    for(i=0;i<time;i++)
    {
        for(j=0;j<1000;j++)
        ;   
    }    
}
int main(void)
{
     CLK_HSICmd(ENABLE);
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);

    uart1Init();
    enableInterrupts();
    userI2CInit();
    
    EpdInitCallback();
    epdGPIOInit();
    epd_Init();
    uint8_t time;
    printf("e-Paper timer init finshed!\n");
    
    /*  2.13 epd */
    EPD epd;
  if (EPD_Init(&epd, lut_full_update) != 0) {
    printf("e-Paper init failed\n");
    return -1;
  }
  
  EPD_ClearFrameMemory(&epd, 0xFF);
  
  Paint paint;
  Paint_Init (&paint, frame_buffer, 128, 60);
  
  Paint_Clear(&paint, UNCOLORED);
  Paint_DrawStringAt(&paint, 0, 0, "e-Paper Demo", &Font12, COLORED);
  EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, 128, 24);

  Paint_Clear(&paint, UNCOLORED);
  Paint_DrawStringAt(&paint, 0, 0, "Hello Kit!", &Font12, COLORED);
  EPD_SetFrameMemory(&epd, frame_buffer, 0, 12, 128, 24);
  
  
  Paint_Init (&paint, frame_buffer, 64, 64);
  Paint_Clear(&paint, UNCOLORED);
//  Paint_Init (&paint, frame_buffer, 64, 64);
  /* Draw something to the frame buffer */
  Paint_DrawRectangle(&paint, 0, 0, 40, 50, COLORED);
  Paint_DrawLine(&paint, 0, 0, 40, 50, COLORED);
  Paint_DrawLine(&paint, 40, 0, 0, 50, COLORED);
//  Paint_DrawCircle(&paint, 88, 80, 30, COLORED);
//  Paint_DrawFilledRectangle(&paint, 10, 120, 50, 180, COLORED);
//  Paint_DrawFilledCircle(&paint, 88, 150, 30, COLORED);
  
  EPD_SetFrameMemory(&epd, frame_buffer, 0, 24, 64, 64);
  
  EPD_DisplayFrame(&epd);
  EPD_DelayMs(&epd, 2000);

  if (EPD_Init(&epd, lut_partial_update) != 0) {
    printf("e-Paper init failed\n");
    return -1;
  }
  
  Paint_Init (&paint, frame_buffer, 64, 64);
  Paint_Clear(&paint, UNCOLORED);
  EPD_SetFrameMemory(&epd, IMAGE_DATA, 0, 0, epd.width, epd.height);
  EPD_DisplayFrame(&epd);
  EPD_SetFrameMemory(&epd, IMAGE_DATA, 0, 0, epd.width, epd.height);
  EPD_DisplayFrame(&epd);
  /* Infinite loop */
    while (1)
    {
        delay(70);
        PCF8563_Read_Time();
        printf("%d%d%d%dÄê%d%dÔÂ%d%dÈÕ\r\n",time_buf1[0]/10,time_buf1[0]%10,time_buf1[1]/10,time_buf1[1]%10,time_buf1[2]/10,time_buf1[2]%10,time_buf1[3]/10,time_buf1[3]%10);
	printf("%d%d:%d%d:%d%d\r\n",time_buf1[4]/10,time_buf1[4]%10,time_buf1[5]/10,time_buf1[5]%10,time_buf1[6]/10,time_buf1[6]%10);
        
        /*
       time_buf1[5]++;
       time_buf1[6]++;
    time_string[0] = time_buf1[5] / 10 + '0';
    time_string[1] = time_buf1[5]  % 10 + '0';
    time_string[3] = time_buf1[6] / 10 + '0';
    time_string[4] = time_buf1[6] % 10 + '0';
  
    Paint_SetWidth(&paint, 32);
    Paint_SetHeight(&paint, 96);
    Paint_SetRotate(&paint, ROTATE_90);

    Paint_Clear(&paint, UNCOLORED);
    Paint_DrawStringAt(&paint, 0, 4, time_string, &Font24, COLORED);
    EPD_SetFrameMemory(&epd, frame_buffer, 80, 72, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
    EPD_DisplayFrame(&epd);
    if(time_buf1[5]>6)
    EPD_Sleep(&epd);
        */
    
    }
}