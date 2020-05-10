#ifndef __GLCD_H__
#define __GLCD_H__

#include "main.h"

extern uint8_t 		_glcd_gbuf_0[16][8],	/*нулевой массив битов */
					_glcd_gbuf_1[16][8];	/*первый мссив битов*/
extern uint8_t*** 	_glcd_gbuf;				/*указатель на текущий массив битов для двойной буфферизации*/

/*
* Function: GLCDSetPixel
* Desc:     Установить пиксель с координатами {x,y} в состояние state
* Input:    x: x координата пикселя
*			y: y координата пикселя
*			state: в какое состояние установить пиксель
* Output:   none
*/
void GLCDSetPixel(uint8_t x, uint8_t y, bool state);

#endif