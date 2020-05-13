#ifndef __MAIN_H__
#define __MAIN_H__ 1

#define F_CPU 8000000L

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>


typedef enum
{
	true = 1, 
	false = 0,
} bool;

typedef struct 
{
	uint8_t a, b;
} vect;


int main(void);

#define _delay_ns(_delay) _delay_us(_delay * 10)

inline void VectToArray(const vect v, uint8_t* target)
{
	target[0] = v.a;
	target[1] = v.b;
}

inline void ArrayToVect(const uint8_t* array, vect* target)
{
	*target = (vect){array[0], array[1]};
}

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


// #pragma GCC error "A"

// #define _if #if
// #define _endif #endif
// #define _pragma #pragma

#define ASSERT_CONCAT_(a, b) a##b
#define ASSERT_CONCAT(a, b) ASSERT_CONCAT_(a, b)
#define STATIC_ASSERT(e) enum { ASSERT_CONCAT(assert_line_, __LINE__) = 1/(!!(e)) }

// #pragma GCC diagnostic push
// #pragma GCC diagnostic ignored "-Wunused-variable"
// #define STATIC_ASSERT(COND,MSG) { if(!COND){ const char msg[] = "GCC error \" \""; _Pragma(msg); }}
// #pragma GCC diagnostic pop

// #pragma GCC diagnostic push
// #pragma GCC diagnostic ignored "-Wunused-variable"
// #define STATIC_ASSERT(COND,MSG) {static int static_assertion_##MSG[(COND)?1:-1] = {0}; static_assertion_##MSG[0]=*static_assertion_##MSG;}
// #pragma GCC diagnostic pop

// #pragma GCC diagnostic push
// #pragma GCC diagnostic ignored "-Wunused-local-typedefs"
// #define CTASTR2(pre,post) pre ## post
// #define CTASTR(pre,post) CTASTR2(pre,post)
// #define STATIC_ASSERT(cond,msg) 
//     typedef struct { int static_assertion_failed_ : !!(cond); } 
//         CTASTR2(static_assertion_failed_,__COUNTER__)
//         #pragma GCC diagnostic pop

// #define STATIC_ASSERT(COND,MSG) typedef char static_assertion_##MSG[(!!(COND))*2-1]
// token pasting madness:
// #define COMPILE_TIME_ASSERT3(X,L) STATIC_ASSERT(X,static_assertion_at_line_##L)
// #define COMPILE_TIME_ASSERT2(X,L) COMPILE_TIME_ASSERT3(X,L)
// #define COMPILE_TIME_ASSERT(X)    COMPILE_TIME_ASSERT2(X,__LINE__)

// #define CTC(X) ({ extern int __attribute__((error("assertion failure: '" #X "' not true"))) compile_time_check(); ((X)?0:compile_time_check()),0; })

#define MAX(x,y) ((x)>(y)?(x):(y))



#endif

