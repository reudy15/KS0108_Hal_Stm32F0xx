/*
 * KS0108.c
 *
 *  Created on: Apr 15, 2018
 *      Author: reudy15
 *      Not created to modified by me
 */

//-------------------------------------------------------------------------------------------------
// Graphic LCD C library
// (c) Rados≥aw KwiecieÒ, radek@dxp.pl
//-------------------------------------------------------------------------------------------------
#include "KS0108.h"
#include "font5x8.h"
//-------------------------------------------------------------------------------------------------
// Reference to MCU-specific external functions
//-------------------------------------------------------------------------------------------------
extern void GLCD_InitializePorts(void);
extern void GLCD_WriteData(unsigned char);
extern void GLCD_WriteCommand(unsigned char, unsigned char);
extern unsigned char GLCD_ReadData(void);
extern unsigned char GLCD_ReadStatus(unsigned char);
//-------------------------------------------------------------------------------------------------
unsigned char screen_x = 0, screen_y = 0; // screen coordinates
//-------------------------------------------------------------------------------------------------
// Initialization interface and LCD controller
//-------------------------------------------------------------------------------------------------
void GLCD_Initialize(void)
{
unsigned char i;
GLCD_InitializePorts();
for(i = 0; i < 3; i++)
  GLCD_WriteCommand((DISPLAY_ON_CMD | ON), i);
}
//-------------------------------------------------------------------------------------------------
// Sets screen coordinates and address
//-------------------------------------------------------------------------------------------------
void GLCD_GoTo(unsigned char x, unsigned char y)
{
unsigned char i;
screen_x = x;
screen_y = y;

for(i = 0; i < KS0108_SCREEN_WIDTH/64; i++)
  {
  GLCD_WriteCommand(DISPLAY_SET_Y | 0,i);
  GLCD_WriteCommand(DISPLAY_SET_X | y,i);
  GLCD_WriteCommand(DISPLAY_START_LINE | 0,i);
  }
GLCD_WriteCommand((DISPLAY_SET_Y | (x % 64)), (x / 64));
GLCD_WriteCommand((DISPLAY_SET_X | y), (x / 64));
}
//-------------------------------------------------------------------------------------------------
// Sets text coordinates and address
//-------------------------------------------------------------------------------------------------
void GLCD_TextGoTo(unsigned char x, unsigned char y)
{
GLCD_GoTo(x*6,y);
}
//-------------------------------------------------------------------------------------------------
// Clears screen
//-------------------------------------------------------------------------------------------------
void GLCD_ClearScreen(void)
{
unsigned char i, j;
for(j = 0; j < KS0108_SCREEN_HEIGHT/8; j++)
	{
	GLCD_GoTo(0,j);
	for(i = 0; i < KS0108_SCREEN_WIDTH; i++)
 		GLCD_WriteData(0x00);
	}
}
//-------------------------------------------------------------------------------------------------
// Writes char to screen memory
//-------------------------------------------------------------------------------------------------
void GLCD_WriteChar(char charToWrite)
{
char i;
charToWrite -= 32;
for(i = 0; i < 5; i++)
  GLCD_WriteData(GLCD_ReadByteFromROMMemory((char *)(font5x8 + (5 * charToWrite) + i)));
GLCD_WriteData(0x00);
}
//-------------------------------------------------------------------------------------------------
// Write null-terminated string to screen memory
//-------------------------------------------------------------------------------------------------
void GLCD_WriteString(char * stringToWrite)
{
while(*stringToWrite)
  GLCD_WriteChar(*stringToWrite++);
}
//-------------------------------------------------------------------------------------------------
// Sets or clears pixel at (x,y)
//-------------------------------------------------------------------------------------------------
void GLCD_SetPixel(unsigned char x, unsigned char y, unsigned char color)
{
unsigned char tmp;
GLCD_GoTo(x, y/8);
tmp = GLCD_ReadData();
GLCD_GoTo(x, y/8);
tmp = GLCD_ReadData();
GLCD_GoTo(x, y/8);
if(color)
	tmp |= (1 << (y%8));
else
	tmp &= ~(1 << (y%8));
GLCD_WriteData(tmp);
}
//-------------------------------------------------------------------------------------------------
// Displays bitmap at (x,y) and (dx,dy) size
//-------------------------------------------------------------------------------------------------
void GLCD_Bitmap(char * bmp, unsigned char x, unsigned char y, unsigned char dx, unsigned char dy)
{
unsigned char i, j;
for(j = 0; j < dy / 8; j++)
  {
  GLCD_GoTo(x,y + j);
  for(i = 0; i < dx; i++)
    GLCD_WriteData(GLCD_ReadByteFromROMMemory(bmp++));
  }
}
//-------------------------------------------------------------------------------------------------
// End of file KS0108.c
//-------------------------------------------------------------------------------------------------






