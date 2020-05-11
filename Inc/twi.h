#ifndef __TWI_H__
#define __TWI_H__

#include "main.h"
#include <util/atomic.h>

enum Responce { ACK = 1, NACK = 0 };

#define _TWI_OUT_BUF_LEN 	40
#define _TWI_IN_BUF_LEN 	60
#define _TWI_USR_IN_BUF_LEN 40

#define I2C_WRITE			0x00
#define I2C_READ			0x01
#define I2C_STANDBY 		0x02
#define I2C_FAIL    		0x03
#define I2C_RESTART_FAIL  	0x04
#define I2C_DISABLED   		0xFF

extern uint16_t	_twi_in_len;
extern uint16_t _twi_out_len;


/*
* Function:	TWISetFreq
* Desc:     Установить рабочую частоту шины I2C
* Input:    _freq: какую частоту установить
* Output:   none
*/
inline void	TWISetFreq(uint8_t _freq)
{
	TWBR = _freq;
}

/*
*	Function:	TWIAddPack
*	Desc:		Добавить пакет в очередь
*	Input:		addr:	адрес устройства
*				data:	указатель на массив с данными
*				len:	кол-во байт в массиве данных
*				mode:	режим чтения или записи
*	Output:		none
*/
void	TWIAddPack(uint8_t addr, const uint8_t* data, uint8_t len, uint8_t mode);

/*
*	Function:	TWIAddPackSingle
*	Desc:		Добавить пакет с одним байтом данных в очередь
*	Input:		addr:		адрес устройства
*				data:		байт данных
*				mode:		режим чтения или записи
*	Output:		none
*/
void	TWIAddPackSingle(uint8_t addr, uint8_t data, uint8_t mode);

/*
*	Function:	TWIAddPackDouble
*	Desc:		Добавить пакет с двумя байтами данных в очередь
*	Input:		addr:		адрес устройства
*				data:		2 байта
*				mode:		режим чтения или записи
*	Output:		none
*/
void	TWIAddPackDouble(uint8_t addr, uint16_t data, uint8_t mode);

/*
*	Function:	TWIGetByte
*	Desc:		Получить байт из очереди ввода(если имеется)
*	Input:		none
*	Output:		прочитанный байт (0xFF если нечего читать)
*/
uint8_t	TWIGetByte(void);

/*
*	Function: 	TWIWrite
*	Desc:		Записать байт в регистр на внешнем устройстве
*	Input:		addr: адрес устройства
*				reg: регистр для записи
*				data: что записывать
*	Output:		none
*/
void	TWIWrite(uint8_t addr, uint8_t reg, uint8_t data);


/*
*	Function: 	TWIReqRead
*	Desc:		Запросить чтение из регистра внешнего устройства
*	Input:		addr: адрес устройства
*				reg: какой регистр читать
*				len: длина в байтах
*	Output:		none
*/
void	TWIReqRead(uint8_t addr, uint8_t reg, uint8_t len);


/*
*	Function:	TWIStart
*	Desc:		Запустить конечный автомат TWI
*	Input:		none
*	Output:		none
*/
void	TWIStart(void);

/*
*	Function:	TWIStop
*	Desc:		Остановить конечный автомат TWI
*	Input:		none
*	Output:		none
*/
void	TWIStop(void);


/*
*	Function:	TWIHadRead
*	Desc:		Есть ли что читать
*	Input:		none
*	Output:		bool
*/
inline bool	TWIHadRead(void)
{
	return (_twi_in_len > 0)? true : false;
}

#endif