
#include <stdio.h>

#include "gba.h"
#include "screenmodes.h"

/* 2 images generated with bitmap.c */
#include "img.h"
#include "img1.h"

/* Image size */
#define   SIZE_X    124
#define   SIZE_Y    155


u16* theVideoBuffer = (u16*)VideoBuffer;


u16
average(u16 c1, u16 c2, s8 alfa)
{
    u16 r, g, b;

    b = ( alfa*(c1 & 31) + (100-alfa)*(c2 & 31) ) / 200;
    g = ( alfa*((c1 >> 5) & 31) + (100-alfa)*((c2 >> 5) & 31) ) / 200;
    r = ( alfa*((c1 >> 10) & 31) + (100-alfa)*((c2 >> 10) & 31) ) / 200;

    return ( (r << 10) + (g << 5) + b );
}


void
drawImage(const u16 img[SIZE_Y][SIZE_X], u8 pad_x, u8 pad_y)
{
    u8 x = pad_x;
    u8 y = pad_y;
    s16 i, j;

    for(i = SIZE_Y-1; i >= 0; i--)  {
        for(j = 0; j < SIZE_X; j++)  {
            VideoBuffer[x + y * _X_RES_] = img[i][j];
            x++;
        }
        x = pad_x;
        y++;
    }
}


int
main(void)
{
    SetMode( SCREENMODE3 | BG2ENABLE ); 

    s16 i, j;
    u8 x, y;

    s8 alfa;

    drawImage(img, 10, 3);

    alfa = 100;
    while(alfa >= 0)  {
        x = 10;
        y = 3;
        for(i = 154; i >= 0; i--)  {
            for(j = 0; j < 124; j++)  {
                VideoBuffer[x + y * _X_RES_] = average(img[i][j], img1[i][j], alfa);
                x++;
            }
            x = 10;
            y++;
        }

        alfa -= 20;
    }

    drawImage(img1, 10, 3);

    return 0;
}
