#ifndef __GOBJECTS_H__
#define __GOBJECTS_H__ 1

#include <main.h>
#include <glcd.h>
#include <string.h>
#include <font.h>

#define GOBJECT_TEXT_SIZE 10
#define GOBJECT_PRIMITIVE_ARRAY_SIZE 	5
#define GOBJECT_TEXT_ARRAY_SIZE 		(5 + GOBJECT_TEXT_SIZE)
#define GOBJECT_BUTTON_ARRAY_SIZE 		(6 + GOBJECT_TEXT_SIZE)

typedef enum 
{
	FILLED = true,
	NOT_FILLED = false
} isFilled;

typedef enum 
{
	BORDERED = true,
	NOT_BORDERED = false
} isBordered;

typedef enum 
{
	INVERTED = true,
	NOT_INVERTED = false
} isInverted;

typedef struct 
{
	vect	 	coords,
				size;
	isFilled	filled;
	isBordered	bordered;
} graph_primitive;

typedef struct 
{
	vect 		coords,
				size;
	isInverted	inverted;
	char 		text[GOBJECT_TEXT_SIZE];
} graph_text;

typedef struct 
{
	vect	 	coords,
				size;
	isFilled	filled;
	char 		text[GOBJECT_TEXT_SIZE];
	uint8_t	 	clickSignal;
} graph_button;

/*
* Function: GOBJECTDrawPrimitive
* Desc:     Нарисовать прямоугольник
* Input:    object: объект
* Output:   none
*/
void GOBJECTDrawPrimitive(const graph_primitive* object);

/*
* Function: GOBJECTPrimitiveToArray
* Desc:     Упаковать примитив в массив
* Input:    object: объект
*			target: куда упаковать
* Output:   none
*/
void GOBJECTPrimitiveToArray(const graph_primitive* object, uint8_t* target);

/*
* Function: GOBJECTArrayToPrimitive
* Desc:     Распаковать массив в примитив
* Input:    array: массив
*			target: куда распаковать
* Output:   none
*/
void GOBJECTArrayToPrimitive(const uint8_t* array, graph_primitive* target);

/*
* Function: GOBJECTDrawText
* Desc:     Нарисовать текст
* Input:    object: объект
* Output:   none
*/
void GOBJECTDrawText(const graph_text* text);

/*
* Function: GOBJECTTextToArray
* Desc:     Упаковать текст в массив
* Input:    object: объект
*			target: куда упаковать
* Output:   none
*/
void GOBJECTTextToArray(const graph_text* object, uint8_t* target);

/*
* Function: GOBJECTArrayToText
* Desc:     Распаковать массив в текст
* Input:    array: массив
*			target: куда распаковать
* Output:   none
*/
void GOBJECTArrayToText(const uint8_t* array, graph_text* target);

/*
* Function: GOBJECTDrawButton
* Desc:     Нарисовать кнопку
* Input:    object: объект
* Output:   none
*/
void GOBJECTDrawButton(const graph_button* btn);

/*
* Function: GOBJECTButtonToArray
* Desc:     Упаковать текст в массив
* Input:    object: объект
*			target: куда упаковать
* Output:   none
*/
void GOBJECTButtonToArray(const graph_button* object, uint8_t* target);

/*
* Function: GOBJECTArrayToButton
* Desc:     Распаковать массив в кнопку
* Input:    array: массив
*			target: куда распаковать
* Output:   none
*/
void GOBJECTArrayToButton(const uint8_t* array, graph_button* target);



#endif
