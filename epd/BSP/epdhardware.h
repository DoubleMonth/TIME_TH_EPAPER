#ifndef __EPDHARDWARE_H
#define __EPDHARDWARE_H
#include "stm8l15x.h"

#define DC_Pin GPIO_Pin_2
#define DC_GPIO_Port GPIOB
#define BUSY_Pin GPIO_Pin_0
#define BUSY_GPIO_Port GPIOB
#define RST_Pin GPIO_Pin_1
#define RST_GPIO_Port GPIOB
#define SPI_CS_Pin GPIO_Pin_4
#define SPI_CS_GPIO_Port GPIOB

 #define epd_SPI                       SPI1
 #define epd_SPI_CLK                   CLK_Peripheral_SPI1
 #define epd_SPI_SCK_PIN               GPIO_Pin_5                  /* PB.05 */
 #define epd_SPI_SCK_GPIO_PORT         GPIOB                       /* GPIOB */
 #define epd_SPI_MISO_PIN              GPIO_Pin_7                  /* PB.07 */
 #define epd_SPI_MISO_GPIO_PORT        GPIOB                       /* GPIOB */
 #define epd_SPI_MOSI_PIN              GPIO_Pin_6                  /* PB.06 */
 #define epd_SPI_MOSI_GPIO_PORT        GPIOB                       /* GPIOAB */
// #define epd_CS_PIN                    GPIO_Pin_4                  /* PE.04 */
// #define epd_CS_GPIO_PORT              GPIOE                       /* GPIOE */
#define epd_CS_HIGH()   GPIO_SetBits(SPI_CS_GPIO_Port, SPI_CS_Pin)
void epdGPIOInit(void);
void epd_Init(void);
uint8_t epd_SendByte(uint8_t byte);
#endif
