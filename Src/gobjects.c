#include <gobjects.h>


/*
* Function: GOBJECTDrawPrimitive
* Desc:     Нарисовать прямоугольник
* Input:    object: объект
* Output:   none
*/
void GOBJECTDrawPrimitive(const graph_primitive* object)
{
	const uint8_t 	width = object->size.a,
					width_byte = width / 8,
					height = object->size.b;
	uint8_t pixmap[width_byte + 1][height];
	if(!object->filled)
		memset(pixmap, 0, (size_t)(width_byte*height));

	if(!object->filled && object->bordered)
	{
		for(uint8_t i = 0; i < width_byte; i++)
		{
			pixmap[i][0] = 0xFF;
			pixmap[i][height] = 0xFF;
		}
		for(uint8_t i = 0; i < height; i++)
		{
			pixmap[0][i] |= 1 << 7;
			pixmap[width_byte + (width - width_byte)][i] |= 1 << 7;
		}
	}
	else if(object->filled)
		memset(pixmap, 1, (size_t)(width_byte*height));
	
	GLCDDrawPixmap(object->coords, object->size, (const uint8_t**)pixmap);
}

/*
* Function: GOBJECTDrawText
* Desc:     Нарисовать текст
* Input:    object: объект текста
* Output:   none
*/
void GOBJECTDrawText(const graph_text* text)
{
	const graph_primitive primitive = {text->coords, text->size, text->inverted, 0};
	GOBJECTDrawPrimitive(&primitive);
	GLCDDrawText(text->coords, text->text);
}

/*
* Function: GOBJECTDrawButton
* Desc:     Нарисовать кнопку
* Input:    object: объект кнопки
* Output:   none
*/
void GOBJECTDrawButton(const graph_button* btn)
{
	const graph_text txt = {btn->coords, btn->size, btn->filled, {*btn->text}};
	GOBJECTDrawText(&txt);
}