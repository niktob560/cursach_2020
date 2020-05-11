#include "glcd.h"

			/*нулевой массив битов*/
uint8_t 	_glcd_gbuf_0[GLCD_WIDTH_DWORD][GLCD_HEIGHT] = {{0}},
			/*первый мссив битов*/
			_glcd_gbuf_1[GLCD_WIDTH_DWORD][GLCD_HEIGHT] = {{0}};
			/*указатель на текущий массив битов для двойной буфферизации*/
uint8_t*** 	_glcd_gbuf = (uint8_t***)&_glcd_gbuf_0;	/*указатель на текущий массив битов для двойной буфферизации*/



/*
* Function: GLCDSetPixel
* Desc:     Установить пиксель с координатами {x,y} в состояние state
* Input:    coords: координаты вектора
*			state: в какое состояние установить пиксель
* Output:   none
*/
void GLCDSetPixel(const vect coords, const bool state)
{
	*_glcd_gbuf[coords.a / GLCD_WIDTH_DWORD][coords.b] = (uint8_t)(state >> (coords.a % GLCD_WIDTH_DWORD));
}


/*
* Function: GLCDSwitchBuffers
* Desc:     поменять буфферы битов местами
* Input:    none
* Output:   none
*/
void GLCDSwitchBuffers(void)
{
	if(_glcd_gbuf == (uint8_t***)&_glcd_gbuf_0)
		_glcd_gbuf = (uint8_t***)&_glcd_gbuf_1;
	else
		_glcd_gbuf = (uint8_t***)&_glcd_gbuf_0;
}



/*
* Function: GLCDDrawSymbol
* Desc:     Нарисовать символ на текущем полотне
* Input:    coords: координаты левого верхнего угла символа
*			c:	символ
* Output:   none
*/
void GLCDDrawSymbol(const vect coords, const char c)
{
	for(uint8_t i = 0; i < 8; i++)
	{
		for (uint8_t j = 0; j < 8; ++j)
		{
			*_glcd_gbuf[coords.a / 8][coords.b + i] = setBit(*_glcd_gbuf[coords.a / 8][coords.b + i], j, getBit((uint8_t)c, j));
		}
	}
}