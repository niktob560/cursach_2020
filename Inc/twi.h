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
* Function: TWI_setFreq
* Desc:     Установить рабочую частоту шины I2C
* Input:    _freq: какую частоту установить
* Output:   none
*/
inline void TWI_setFreq(uint8_t _freq)
{
	TWBR = _freq;
}

/*
*	Function:	_shiftLeft_
*	Desc:		Сдвинуть массив влево на N элементов
*	Input:		arr: 	указатель на массив
*				len:	длина массива
*				el:		на сколько сдвинуть
*	Output:		none
*/
void _shiftLeft_(uint8_t* arr, uint32_t len, uint32_t el);

/*
*	Function:	_shiftLeft_
*	Desc:		Сдвинуть массив вправо на N элементов
*	Input:		arr:	указатель на массив
*				len: 	длина массива
*				el:		на сколько сдвинуть
*	Output:		none
*/
void _shiftRight_(uint8_t* arr, uint32_t len, uint32_t el);

/*
*	Function:	TWI_addPack
*	Desc:		Добавить пакет в очередь
*	Input:		addr:	адрес устройства
*				data:	указатель на массив с данными
*				len:	кол-во байт в массиве данных
*				mode:	режим чтения или записи
*	Output:		none
*/
void TWI_addPack(uint8_t addr, const uint8_t* data, uint8_t len, uint8_t mode);

/*
*	Function:	TWI_addPackSingle
*	Desc:		Добавить пакет с одним байтом данных в очередь
*	Input:		addr:		адрес устройства
*				data:		байт данных
*				mode:		режим чтения или записи
*	Output:		none
*/
void TWI_addPackSingle(uint8_t addr, uint8_t data, uint8_t mode);

/*
*	Function:	TWI_addPackDouble
*	Desc:		Добавить пакет с двумя байтами данных в очередь
*	Input:		addr:		адрес устройства
*				data:		2 байта
*				mode:		режим чтения или записи
*	Output:		none
*/
void TWI_addPackDouble(uint8_t addr, uint16_t data, uint8_t mode);

/*
*	Function:	TWI_getByte
*	Desc:		Получить байт из очереди ввода(если имеется)
*	Input:		none
*	Output:		прочитанный байт (0xFF если нечего читать)
*/
uint8_t TWI_getByte(void);

/*
*	Function: 	TWI_write
*	Desc:		Записать байт в регистр на внешнем устройстве
*	Input:		addr: адрес устройства
*				reg: регистр для записи
*				data: что записывать
*	Output:		none
*/
void TWI_write(uint8_t addr, uint8_t reg, uint8_t data);


/*
*	Function: 	TWI_reqRead
*	Desc:		Запросить чтение из регистра внешнего устройства
*	Input:		addr: адрес устройства
*				reg: какой регистр читать
*				len: длина в байтах
*	Output:		none
*/
void TWI_reqRead(uint8_t addr, uint8_t reg, uint8_t len);


/*
*	Function:	TWI_start
*	Desc:		Запустить конечный автомат TWI
*	Input:		none
*	Output:		none
*/
void TWI_start(void);

/*
*	Function:	TWI_stop
*	Desc:		Остановить конечный автомат TWI
*	Input:		none
*	Output:		none
*/
void TWI_stop(void);


/*
*	Function:	TWI_hadRead
*	Desc:		Есть ли что читать
*	Input:		none
*	Output:		bool
*/
inline bool TWI_hadRead(void)
{
	return (_twi_in_len > 0);
}

#endif