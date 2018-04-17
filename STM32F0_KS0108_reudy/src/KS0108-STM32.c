/*
 * KS0108-STM32.c
 *
 *  Created on: Apr 15, 2018
 *      Author: reudy15
 *
 *      Modify Universal KS0108 driver library
 *      **library was edit to make compatible with STM32f0 with CortexM0 processor
 *      **instead of using the stm32f10xx_lib.h the Hardware Abstraction Layer is used (HAL)
 *
 */

//-------------------------------------------------------------------------------------------------
// Universal KS0108 driver library
// STM32 MCU low-level driver
// (c) Rados≥aw KwiecieÒ, radek@dxp.pl
//-------------------------------------------------------------------------------------------------

#include "stm32f0xx.h"


#define KS0108_PORT  GPIOC

#define KS0108_RW    GPIO_PIN_11
#define KS0108_RS    GPIO_PIN_12
#define KS0108_EN    GPIO_PIN_13

#define KS0108_CS1   GPIO_PIN_9
#define KS0108_CS2   GPIO_PIN_8
#define KS0108_CS3   GPIO_PIN_10

#define KS0108_D0    0

#define DISPLAY_STATUS_BUSY	0x80

extern unsigned char screen_x;
extern unsigned char screen_y;

GPIO_InitTypeDef GPIO_InitStructure;



//-------------------------------------------------------------------------------------------------
// Delay function /for 8MHz/
//-------------------------------------------------------------------------------------------------
void GLCD_Delay(void)
{
  asm("nop");asm("nop");asm("nop");asm("nop");
}
//-------------------------------------------------------------------------------------------------
// Enalbe Controller (0-2)
//-------------------------------------------------------------------------------------------------
void GLCD_EnableController(unsigned char controller)
{
switch(controller){

	case 0 : HAL_GPIO_WritePin(KS0108_PORT, KS0108_CS1,GPIO_PIN_RESET); break;
	case 1 : HAL_GPIO_WritePin(KS0108_PORT, KS0108_CS2,GPIO_PIN_RESET); break;
	case 2 : HAL_GPIO_WritePin(KS0108_PORT, KS0108_CS3,GPIO_PIN_RESET); break;

	}
}
//-------------------------------------------------------------------------------------------------
// Disable Controller (0-2)
//-------------------------------------------------------------------------------------------------
void GLCD_DisableController(unsigned char controller)
{
switch(controller){
	case 0 : HAL_GPIO_WritePin(KS0108_PORT, KS0108_CS1,GPIO_PIN_SET); break;
	case 1 : HAL_GPIO_WritePin(KS0108_PORT, KS0108_CS2,GPIO_PIN_SET); break;
	case 2 : HAL_GPIO_WritePin(KS0108_PORT, KS0108_CS3,GPIO_PIN_SET); break;
	}
}
//-------------------------------------------------------------------------------------------------
// Read Status byte from specified controller (0-2)
//-------------------------------------------------------------------------------------------------
unsigned char GLCD_ReadStatus(unsigned char controller)
{
unsigned char status;

GPIO_InitStructure.Pin = GPIO_PIN_All;
GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_MEDIUM;
GPIO_InitStructure.Pull = GPIO_NOPULL;

GPIO_InitStructure.Pin = 0xFF << KS0108_D0;
GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
GPIO_InitStructure.Pull = GPIO_PULLUP;
HAL_GPIO_Init(KS0108_PORT, &GPIO_InitStructure);


HAL_GPIO_WritePin(KS0108_PORT, KS0108_RW,GPIO_PIN_SET);
HAL_GPIO_WritePin(KS0108_PORT, KS0108_RS,GPIO_PIN_RESET);

GLCD_EnableController(controller);
GLCD_Delay();
HAL_GPIO_WritePin(KS0108_PORT, KS0108_EN,GPIO_PIN_SET);
GLCD_Delay();
status = ((((uint16_t)KS0108_PORT->IDR) >> KS0108_D0) & 0xFF);
HAL_GPIO_WritePin(KS0108_PORT, KS0108_EN,GPIO_PIN_RESET);
GLCD_DisableController(controller);
return status;
}
//-------------------------------------------------------------------------------------------------
// Write command to specified controller
//-------------------------------------------------------------------------------------------------
void GLCD_WriteCommand(unsigned char commandToWrite, unsigned char controller)
{
//while(GLCD_ReadStatus(controller)&DISPLAY_STATUS_BUSY);

GPIO_InitStructure.Pin = GPIO_PIN_All;
GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_MEDIUM;
GPIO_InitStructure.Pull = GPIO_NOPULL;

GPIO_InitStructure.Pin  = (0xFF << KS0108_D0);
GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
HAL_GPIO_Init(KS0108_PORT, &GPIO_InitStructure);


HAL_GPIO_WritePin(KS0108_PORT, KS0108_RS | KS0108_RW,GPIO_PIN_RESET);
//HAL_GPIO_WritePin(KS0108_PORT, KS0108_RW,GPIO_PIN_RESET);
GLCD_Delay();
GLCD_EnableController(controller);
GLCD_Delay();
HAL_GPIO_WritePin(KS0108_PORT, (commandToWrite << KS0108_D0),GPIO_PIN_SET);
commandToWrite ^= 0xFF;
HAL_GPIO_WritePin(KS0108_PORT, (commandToWrite << KS0108_D0),GPIO_PIN_RESET);
GLCD_Delay();
HAL_GPIO_WritePin(KS0108_PORT, KS0108_EN,GPIO_PIN_SET);
GLCD_Delay();
HAL_GPIO_WritePin(KS0108_PORT, KS0108_EN,GPIO_PIN_RESET);
GLCD_Delay();
GLCD_DisableController(controller);
}

