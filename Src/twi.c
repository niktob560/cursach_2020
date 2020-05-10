#include "twi.h"

uint16_t	_twi_out_len = 0;									/*2 bytes*/
uint8_t		_twi_out_curr = 0;									/*1 byte*/
uint16_t	_twi_in_len = 0;									/*2 bytes*/
uint16_t	_twi_usr_len = 0;									/*2 bytes*/
uint8_t		_twi_usr_packs = 0;									/*1 byte*/
uint8_t		_twi_usr_lens = 0;									/*1 byte*/
uint8_t 	_twi_out_queue[_TWI_OUT_BUF_LEN];					/*_OUT_BUF_LEN bytes*/
uint8_t 	_twi_in_queue[_TWI_IN_BUF_LEN];						/*_IN_BUF_LEN bytes*/
uint8_t 	_twi_usr_in_queue[_TWI_USR_IN_BUF_LEN];				/*_USR_IN_BUF_LEN bytes*/
uint8_t		_twi_usr_in_lens[_TWI_USR_IN_BUF_LEN];				/*_USR_IN_BUF_LEN bytes*/

uint8_t		_twi_status = 0xFF;									/*1 byte*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*																10 + _OUT_BUF_LEN + _IN_BUF_LEN + 2*_USR_IN_BUF_LEN bytes*/
/*																190 here*/








/*
*	Function:	TWI_addPack
*	Desc:		Добавить пакет в очередь
*	Input:		addr:	адрес устройства
*				data:	указатель на массив с данными
*				len:	кол-во байт в массиве данных
*				mode:	режим чтения или записи
*	Output:		none
*/
void TWI_addPack(uint8_t addr, const uint8_t* data, uint8_t len, uint8_t mode)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		addr = (uint8_t)(addr << 1);
		addr = (uint8_t)(addr | (mode & 1));

		_twi_usr_packs++;
		_twi_usr_in_queue[_twi_usr_len++] = addr;	/*Установить адрес внешнего устройства*/
		for(int i = 0; i < len; i++)				/*Переместить массив данных в пакет*/
		{
			_twi_usr_in_queue[_twi_usr_len++] = data[i];
		}
		_twi_usr_in_lens[_twi_usr_lens++] = (uint8_t)(len + 1);	/*Установить размер пакета*/
	}
}






/*
*	Function:	TWI_addPackSingle
*	Desc:		Добавить пакет с одним байтом данных в очередь
*	Input:		addr:		адрес устройства
*				data:		байт данных
*				mode:		режим чтения или записи
*	Output:		none
*/
void TWI_addPackSingle(uint8_t addr, uint8_t data, uint8_t mode)
{
	addr = (uint8_t)(addr << 1);
	addr = (uint8_t)(addr | (mode & 1));
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		_twi_usr_packs++;
		_twi_usr_in_queue[_twi_usr_len] = addr;	/*Установить адрес внешнего устройства*/
		_twi_usr_len++;
		_twi_usr_in_queue[_twi_usr_len] = data;	/*Байты для отправки*/
		_twi_usr_len++;
		_twi_usr_in_lens[_twi_usr_lens] = 2;	/*И размер пакета*/
		_twi_usr_lens++;
	}
}


/*
*	Function:	TWI_addPackDouble
*	Desc:		Добавить пакет с двумя байтами данных в очередь
*	Input:		addr:		адрес устройства
*				data:		2 байта
*				mode:		режим чтения или записи
*	Output:		none
*/
void TWI_addPackDouble(uint8_t addr, uint16_t data, uint8_t mode)
{
	addr = (uint8_t)(addr << 1);
	addr = (uint8_t)(addr | (mode & 1));
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		_twi_usr_packs++;
		_twi_usr_in_queue[_twi_usr_len++] = addr;		/*Установить адрес внешнего устройства*/
		_twi_usr_in_queue[_twi_usr_len++] = data & 0xFF;/*Байты для отправки*/
		_twi_usr_in_queue[_twi_usr_len++] = (uint8_t)((data >> 8) & 0xFF);
		/*NOTE: why 2 when 3?*/
		_twi_usr_in_lens[_twi_usr_lens++] = 2;			/*И размер пакета*/
	}
}






