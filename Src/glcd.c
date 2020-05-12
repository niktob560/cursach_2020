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
* Function: GLCDOn
* Desc:     Отправить команду на включение экрана
* Input:    none
* Output:   none
*/
void GLCDOn()
{
	GLCDWriteCommand(1, 1, 0, 0, 0x1F);
}


/*
* Function: GLCDSetX
* Desc:     Записать в регистр координаты X
* Input:    x: координата, [0; 7]
* Output:   none
*/
void GLCDSetX(const uint8_t x)
{
	const bool 	cs1 = (x < 64), 
				cs2 = (x >= 64);
	GLCDWriteCommand(cs1, cs2, 0, 0, 0xB8 | x);
}

/*
* Function: GLCDSetY
* Desc:     Записать в регистр координаты Y
* Input:    y: координата, [0; 63]
* Output:   none
*/
void GLCDSetY(const uint8_t y)
{
	GLCDWriteCommand(1, 1, 0, 0, 0x40 | y);
}

/*
* Function: GLCDWriteDisplayData
* Desc:     Записать в память данные
* Input:    isCS1: выбранный контроллер CS1?
*			data: данные
* Output:   none
*/
void GLCDWriteDisplayData(const bool isCS1, const uint8_t data)
{
	GLCDWriteCommand(isCS1, !isCS1, 0, 1, data);
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