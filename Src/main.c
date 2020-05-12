#include <main.h>
#include <glcd.h>
#include <usart.h>
#include <twi.h>

#define FUNCS_NUM 10

void a();

void b();

/*Массив ф-ций для вызова*/
void (*funcsArray[FUNCS_NUM])() = {a, b};
volatile uint8_t currFuncIndex = 0;
volatile bool systemIdle = true;


ISR(TIMER0_COMP_vect)
{
	if(systemIdle)
	{
		if(funcsArray[currFuncIndex] != NULL)
		{
			systemIdle = false;
			sei();
			funcsArray[currFuncIndex]();
			cli();
			systemIdle = true;
		}

		if(currFuncIndex >= FUNCS_NUM - 1)
			currFuncIndex = 0;
		else
			currFuncIndex++;
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
	#ifdef DEBUG
	USART0Begin(115200);
	#endif
	/*порт управления экрана*/
	DDRE = 0xFF;
	/*порт данных экрана*/
	DDRA = 0xFF;
	
	GLCDOn();
	#ifdef DEBUG
	USART0Println("GLCD ON");
	#endif

			/*100КГц*/
	TWISetFreq(100000);
	#ifdef DEBUG
	USART0Println("TWI ON");
	#endif

	initTimers();
	#ifdef DEBUG
	USART0Println("TIMERS ON");
	#endif
}


int main()
{
	cli();
	init();
	sei();

	//do nothing
	while(1);
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



void a(){}
void b(){}