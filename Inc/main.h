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


inline bool getBit(uint8_t byte, uint8_t i)
{
	return (byte & (1 << i))? true : false;
}


inline uint8_t setBit(uint8_t base, uint8_t i, bool state)
{
	return (uint8_t)((base & ~(1 << i)) | (1 << state));
}


inline void turnPortOn(volatile uint8_t* port, uint8_t mask)
{
	*port |= mask;
}

inline void turnPortOff(volatile uint8_t* port, uint8_t mask)
{
	*port &= (uint8_t)~mask;
}


inline void togglePort(volatile uint8_t* port, uint8_t mask)
{
	*port ^= mask;
}




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

