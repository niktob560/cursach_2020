#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

enum Bool
{
	True = 1, 
	False = 0,
};

typedef struct 
{
	uint8_t a, b;
} vect;

#define bool enum Bool
#define true True
#define false False

#define F_CPU 8000000L

int main(void);







/*
*	Function:	shiftLeft
*	Desc:		Сдвинуть массив влево на N элементов
*	Input:		arr: 	указатель на массив
*				len:	длина массива
*				el:		на сколько сдвинуть
*	Output:		none
*/
void shiftLeft(uint8_t* arr, uint32_t len, uint32_t el);





/*
*	Function:	shiftRight
*	Desc:		Сдвинуть массив вправо на N элементов
*	Input:		arr:	указатель на массив
*				len: 	длина массива
*				el:		на сколько сдвинуть
*	Output:		none
*/
void shiftRight(uint8_t* arr, uint32_t len, uint32_t el);



#endif

