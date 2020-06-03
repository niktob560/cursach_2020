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
	const graph_primitive primitive = {text->coords, text->size, text->inverted? FILLED : NOT_FILLED, NOT_BORDERED};
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
	const graph_text txt = {btn->coords, btn->size, btn->filled? INVERTED : NOT_INVERTED, {*btn->text}, btn->textScale};
	GOBJECTDrawText(&txt);
}


/*
* Function: GOBJECTPrimitiveToArray
* Desc:     Упаковать примитив в объект
* Input:    object: объект
*			target: куда упаковать
* Output:   none
*/
void GOBJECTPrimitiveToArray(const graph_primitive* object, uint8_t* target)
{
	VectToArray(object->coords, target);
	target += 2;
	VectToArray(object->size, target);
	target += 2;
	*target = (uint8_t)((object->filled << 1) | (object->bordered));
}

/*
* Function: GOBJECTTextToArray
* Desc:     Упаковать текст в объект
* Input:    object: объект
*			target: куда упаковать
* Output:   none
*/
void GOBJECTTextToArray(const graph_text* object, uint8_t* target)
{
	VectToArray(object->coords, target);
	target += 2;
	VectToArray(object->size, target);
	target += 2;
	*target = object->inverted;
	target++;
	memcpy(target, &(object->text[0]), GOBJECT_TEXT_SIZE);
}

/*
* Function: GOBJECTButtonToArray
* Desc:     Упаковать текст в объект
* Input:    object: объект
*			target: куда упаковать
* Output:   none
*/
void GOBJECTButtonToArray(const graph_button* object, uint8_t* target)
{
	VectToArray(object->coords, target);
	target += 2;
	VectToArray(object->size, target);
	target += 2;
	*target = object->filled;
	target++;
	*target = object->clickSignal;
	target++;
	memcpy(target, &(object->text[0]), GOBJECT_TEXT_SIZE);
}




/*
* Function: GOBJECTArrayToPrimitive
* Desc:     Распаковать массив в примитив
* Input:    array: массив
*			target: куда распаковать
* Output:   none
*/
void GOBJECTArrayToPrimitive(const uint8_t* array, graph_primitive* target)
{
	ArrayToVect(array, &target->coords);
	array += 2;
	ArrayToVect(array, &target->size);
	array += 2;
	target->bordered 	= *array & 1;
	target->filled		= (*array >> 1) & 1;
}


/*
* Function: GOBJECTArrayToText
* Desc:     Распаковать массив в текст
* Input:    array: массив
*			target: куда распаковать
* Output:   none
*/
void GOBJECTArrayToText(const uint8_t* array, graph_text* target)
{
	ArrayToVect(array, &target->coords);
	array += 2;
	ArrayToVect(array, &target->size);
	array += 2;
	target->inverted	= *array & 1;
	array++;
	memcpy(target->text, array, GOBJECT_TEXT_SIZE);
}

/*
* Function: GOBJECTArrayToButton
* Desc:     Распаковать массив в кнопку
* Input:    array: массив
*			target: куда распаковать
* Output:   none
*/
void GOBJECTArrayToButton(const uint8_t* array, graph_button* target)
{
	ArrayToVect(array, &target->coords);
	array += 2;
	ArrayToVect(array, &target->size);
	array += 2;
	target->filled	= *array & 1;
	array++;
	target->clickSignal = *array;
	array++;
	memcpy(target->text, array, GOBJECT_TEXT_SIZE);
}
