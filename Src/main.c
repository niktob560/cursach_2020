#include <main.h>
#include <glcd.h>
#include <usart.h>
#include <twi.h>

#define FUNCS_NUM 10
/*Массив ф-ций для вызова*/
void (*funcsArray[FUNCS_NUM])();
volatile uint8_t currFuncIndex = 0;
bool systemIdle = true;
bool taskSwitching = false;

void funcCaller(const uint8_t index)
{
	systemIdle = false;
	taskSwitching = false;
	if(funcsArray[index] != NULL)
		funcsArray[index]();
	systemIdle = true;
}

ISR(TIMER0_COMP_vect)
{
	if(systemIdle && !taskSwitching)
	{
		if(currFuncIndex >= FUNCS_NUM - 1)
			currFuncIndex = 0;
		else
			currFuncIndex++;

		taskSwitching = true;
	}
}


void initTimers(void)
{
					/*CTC; предделитель 1024*/
	TCCR0 = (1 << WGM01) | (1 << CS02) | (1 << CS01) | (1 << CS00);
	
	/*разрешить прерывание по совпадению*/
	TIMSK = 1 << OCIE0;
	
	/*разрешить сравнение*/
	TIFR = 1 << OCF0;

	/*с чем сравнивать*/
	OCR0 = 100;
}

void init(void)
{
	/*порт управления экрана*/
	DDRE = 0xFF;
	/*порт данных экрана*/
	DDRA = 0xFF;

	GLCDOn();

			/*100КГц*/
	TWISetFreq(100000);

	initTimers();
}


int main()
{
	cli();
	init();
	sei();

	while(1)
	{
		if(!taskSwitching)
			funcCaller(currFuncIndex);
		//else do nothing
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
