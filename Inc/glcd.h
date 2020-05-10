#ifndef __GLCD_H__
#define __GLCD_H__

#include "main.h"

#define GLCD_WIDTH 128
#define GLCD_WIDTH_DWORD (GLCD_WIDTH / 8)
#define GLCD_HEIGHT 64
#define GLCD_HEIGHT_DWORD (GLCD_HEIGHT / 8)

					/*нулевой массив битов*/
extern uint8_t 		_glcd_gbuf_0[GLCD_WIDTH_DWORD][GLCD_HEIGHT],	
					/*первый мссив битов*/
					_glcd_gbuf_1[GLCD_WIDTH_DWORD][GLCD_HEIGHT];	
					/*указатель на текущий массив битов для двойной буфферизации*/
extern uint8_t*** 	_glcd_gbuf;				


/*
* Function: GLCDSetPixel
* Desc:     Установить пиксель с координатами {x,y} в состояние state
* Input:    coords: координаты вектора
*			state: в какое состояние установить пиксель
* Output:   none
*/
void GLCDSetPixel(const vect coords, const bool state);

/*
* Function: GLCDSwitchBuffers
* Desc:     поменять буфферы битов местами
* Input:    none
* Output:   none
*/
void GLCDSwitchBuffers(void);

#endif