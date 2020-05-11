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
	const uint8_t 	byteOffset = coords.a % 8;
	uint8_t 		*saved = _glcd_gbuf[coords.a / 8][coords.b];
	*saved = setBit(*saved, byteOffset, state);
}


/*
* Function: GLCDSwapBuffers
* Desc:     поменять буфферы битов местами
* Input:    none
* Output:   none
*/
void GLCDSwapBuffers(void)
{
	if(_glcd_gbuf == (uint8_t***)&_glcd_gbuf_0)
		_glcd_gbuf = (uint8_t***)&_glcd_gbuf_1;
	else
		_glcd_gbuf = (uint8_t***)&_glcd_gbuf_0;
}


/*
* Function: GLCDDrawPixmap
* Desc:     Нарисовать картинку на текущем полотне
* Input:    coords: координаты левого верхнего угла
*			size: 	размер картинки
*			pixmap: указатель на картинку
* Output:   none
*/
void GLCDDrawPixmap(const vect coords, const vect size, const uint8_t** pixmap)
{
	for(uint8_t x_px = 0; x_px < size.a * 8; x_px++)
	{
		const uint8_t 	x_byte = x_px / 8,
						x_byte_offset = (uint8_t)(x_px - x_byte);
		for(uint8_t y_px = 0; y_px < size.b; y_px++)
		{
			GLCDSetPixel((const vect){	(uint8_t)(coords.a + x_px), 
										(uint8_t)(coords.b + y_px)}, 
							getBit(pixmap[x_byte][y_px], x_byte_offset));
		}
	}
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
	GLCDDrawPixmap(coords, (const vect){1, 8}, (const uint8_t**)&Font8x8[(int)c]);
}

/*
* Function: GLCDDrawText
* Desc:     Нарисовать текст на текущем полотне
* Input:    coords: координаты левого верхнего угла текста
*			text:	строка
* Output:   none
*/
void GLCDDrawText(const vect coords, const char* text)
{
	vect pointerCoords = coords;
	while(*text)
	{
		GLCDDrawSymbol(pointerCoords, *text);
		if(*text != '\n')
			pointerCoords.a = (uint8_t)(pointerCoords.a + 8);
		else
		{
			pointerCoords.a = coords.a;
			pointerCoords.b = (uint8_t)(pointerCoords.b + 8);
		}
		text++;
	}
}


/*
* Function: GLCDOn
* Desc:     Отправить команду на включение экрана
* Input:    none
* Output:   none
*/
void GLCDOn()
{
	turnPortOff(&GLCD_SPORT, (1 << GLCD_RS) | (1  << GLCD_RW));
	GLCD_DPORT = (0 << 7) | (0 << 6) | (1 << 5) | (1 << 4) | (1 << 3) | (1 << 2) | (1 << 1) | (1 << 0);
	_delay_ms(1);
	GLCD_DPORT = 0;
}


/*
* Function: GLCDSetX
* Desc:     Записать в регистр координаты X
* Input:    x: координата, [0; 7]
* Output:   none
*/
void GLCDSetX(const uint8_t x)
{
	turnPortOff(&GLCD_SPORT, (1 << GLCD_RS) | (1  << GLCD_RW));
	GLCD_DPORT = (1 << 7) | (0 << 6) | (1 << 5) | (1 << 4) | (1 << 3) | x;
	_delay_us(140);
	GLCD_DPORT = 0;
}

/*
* Function: GLCDSetY
* Desc:     Записать в регистр координаты Y
* Input:    y: координата, [0; 63]
* Output:   none
*/
void GLCDSetY(const uint8_t y)
{
	turnPortOff(&GLCD_SPORT, (1 << GLCD_RS) | (1  << GLCD_RW));
	GLCD_DPORT = (0 << 7) | (1 << 6) | y;
	_delay_us(140);
	GLCD_DPORT = 0;
}

/*
* Function: GLCDWriteData
* Desc:     Записать в память данные
* Input:    data: данные
* Output:   none
*/
void GLCDWriteData(const uint8_t data)
{
	turnPortOn(&GLCD_SPORT, 1 << GLCD_RS);
	turnPortOff(&GLCD_SPORT, 1 << GLCD_RW);
	GLCD_DPORT = data;
	_delay_us(150);
	GLCD_DPORT = 0;
}


/*
* Function: GLCDDrawScren
* Desc:     Отобразить графический буффер на экран
* Input:    none
* Output:   none
*/
void GLCDDrawScren(void)
{

	for(uint8_t i = 0; i < 64; i++)
	{
		GLCDSetY(i);
		for(uint8_t j = 0; j < 8; j++)
		{
			GLCDSetX(j);
			GLCDWriteData(*_glcd_gbuf[j][i]);
		}
	}
}
