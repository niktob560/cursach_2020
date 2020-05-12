#include <glcd.h>
#include <font.h>


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
		GLCDSetX(byteNum);
		GLCDSetY(coords.b);
		byte = GLCDReadData();
	}
	byte &= (uint8_t)~(1 << byteOffset);
	byte |= (uint8_t)(state << byteOffset);

			/*Записать новый байт*/
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		GLCDSetX(byteNum);
		GLCDSetY(coords.b);
		GLCDWriteData(byte);
	}
}

/*
* Function: GLCDSet8Pixels
* Desc:     Установить 8 пикселей с координатами {x,y}
* Input:    coords: координаты вектора
*			pixels: пиксели
* Output:   none
*/
void GLCDSet8Pixels(const vect coords, const uint8_t pixels)
{
	GLCDSetX(coords.a / 8);
	GLCDSetY(coords.b);
	GLCDWriteData(pixels);
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
* Function: GLCDOn
* Desc:     Отправить команду на включение экрана
* Input:    none
* Output:   none
*/
void GLCDOn()
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		turnPortOff(&GLCD_SPORT, (1 << GLCD_RS) | (1  << GLCD_RW));
		GLCD_DPORT = (0 << 7) | (0 << 6) | (1 << 5) | (1 << 4) | (1 << 3) | (1 << 2) | (1 << 1) | (1 << 0);
		_delay_ms(1);
		GLCD_DPORT = 0;
	}
}


/*
* Function: GLCDSetX
* Desc:     Записать в регистр координаты X
* Input:    x: координата, [0; 7]
* Output:   none
*/
void GLCDSetX(const uint8_t x)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		turnPortOff(&GLCD_SPORT, (1 << GLCD_RS) | (1  << GLCD_RW));
		GLCD_DPORT = (1 << 7) | (0 << 6) | (1 << 5) | (1 << 4) | (1 << 3) | x;
		_delay_us(140);
		GLCD_DPORT = 0;
	}
}

/*
* Function: GLCDSetY
* Desc:     Записать в регистр координаты Y
* Input:    y: координата, [0; 63]
* Output:   none
*/
void GLCDSetY(const uint8_t y)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		turnPortOff(&GLCD_SPORT, (1 << GLCD_RS) | (1  << GLCD_RW));
		GLCD_DPORT = (0 << 7) | (1 << 6) | y;
		_delay_us(140);
		GLCD_DPORT = 0;
	}
}

/*
* Function: GLCDWriteData
* Desc:     Записать в память данные
* Input:    data: данные
* Output:   none
*/
void GLCDWriteData(const uint8_t data)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		turnPortOn(&GLCD_SPORT, 1 << GLCD_RS);
		turnPortOff(&GLCD_SPORT, 1 << GLCD_RW);
		GLCD_DPORT = data;
		_delay_us(150);
		GLCD_DPORT = 0;
	}
}


/*
* Function: GLCDReadData
* Desc:     Прочитать данные из памяти
* Input:    none
* Output:   данные
*/
uint8_t GLCDReadData(void)
{
	uint8_t ret = 0;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		/*установить лог. 0 на порту данных*/
		GLCD_DPORT = 0;
		/*Установить порт данных в чтение*/
		DDRD = 0x00;
		/*поднять RS и RW*/
		turnPortOn(&GLCD_SPORT, (1 << GLCD_RS) | (1 << GLCD_RW));
		_delay_us(140);
		/*сохранить данные с шины*/
		ret = PIND;
		/*опустить RS и RW*/
		turnPortOff(&GLCD_SPORT, (1 << GLCD_RS) | (1 << GLCD_RW));
		/*установить порт данных в запись*/
		DDRD = 0xFF;
	}
	return ret;
}