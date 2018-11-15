#include <stm8l15x.h>
#include "stm8l15x_usart.h"
#include "user_usart.h"
#include "stdio.h"
void uart1Init(void)
{
    USART_DeInit(USART1);
    
    /* Configure USART Tx as alternate function push-pull  (software pull up)*/
    GPIO_ExternalPullUpConfig(GPIOC, GPIO_Pin_3, ENABLE);
    /* Configure USART Rx as alternate function push-pull  (software pull up)*/
    GPIO_ExternalPullUpConfig(GPIOC, GPIO_Pin_2, ENABLE);
    CLK_PeripheralClockConfig(CLK_Peripheral_USART1, ENABLE);
    USART_Init(USART1,(uint32_t)115200,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No,(USART_Mode_Rx|USART_Mode_Tx));
    USART_ITConfig(USART1,(USART_IT_RXNE),ENABLE);
    USART_ITConfig(USART1,USART_IT_TC,DISABLE);
    USART_Cmd(USART1,ENABLE);
//    CLK_PeripheralClockConfig(CLK_Peripheral_USART1, DISABLE);
    
}
void usart1SendByte(uint8_t data)
{
    USART1->DR = data;
    while(!(USART1->SR & USART_FLAG_TXE));
}
/*将Printf内容发往串口*/ 
int fputc(int ch, FILE *f)
{  
  USART1->DR=(unsigned char)ch;
  while (!(USART1->SR & USART_FLAG_TXE));
  return (ch);
}
