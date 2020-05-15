#ifndef __GLCD_H__
#define __GLCD_H__ 1

#include <main.h>
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




/*
* Function: GLCDWriteCommand
* Desc:     Отправить команду записи
* Input:    cs1:	состояние CS1
*			cs2:	состояние CS2
*			rs:		состояние RS
*			rw:		состояние R/W
*			data:	данные для записи
* Output:   none
*/
void GLCDWriteCommand(const bool cs1, const bool cs2, const bool rs, const bool rw, const uint8_t data);


/*
* Function: GLCDReadCommand
* Desc:     Отправить команду чтения
* Input:    isCS1:	состояние CS1
*			rs:		состояние RS
* Output:   прочитанный байт
*/
uint8_t GLCDReadCommand(const bool isCS1, const bool rs);


/*
* Function: GLCDSetPixel
* Desc:     Установить пиксель с координатами {x,y}
* Input:    coords: координаты вектора
*			pixels: пиксели
* Output:   none
*/
void GLCDSetPixel(const vect coords, const bool state);

/*
* Function: GLCDSet8Pixels
* Desc:     Установить 8 пикселей с координатами {x,y}
* Input:    coords: координаты вектора
*			pixels: пиксели
* Output:   none
*/
void GLCDSet8Pixels(const vect coords, const uint8_t pixels);

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
static inline void GLCDOn()
{
	GLCDWriteCommand(1, 1, 0, 0, 0x1F);
}

/*
* Function: GLCDSetX
* Desc:     Записать в регистр координаты X
* Input:    x: координата, [0; 15], в байтах
* Output:   none
*/
static inline void GLCDSetX(const uint8_t x)
{
	const bool 	cs1 = (x < 8), 
				cs2 = (x >= 8);
	GLCDWriteCommand(cs1, cs2, 0, 0, 0xB8 | (x % 8));
}

/*
* Function: GLCDSetY
* Desc:     Записать в регистр координаты Y
* Input:    y: координата, [0; 63]
* Output:   none
*/
static inline void GLCDSetY(const uint8_t y)
{
	GLCDWriteCommand(1, 1, 0, 0, 0x40 | y);
}


/*
* Function: GLCDWriteData
* Desc:     Записать в память данные
* Input:    isCS1: выбранный контроллер CS1?
*			data: данные
* Output:   none
*/
static inline void GLCDWriteDisplayData(const bool isCS1, const uint8_t data)
{
	GLCDWriteCommand(isCS1, !isCS1, 0, 1, data);
}

/*
* Function: GLCDReadDisplayData
* Desc:     Прочитать данные из памяти
* Input:    none
* Output:   данные
*/
static inline uint8_t GLCDReadDisplayData(const bool isCS1)
{
	return GLCDReadCommand(isCS1, 1);
}


/*
* Function: GLCDDrawGbuf
* Desc:     Отрисовать на дисплее графический буфер
* Input:    none
* Output:   none
*/
void GLCDDrawGbuf();

#endif