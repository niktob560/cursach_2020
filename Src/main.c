#include "main.h"
#include "glcd.h"
#include "usart.h"
#include "twi.h"




int main()
{
	sei();
	GLCDOn();
	while(1)
	{
		GLCDDrawSymbol((vect){0, 0}, 'A');
	}
    return 0;
}








/*
*	Function:	shiftLeft
*	Desc:		Сдвинуть массив влево на N элементов
*	Input:		arr: 	указатель на массив
*				len:	длина массива
*				el:		на сколько сдвинуть
*	Output:		none
*/
void shiftLeft(uint8_t* arr, uint32_t len, uint32_t el)
{
	for(uint32_t i = 0; i < len - el; i++)
	{
		arr[i] = arr[i + el];
	}
}



/*
*	Function:	shiftRight
*	Desc:		Сдвинуть массив вправо на N элементов
*	Input:		arr:	указатель на массив
*				len: 	длина массива
*				el:		на сколько сдвинуть
*	Output:		none
*/
void shiftRight(uint8_t* arr, uint32_t len, uint32_t el)
{
	while(len >= el)
	{
		arr[len] = arr[len - el];
		len--;
	}
}
