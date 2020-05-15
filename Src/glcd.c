#include <glcd.h>
#include <font.h>


uint8_t GLCD_gbuf [GLCD_WIDTH_DWORD][GLCD_HEIGHT] = {0};

/*
* Function: GLCDSetPixel
* Desc:     Установить пиксель с координатами {x,y}
* Input:    coords: координаты вектора
*			pixels: пиксели
* Output:   none
*/
void GLCDSetPixel(const vect coords, const bool state)
{
	const uint8_t 	byteOffset = coords.a % 8,
					byteNum    = coords.a / 8;
			/*Сохранить текущий байт*/
	uint8_t byte = 0;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		GLCDSetX_byte(byteNum);
		GLCDSetY(coords.b);
		byte = GLCDReadDisplayData(coords.a < 64);
	}
	byte &= (uint8_t)~(1 << byteOffset);
	byte |= (uint8_t)(state << byteOffset);

			/*Записать новый байт*/
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		GLCDSetX_byte(byteNum);
		GLCDSetY(coords.b);
		GLCDWriteDisplayData(coords.a < 64, byte);
	}
}

/*
* Function: GLCDSet8Pixels
* Desc:     Установить 8 пикселей с координатами {x,y}
* Input:    coords: координаты левого верхнего угла
*			pixels: пиксели
* Output:   none
*/
void GLCDSet8Pixels(const vect coords, const uint8_t pixels)
{
	const uint8_t byteOffset = coords.a % 8;
	const bool cs1 = coords.a < 64;
	GLCDSetX_byte(coords.a / 8);
	GLCDSetY(coords.b);
	if(byteOffset == 0)
	{
		GLCDWriteDisplayData(coords.a < 64, pixels);
	}
	else
	{
		uint8_t byte = GLCDReadDisplayData(cs1);
		byte &= (uint8_t)(~(((uint8_t)(1 << (7 - byteOffset))) - 1) & 0xFF);
		byte |= (uint8_t)(pixels >> byteOffset);
		GLCDSetY(coords.b);
		GLCDWriteDisplayData(cs1, byte);

		GLCDSetX_byte((uint8_t)((coords.a / 8) + 1));
		GLCDSetY(coords.b);
		byte = GLCDReadDisplayData(cs1);
		byte &= (uint8_t)((1 << byteOffset) - 1);
		byte |= (uint8_t)(pixels << (7 - byteOffset));
		GLCDSetY(coords.b);
		GLCDWriteDisplayData(cs1, byte);
	}
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
		const uint8_t 	x_byte = x_px / 8;
		for(uint8_t y_px = 0; y_px < size.b; y_px++)
		{
			GLCDSet8Pixels((const vect){	(uint8_t)(coords.a + x_px), 
											(uint8_t)(coords.b + y_px)}, 
											pixmap[x_byte][y_px]);
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
	uint8_t pixmap[8];
	FontGetPixmap((uint8_t**)&pixmap, c);
	GLCDDrawPixmap(coords, (const vect){1, 8}, (const uint8_t**)&pixmap);
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
* Function: GLCDWriteCommand
* Desc:     Отправить команду записи
* Input:    cs1:	состояние CS1
*			cs2:	состояние CS2
*			rs:		состояние RS
*			rw:		состояние R/W
*			data:	данные для записи
* Output:   none
*/
void GLCDWriteCommand(const bool cs1, const bool cs2, const bool rs, const bool rw, const uint8_t data)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		turnPortOff(&GLCD_SPORT, 1 << GLCD_E);
		_delay_ns(450 - 140);
		turnPortOff(&GLCD_SPORT, (1 << GLCD_CS1) | (1 << GLCD_CS2));
		turnPortOn(&GLCD_SPORT, (uint8_t)((cs1 << GLCD_CS1) | (cs2 << GLCD_CS2)));
		turnPortOff(&GLCD_SPORT, (1 << GLCD_RS) | (1  << GLCD_RW));
		turnPortOn(&GLCD_SPORT, (uint8_t)((rs << GLCD_RS) | (rw  << GLCD_RW)));
		GLCD_DPORT = data;
		_delay_ns(140);
		turnPortOn(&GLCD_SPORT, 1 << GLCD_E);
		_delay_ns(1000 - 140 - 10);
		turnPortOff(&GLCD_SPORT, 1 << GLCD_E);
		_delay_ns(10);
		GLCD_DPORT = 0;
		turnPortOff(&GLCD_SPORT, (1 << GLCD_CS1) | (1 << GLCD_CS2) | (1 << GLCD_RS) | (1  << GLCD_RW));
	}
}


/*
* Function: GLCDWriteCommand
* Desc:     Отправить команду чтения
* Input:    isCS1:	состояние CS1
*			rs:		состояние RS
* Output:   прочитанный байт
*/
uint8_t GLCDReadCommand(const bool isCS1, const bool rs)
{
	uint8_t ret = 0;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		turnPortOff(&GLCD_SPORT, 1 << GLCD_E);
		_delay_ns(450 - 140);
		turnPortOff(&GLCD_SPORT, (1 << GLCD_RS) | (1 << GLCD_CS1) | (1 << GLCD_CS2));
		turnPortOn(&GLCD_SPORT, (uint8_t)((1 << GLCD_RW) | (rs << GLCD_RS) | (isCS1 << GLCD_CS1) | (uint8_t)(!isCS1 << GLCD_CS2)));
		_delay_ns(140);
		turnPortOn(&GLCD_SPORT, 1 << GLCD_E);
		_delay_ns(30);
		ret = PIND;
		_delay_ns(450 - 30);
		turnPortOn(&GLCD_SPORT, 1 << GLCD_E);
		turnPortOff(&GLCD_SPORT, 1 << GLCD_RW);
	}
	return ret;
}



/*
* Function: GLCDDrawGbuf
* Desc:     Отрисовать на дисплее графический буфер
* Input:    none
* Output:   none
*/
void GLCDDrawGbuf()
{
	for(uint8_t x_byte = 0; x_byte < GLCD_WIDTH_DWORD; x_byte++)
	{
		GLCDSetX_byte(x_byte);
		GLCDSetY(0);
		for(uint8_t y = 0; y < GLCD_HEIGHT; y++)
		{
			GLCDWriteDisplayData((x_byte < 8), GLCD_gbuf[x_byte][y]);
		}
	}
}