/*
*	Function:	TWI_getByte
*	Desc:		Получить байт из очереди ввода(если имеется)
*	Input:		none
*	Output:		прочитанный байт (0xFF если нечего читать)
*/
uint8_t TWI_getByte(void)
{
	if(_twi_in_len > 0)
	{
		uint8_t _buf = _twi_in_queue[0];
		shiftLeft(_twi_in_queue, _twi_in_len--, 1);
		return _buf;
	}
	else
	{
		return 0xFF;	/*нечего читать*/
	}
}






/*
*	Function:	 _TWI_reply_
*	Desc:		Отправить ответ в TWI (ACK или NACK)
*	Input:		_ack: ACK или NACK
*	Output:		none
*/
void _TWI_reply_(enum Responce _ack)
{
	if(_ack == ACK)
	{
		TWCR 	= (1 << TWEN) 	/*Включить TWI*/
				| (1 << TWIE) 	/*Установить флаг прерывания*/
				| (1 << TWINT) 	/*Разрешить прерывания*/
				| (1 << TWEA);	/*Разрешить ACK*/
	}
	else
	{
		TWCR 	= (1 << TWEN) 	/*Включить TWI*/
				| (1 << TWIE) 	/*Установить флаг прерывания*/
				| (1 << TWINT);	/*Разрешить прерывания*/
	}
}





/*
*	Function:	_TWI_start_
*	Desc:		Запустить TWI
*	Input:		none
*	Output:		none
*/
inline void _TWI_start_(void)
{
	TWCR 	= (1 << TWSTA)	/*Сформировать START*/
			| (1 << TWINT)	/*Установить флаг прерывания*/
			| (1 << TWEN) 	/*Включить TWI*/
			| (1 << TWIE);	/*Разрешить прерывания*/
}






/*
*	Function:	_TWI_stop_
*	Desc:		Остановить TWI
*	Input:		none
*	Output:		none
*/
inline void _TWI_stop_(void)
{
	TWCR 	= (1 << TWEN)	/*Включить TWI*/
			| (1 << TWIE)	/*Разрешить прерывания*/
			| (1 << TWINT)	/*Установить флаг прерывания*/
			| (1 << TWSTO);	/*Сформировать STOP*/
}






/*
*	Function:	TWI_start
*	Desc:		Запустить конечный автомат TWI
*	Input:		none
*	Output:		none
*/
void TWI_start(void)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		if(_twi_status != I2C_READ
			&& _twi_status != I2C_WRITE)
		{
			uint8_t bytes = _twi_usr_in_lens[0];				/*Получить кол-во байт к отправке*/
			shiftLeft(_twi_usr_in_lens, _twi_usr_lens--, 1);	/*Сдвинуть массив длин пакетов влево на 1 элемент*/
			for(uint8_t i = 0; i < bytes; i++)
			{													/*Копировать пакет в буффер вывода конечного автомата*/
				_twi_out_queue[i] = _twi_usr_in_queue[i];
			}
			shiftLeft(_twi_usr_in_queue, _twi_usr_len, bytes);/*Удалить пакет из пользовательского буффера вывода*/

			_twi_usr_len -= bytes;
			_twi_out_len = bytes;
			_twi_status = (_twi_out_queue[0] & 1)? I2C_READ : I2C_WRITE;/*Сохранить состояние*/
			_twi_usr_packs--;
			_TWI_start_();										/*Запустить TWI*/
		}
	}
}





