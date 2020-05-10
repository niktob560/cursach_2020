#ifndef __USART_H__
#define __USART_H__

#include "main.h"

#define USART_TX_BUF_LEN 100
#define _USART_MAX_BUF_SIZE_ 254


#ifndef DEC
	#define DEC 0
#endif //ifndef DEC

#ifndef BIN
	#define BIN 1
#endif //ifndef DEC

#ifndef EOL
	#define EOL "\r\n"
#endif

	


/*
 * Function USART0Begin
 * Desc     Инициализировать USART0
 * Input    __baud: скорость передачи, бод
 * Output   none
*/void USART0Begin(uint64_t __baud);


/*
 * Function USART0Send
 * Desc     Отправить байт в USART0
 * Input    _data: байт к отправке
 * Output   none
*/
/*TODO: const*/
void USART0Send(char __data);

/*
 * Function USART0Print
 * Desc     Отправить массив байт в USART0
 * Input    __data: массив байт к отправке
 * Output   none
*/
void USART0Print(const char* __data);

/*
 * Function USART0Println
 * Desc     Отправить конец строки в USART0
 * Input    none
 * Output   none
*/
void USART0PrintNL();

/*
 * Function USART0Println
 * Desc     Отправить массив байт и байт конца строки в USART0
 * Input    __data: массив байт к отправке
 * Output   none
*/
void USART0Println(const char* __data);



/*
 * Function USART0Read
 * Desc     Прочитать байт, полученный по USART0
 * Input    none
 * Output   Полученный байт
*/
char USART0Read(void);

/*
 * Function USART0Available
 * Desc     Проверить получен ли новый байт
 * Input    none
 * Output   Получен ли байт
*/
bool USART0Available(void);

/*
 * Function USART0Flush
 * Desc     Удалить все пришедшие байты
 * Input    none
 * Output   none
*/
void USART0Flush(void);

#endif