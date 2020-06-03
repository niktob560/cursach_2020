#include <main.h>
#include <glcd.h>
#include <twi.h>
#include <gobjects.h>
#include <layout.h>
#include <ds1307.h>
#include <touch.h>

#define FUNCS_NUM 10


/*Массив ф-ций для вызова*/
void (*funcsArray[FUNCS_NUM])() = {DS1307RequestData, LayoutDraw, DS1307SaveData, TouchTask};
/*Текущая задача*/
volatile uint8_t currFuncIndex = 0;
/*Массив флагов для блокировки вызова*/
volatile bool tasksRunned[FUNCS_NUM] = {false};


ISR(TIMER0_COMP_vect)
{
	TouchChannels();
	if(funcsArray[currFuncIndex] != NULL)
	{

		if(!tasksRunned[currFuncIndex])
		{
			tasksRunned[currFuncIndex] = true;
			sei();
			funcsArray[currFuncIndex]();
			cli();
			tasksRunned[currFuncIndex] = false;
		}
	}

	if(currFuncIndex >= FUNCS_NUM - 1)
		currFuncIndex = 0;
	else
		currFuncIndex++;
}


void initTimers(void)
{
					/*CTC; предделитель 64*/
	TCCR0 = (1 << WGM01) | (1 << CS02) | (0 << CS01) | (0 << CS00);
	
	/*разрешить прерывание по совпадению*/
	TIMSK = 1 << OCIE0;
	
	/*разрешить сравнение*/
	TIFR = 1 << OCF0;

	/*с чем сравнивать*/
	OCR0 = 125;
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
	LayoutSetMainmenu();
	//do nothing
	while(1)
	{
		_delay_us(1);
	}
    return 0;
}








/*
*	Function:	shiftLeft
*	Desc:		Сдвинуть массив влево на N элементов(с потерями)
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
*	Desc:		Сдвинуть массив вправо на N элементов(с потерями)
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