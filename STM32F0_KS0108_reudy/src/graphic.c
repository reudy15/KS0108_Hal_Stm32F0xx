/*
 * graphic.c
 *
 *  Created on: Apr 16, 2018
 *      Author: reudy15
 */


extern void GLCD_SetPixel(unsigned char x, unsigned char y, unsigned char color);

const unsigned char color = 1;

void GLCD_Rectangle(unsigned char x, unsigned char y, unsigned char b, unsigned char a)
{
  unsigned char j; // zmienna pomocnicza
  // rysowanie linii pionowych (boki)
  for (j = 0; j < a; j++) {
		GLCD_SetPixel(x, y + j, color);
		GLCD_SetPixel(x + b - 1, y + j, color);
	}
  // rysowanie linii poziomych (podstawy)
  for (j = 0; j < b; j++)	{
		GLCD_SetPixel(x + j, y, color);
		GLCD_SetPixel(x + j, y + a - 1, color);
	}
}
//

void GLCD_Circle(unsigned char cx, unsigned char cy ,unsigned char radius)
{
int x, y, xchange, ychange, radiusError;
x = radius;
y = 0;
xchange = 1 - 2 * radius;
ychange = 1;
radiusError = 0;
while(x >= y)
  {
  GLCD_SetPixel(cx+x, cy+y, color);
  GLCD_SetPixel(cx-x, cy+y, color);
  GLCD_SetPixel(cx-x, cy-y, color);
  GLCD_SetPixel(cx+x, cy-y, color);
  GLCD_SetPixel(cx+y, cy+x, color);
  GLCD_SetPixel(cx-y, cy+x, color);
  GLCD_SetPixel(cx-y, cy-x, color);
  GLCD_SetPixel(cx+y, cy-x, color);
  y++;
  radiusError += ychange;
  ychange += 2;
  if ( 2*radiusError + xchange > 0 )
    {
    x--;
	radiusError += xchange;
	xchange += 2;
	}
  }
}
//

void GLCD_Line(unsigned int X1,unsigned int Y1,unsigned int X2,unsigned int Y2)
{
int CurrentX, CurrentY, Xinc, Yinc,
    Dx, Dy, TwoDx, TwoDy,
	TwoDxAccumulatedError, TwoDyAccumulatedError;

Dx = (X2-X1); // obliczenie sk≥adowej poziomej
Dy = (Y2-Y1); // obliczenie sk≥adowej pionowej

TwoDx = Dx + Dx; // podwojona sk≥adowa pozioma
TwoDy = Dy + Dy; // podwojona sk≥adowa pionowa

CurrentX = X1; // zaczynamy od X1
CurrentY = Y1; // oraz Y1

Xinc = 1; // ustalamy krok zwiÍkszania pozycji w poziomie
Yinc = 1; // ustalamy krok zwiÍkszania pozycji w pionie

if(Dx < 0) // jesli sk≥adowa pozioma jest ujemna
  {
  Xinc = -1; // to bÍdziemy siÍ "cofaÊ" (krok ujemny)
  Dx = -Dx;  // zmieniamy znak sk≥adowej na dodatni
  TwoDx = -TwoDx; // jak rÛwnieø podwojonej sk≥adowej
  }

if (Dy < 0) // jeúli sk≥adowa pionowa jest ujemna
  {
  Yinc = -1; // to bÍdziemy siÍ "cofaÊ" (krok ujemny)
  Dy = -Dy; // zmieniamy znak sk≥adowej na dodatki
  TwoDy = -TwoDy; // jak rÛwniez podwojonej sk≥adowej
  }

GLCD_SetPixel(X1,Y1, color); // stawiamy pierwszy krok (zapalamy pierwszy piksel)

if ((Dx != 0) || (Dy != 0)) // sprawdzamy czy linia sk≥ada siÍ z wiÍcej niø jednego punktu ;)
  {
  // sprawdzamy czy sk≥adowa pionowa jest mniejsza lub rÛwna sk≥adowej poziomej
  if (Dy <= Dx) // jeúli tak, to idziemy "po iksach"
    {
    TwoDxAccumulatedError = 0; // zerujemy zmiennπ
    do // ruszamy w drogÍ
	  {
      CurrentX += Xinc; // do aktualnej pozycji dodajemy krok
      TwoDxAccumulatedError += TwoDy; // a tu dodajemy podwojonπ sk≥adowπ pionowπ
      if(TwoDxAccumulatedError > Dx)  // jeúli TwoDxAccumulatedError jest wiÍkszy od Dx
        {
        CurrentY += Yinc; // zwiÍkszamy aktualnπ pozycjÍ w pionie
        TwoDxAccumulatedError -= TwoDx; // i odejmujemy TwoDx
        }
       GLCD_SetPixel(CurrentX,CurrentY, color);// stawiamy nastÍpny krok (zapalamy piksel)
       }while (CurrentX != X2); // idziemy tak d≥ugo, aø osiπgniemy punkt docelowy
     }
   else // w przeciwnym razie idziemy "po igrekach"
      {
      TwoDyAccumulatedError = 0;
      do
	    {
        CurrentY += Yinc;
        TwoDyAccumulatedError += TwoDx;
        if(TwoDyAccumulatedError>Dy)
          {
          CurrentX += Xinc;
          TwoDyAccumulatedError -= TwoDy;
          }
         GLCD_SetPixel(CurrentX,CurrentY, color);
         }while (CurrentY != Y2);
    }
  }
}
//