/*
*	Function:	TWI_stop
*	Desc:		Остановить конечный автомат TWI
*	Input:		none
*	Output:		none
*/
void TWI_stop(void)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		_TWI_stop_();					/*Перейти к ожиданию*/
		_twi_status = I2C_STANDBY;
		_twi_out_len = 0;
		if(_twi_usr_packs > 0)
		{
			TWI_start();				/*	Запустить конечный автомат
											если ещё есть пакеты*/
		}
	}
}




/*
*	Function: 	TWI_write
*	Desc:		Записать байт в регистр на внешнем устройстве
*	Input:		addr: адрес устройства
*				reg: регистр для записи
*				data: что записывать
*	Output:		none
*/
void TWI_write(uint8_t addr, uint8_t reg, uint8_t data)
{
	TWI_addPackDouble(addr, (uint16_t)((reg << 8) | data), I2C_WRITE);
	TWI_start();
}


/*
*	Function: 	TWI_reqRead
*	Desc:		Запросить чтение из регистра внешнего устройства
*	Input:		addr: адрес устройства
*				reg: какой регистр читать
*				len: длина в байтах
*	Output:		none
*/
void TWI_reqRead(uint8_t addr, uint8_t reg, uint8_t len)
{
	TWI_addPackSingle(addr, reg, I2C_WRITE);
	TWI_addPackSingle(addr, len, I2C_READ);
	TWI_start();
}







ISR(TWI_vect)
{
	switch(TWSR)
	{
		case 0x00:												/*Ошибка шины*/
		{
			_twi_status = I2C_FAIL;
			TWI_stop();
			break;
		}
		case 0x08:												/*Старт*/
		{
			_twi_out_curr = 0;
			TWDR = _twi_out_queue[_twi_out_curr++];
			_TWI_reply_(ACK);
			break;
		}
		case 0x10:												/*Повторный старт*/
		{
			_twi_out_curr = 0;
			TWDR = _twi_out_queue[_twi_out_curr++];
			_TWI_reply_(ACK);
			break;
		}
		case 0x28:												/*byte+ACK*/
		case 0x18:												/*SLA+W+ACK*/
		{
			if(_twi_out_curr < _twi_out_len)
			{
				TWDR = _twi_out_queue[_twi_out_curr++];
				_TWI_reply_(ACK);
			}
			else
			{
				if(_twi_usr_packs == 0 || ((_twi_usr_in_queue[0])&1) == 0)
				{
					TWI_stop();
				}
				else
				{
					_twi_status = I2C_STANDBY;
					TWI_start();
				}
			}
			break;
		}
		case 0x20:												/*SLA+W+NACK*/
		{
			_twi_status = I2C_FAIL;
			TWI_stop();
			break;
		}
		case 0x30:												/*byte+NACK*/
		{
			_twi_status = I2C_FAIL;
			TWI_stop();
			break;
		}
		case 0x38:												/*Коллизия с другим master*/
		{
			_twi_status = I2C_FAIL;
			TWI_stop();
			break;
		}
		case 0x40:												/*SLA+R+ACK*/
		{
			if(_twi_out_queue[1] <= 1)
				_TWI_reply_(NACK);
			else
				_TWI_reply_(ACK);
			break;
		}
		case 0x48:												/*SLA+R+NACK*/
		{
			_twi_status = I2C_FAIL;
			TWI_stop();
			break;
		}
		case 0x50:												/*Получить байт*/
		{
			_twi_in_queue[_twi_in_len++] = TWDR;
			_twi_out_queue[1]--;
			if(_twi_out_queue[1] <= 1)
				_TWI_reply_(NACK);
			else
				_TWI_reply_(ACK);
			break;
		}
		case 0x58:												/*получить байт и NACK*/
		{
			_twi_in_queue[_twi_in_len++] = TWDR;
			_twi_status = I2C_STANDBY;
			TWI_stop();
			break;
		}
		default:
		{
			_twi_status = I2C_FAIL;
			TWI_stop();
		}
	}
}
