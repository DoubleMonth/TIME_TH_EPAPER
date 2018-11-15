#include "epdhardware.h"


void epdGPIOInit(void)
{
    GPIO_Init(DC_GPIO_Port, DC_Pin, GPIO_Mode_Out_PP_High_Fast);
    GPIO_Init(BUSY_GPIO_Port, BUSY_Pin, GPIO_Mode_Out_PP_High_Fast);
    GPIO_Init(RST_GPIO_Port, RST_Pin, GPIO_Mode_Out_PP_High_Fast);
    GPIO_Init(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_Mode_Out_PP_High_Fast);
    
}

 void epd_LowLevel_DeInit(void)
 {
   /*!< Disable the epd_SPI  */
   SPI_Cmd(epd_SPI, DISABLE);
 
   /*!< epd_SPI Periph clock disable */
   CLK_PeripheralClockConfig(epd_SPI_CLK, DISABLE);
 
   /*!< Configure epd_SPI pins: SCK */
   GPIO_Init(epd_SPI_SCK_GPIO_PORT, epd_SPI_SCK_PIN, GPIO_Mode_In_FL_No_IT);
 
   /*!< Configure epd_SPI pins: MISO */
   GPIO_Init(epd_SPI_MISO_GPIO_PORT, epd_SPI_MISO_PIN, GPIO_Mode_In_FL_No_IT);
 
   /*!< Configure epd_SPI pins: MOSI */
   GPIO_Init(epd_SPI_MOSI_GPIO_PORT, epd_SPI_MOSI_PIN, GPIO_Mode_In_FL_No_IT);
 
   /*!< Configure epd_CS_PIN pin: epd Card CS pin */
   GPIO_Init(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_Mode_In_FL_No_IT);
 }
void epd_LowLevel_Init(void)
{
    CLK_PeripheralClockConfig(epd_SPI_CLK, ENABLE);
    GPIO_ExternalPullUpConfig(epd_SPI_SCK_GPIO_PORT, epd_SPI_SCK_PIN | \
                             epd_SPI_MISO_PIN | epd_SPI_MOSI_PIN, ENABLE);
    GPIO_Init(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_Mode_Out_PP_High_Fast);
}
void epd_Init(void)
{
    epd_LowLevel_Init();
    epd_CS_HIGH();
    SPI_Init(epd_SPI, SPI_FirstBit_MSB, SPI_BaudRatePrescaler_4, SPI_Mode_Master,
            SPI_CPOL_Low, SPI_CPHA_1Edge, SPI_Direction_2Lines_FullDuplex,
            SPI_NSS_Soft, 0x07);
 
   /* Enable SPI  */
   SPI_Cmd(epd_SPI, ENABLE);

}

 uint8_t epd_SendByte(uint8_t byte)
 {
   /* Loop while DR register in not emplty */
   while (SPI_GetFlagStatus(epd_SPI, SPI_FLAG_TXE) == RESET);
 
   /* Send byte through the SPI peripheral */
   SPI_SendData(epd_SPI, byte);
 
   /* Wait to receive a byte */
   while (SPI_GetFlagStatus(epd_SPI, SPI_FLAG_RXNE) == RESET);
 
   /* Return the byte read from the SPI bus */
   return SPI_ReceiveData(epd_SPI);
 }

