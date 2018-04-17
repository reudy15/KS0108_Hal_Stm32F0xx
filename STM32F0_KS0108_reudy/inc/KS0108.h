/*
 * KS0108.h
 *
 *  Created on: Apr 15, 2018
 *      Author: reudy15
 */

#define KS0108_SCREEN_WIDTH	128
#define KS0108_SCREEN_HEIGHT	64


#define DISPLAY_SET_Y       0x40
#define DISPLAY_SET_X       0xB8
#define DISPLAY_START_LINE  0xC0
#define DISPLAY_ON_CMD		0x3E
  #define ON	0x01
  #define OFF	0x00
#define DISPLAY_STATUS_BUSY	0x80
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_Initialize(void);
void GLCD_WriteData(unsigned char);
void GLCD_ClearScreen(void);
void GLCD_TextGoTo(unsigned char, unsigned char);
void GLCD_GoTo(unsigned char, unsigned char);
void GLCD_WriteString(char *);
unsigned char GLCD_ReadByteFromROMMemory(char *);
//-------------------------------------------------------------------------------------------------
// End of file KS0108.h
//-------------------------------------------------------------------------------------------------



