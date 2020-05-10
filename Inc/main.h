#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

enum Bool
{
	True = 1, 
	False = 0
};

typedef struct 
{
	uint8_t a, b;
} vect;

#define bool enum Bool
#define true True
#define false False

#define F_CPU 8000000L

#endif