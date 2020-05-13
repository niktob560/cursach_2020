#ifndef __GOBJECTS_H__
#define __GOBJECTS_H__ 1

#include <main.h>
#include <glcd.h>
#include <string.h>
#include <font.h>

#define GOBJECT_TEXT_SIZE 10

typedef struct 
{
	const vect 	coords,
				size;
	bool 		filled,
				bordered;
} graph_primitive;

typedef struct 
{
	const vect 	coords,
				size;
	bool		inverted;
	char text[GOBJECT_TEXT_SIZE];
} graph_text;

typedef struct 
{
	const vect 	coords,
				size;
	bool 		filled;
	char text[GOBJECT_TEXT_SIZE];
	const uint8_t clickSignal;
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
* Desc:     Упаковать примитив в объект
* Input:    object: объект
*			target: куда упаковать
* Output:   none
*/
void GOBJECTPrimitiveToArray(const graph_primitive* object, uint8_t* target);

/*
* Function: GOBJECTDrawText
* Desc:     Нарисовать текст
* Input:    object: объект
* Output:   none
*/
void GOBJECTDrawText(const graph_text* text);

/*
* Function: GOBJECTTextToArray
* Desc:     Упаковать текст в объект
* Input:    object: объект
*			target: куда упаковать
* Output:   none
*/
void GOBJECTTextToArray(const graph_text* object, uint8_t* target);

/*
* Function: GOBJECTDrawButton
* Desc:     Нарисовать кнопку
* Input:    object: объект
* Output:   none
*/
void GOBJECTDrawButton(const graph_button* btn);

/*
* Function: GOBJECTButtonToArray
* Desc:     Упаковать текст в объект
* Input:    object: объект
*			target: куда упаковать
* Output:   none
*/
void GOBJECTButtonToArray(const graph_button* object, uint8_t* target);



#endif
