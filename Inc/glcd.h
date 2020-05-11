#ifndef __GLCD_H__
#define __GLCD_H__

#include "main.h"
#include "font.h"
#include <util/atomic.h>
#include <util/delay.h>

#define GLCD_WIDTH 128
#define GLCD_WIDTH_DWORD (GLCD_WIDTH / 8)
#define GLCD_HEIGHT 64
#define GLCD_HEIGHT_DWORD (GLCD_HEIGHT / 8)

#define GLCD_CS1 	PE2
#define GLCD_CS2 	PE3
			/*RS=D/I*/
#define GLCD_RS  	PE4
#define GLCD_RW  	PE5
#define GLCD_E  	PE6
#define GLCD_RST  	PE7
			/*порт управления*/
#define GLCD_SPORT	PORTE
			/*порт данных*/
#define GLCD_DPORT  PORTA

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
* Desc:     Поменять буфферы битов местами
* Input:    none
* Output:   none
*/
void GLCDSwitchBuffers(void);

/*
* Function: GLCDDrawPixmap
* Desc:     Нарисовать картинку на текущем полотне
* Input:    coords: координаты левого верхнего угла
*			size: 	размер картинки
*			pixmap: указатель на картинку
* Output:   none
*/
void GLCDDrawPixmap(const vect coords, const vect size, const uint8_t** pixmap);

/*
* Function: GLCDDrawSymbol
* Desc:     Нарисовать символ на текущем полотне
* Input:    coords: координаты левого верхнего угла символа
*			c:	символ
* Output:   none
*/
void GLCDDrawSymbol(const vect coords, const char c);

/*
* Function: GLCDDrawText
* Desc:     Нарисовать текст на текущем полотне
* Input:    coords: координаты левого верхнего угла текста
*			text:	строка
* Output:   none
*/
void GLCDDrawText(const vect coords, const char* text);

/*
* Function: GLCDDrawTextScaled
* Desc:     Нарисовать текст на текущем полотне
* Input:    coords: координаты левого верхнего угла текста
*			scaleFactor: размер увеличения текста
*			text:	строка
* Output:   none
*/
void GLCDDrawTextScaled(const vect coords, uint8_t scaleFactor, const char* text);

/*
* Function: GLCDOn
* Desc:     Отправить команду на включение экрана
* Input:    none
* Output:   none
*/
void GLCDOn();

/*
* Function: GLCDDrawGBuf
* Desc:     Отрисовать графический буффер
* Input:    none
* Output:   none
*/
void GLCDDrawGBuf();

/*
* Function: GLCDSetX
* Desc:     Записать в регистр координаты X
* Input:    x: координата, [0; 7]
* Output:   none
*/
void GLCDSetX(const uint8_t x);

/*
* Function: GLCDSetY
* Desc:     Записать в регистр координаты Y
* Input:    y: координата, [0; 63]
* Output:   none
*/
void GLCDSetY(const uint8_t y);



#endif