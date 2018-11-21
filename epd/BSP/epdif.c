/**
 *  @filename   :   epdif.c
 *  @brief      :   Implements EPD interface functions
 *                  Users have to implement all the functions in epdif.cpp
 *  @author     :   Yehui from Waveshare
 *
 *  Copyright (C) Waveshare     July 7 2017
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documnetation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to  whom the Software is
 * furished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "epdif.h"
#include "epdhardware.h"

EPD_Pin epd_cs_pin = {
  SPI_CS_GPIO_Port,
  SPI_CS_Pin,
};

EPD_Pin epd_rst_pin = {
  RST_GPIO_Port,
  RST_Pin,
};

EPD_Pin epd_dc_pin = {
  DC_GPIO_Port,
  DC_Pin,
};

EPD_Pin epd_busy_pin = {
  BUSY_GPIO_Port,
  BUSY_Pin,
};

EPD_Pin pins[4];

void EpdDigitalWriteCallback(int pin_num, int value) {
  if (value == HIGH) {
    GPIO_WriteBit((GPIO_TypeDef*) pins[pin_num].port,  pins[pin_num].pin, SET);
  } else {
    GPIO_WriteBit((GPIO_TypeDef*) pins[pin_num].port,  pins[pin_num].pin, RESET);
  }
}

int EpdDigitalReadCallback(int pin_num) {
  if ( GPIO_ReadInputDataBit((GPIO_TypeDef*) pins[pin_num].port, pins[pin_num].pin) == SET ) {
    return HIGH;
  } else {
    return LOW;
  }
}
void epd_Delay(uint32_t nCount)
{
   /* Decrement nCount value */
  uint32_t i;
   while (nCount > 0)
   {
 //    for(i=0;i<20;i++)
 //      ;
     nCount--;
   }
}

void EpdDelayMsCallback(unsigned int delaytime) {
  epd_Delay(delaytime);
}

void EpdSpiTransferCallback(unsigned char data) {
  GPIO_WriteBit((GPIO_TypeDef*) pins[CS_PIN].port,  pins[CS_PIN].pin, RESET);
  epd_SendByte(data);
  GPIO_WriteBit((GPIO_TypeDef*) pins[CS_PIN].port,  pins[CS_PIN].pin, SET);
}

int EpdInitCallback(void) {
  pins[CS_PIN] = epd_cs_pin;
  pins[RST_PIN] = epd_rst_pin;
  pins[DC_PIN] = epd_dc_pin;
  pins[BUSY_PIN] = epd_busy_pin;
  
  return 0;
}