//-------------------------------------------------------------------------------------------------
// Read data from current position
//-------------------------------------------------------------------------------------------------
unsigned char GLCD_ReadData(void)
{
unsigned char tmp;
while(GLCD_ReadStatus(screen_x / 64)&DISPLAY_STATUS_BUSY);
GPIO_StructInit(&GPIO_InitStructure);
GPIO_InitStructure.Pin = 0xFF << KS0108_D0;
GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
GPIO_InitStructure.Pull = GPIO_PULLUP;
GPIO_Init(KS0108_PORT, &GPIO_InitStructure);

GPIO_SetBits(KS0108_PORT, KS0108_RS | KS0108_RW);

GLCD_EnableController(screen_x / 64);
GLCD_Delay();
GPIO_SetBits(KS0108_PORT, KS0108_EN);
GLCD_Delay();
tmp = ((GPIO_ReadInputData(KS0108_PORT) >> KS0108_D0) & 0xFF);
GPIO_ResetBits(KS0108_PORT, KS0108_EN);
GLCD_DisableController(screen_x / 64);
screen_x++;
return tmp;
}
//-------------------------------------------------------------------------------------------------
// Write data to current position
//-------------------------------------------------------------------------------------------------
void GLCD_WriteData(unsigned char dataToWrite)
{
//while(GLCD_ReadStatus(screen_x / 64)&DISPLAY_STATUS_BUSY);

GPIO_InitStructure.Pin = GPIO_PIN_All;
GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_MEDIUM;
GPIO_InitStructure.Pull = GPIO_NOPULL;

GPIO_InitStructure.Pin = (0xFF << KS0108_D0);
GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;

HAL_GPIO_Init(KS0108_PORT, &GPIO_InitStructure);

HAL_GPIO_WritePin(KS0108_PORT, KS0108_RW,GPIO_PIN_RESET);
GLCD_Delay();
HAL_GPIO_WritePin(KS0108_PORT, KS0108_RS,GPIO_PIN_SET);
GLCD_Delay();
HAL_GPIO_WritePin(KS0108_PORT, (dataToWrite << KS0108_D0),GPIO_PIN_SET);
dataToWrite ^= 0xFF;
HAL_GPIO_WritePin(KS0108_PORT, (dataToWrite << KS0108_D0),GPIO_PIN_RESET);
GLCD_Delay();
GLCD_EnableController(screen_x / 64);
GLCD_Delay();
HAL_GPIO_WritePin(KS0108_PORT, KS0108_EN,GPIO_PIN_SET);
GLCD_Delay();
HAL_GPIO_WritePin(KS0108_PORT, KS0108_EN,GPIO_PIN_RESET);
GLCD_Delay();
GLCD_DisableController(screen_x / 64);
screen_x++;
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_InitializePorts(void)
{
uint32_t i;

__HAL_RCC_GPIOC_CLK_ENABLE();
GPIO_InitStructure.Pin = GPIO_PIN_All;
GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_MEDIUM;
GPIO_InitStructure.Pull = GPIO_NOPULL;

GPIO_InitStructure.Pin   =  GPIO_PIN_All;
GPIO_InitStructure.Speed =  GPIO_SPEED_FREQ_LOW ;
GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;


HAL_GPIO_Init(KS0108_PORT, &GPIO_InitStructure);
KS0108_PORT->ODR |= KS0108_CS1 | KS0108_CS2 | KS0108_CS3 | KS0108_RS | KS0108_RW | (0xFF << KS0108_D0);
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
unsigned char GLCD_ReadByteFromROMMemory(char * ptr)
{
  return *(ptr);
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------


