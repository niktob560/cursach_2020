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

	


//set bit settings of USART, mode on input
void USART0SetBitSettings(uint8_t __bitness);
//init function, baudrate on input
void USART0Begin(uint64_t __baud);


//send one char function
void USART0Send(char __data);

//send char array function
void USART0Print(const char* __data);

void USART0PrintNL();
void USART0Println(const char* __data);



//get recieved data
char USART0Read(void);
//get is any data recieved
bool USART0Available(void);
//remove all recieved data
void USART0Flush(void);

#endif