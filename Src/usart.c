#include "usart.h"

#define _USART_MAX_BUF_SIZE_ USART_TX_BUF_LEN

char _usart0_txbuf [USART_TX_BUF_LEN];
uint16_t _usart0_txbuf_len_start = 0;
uint16_t _usart0_txbuf_len_end = 0;

/*
 * Function USART0Send
 * Desc     Отправить байт в USART0
 * Input    _data: байт к отправке
 * Output   none
*/
void USART0Send(const char __data)
{
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = (uint8_t)__data;
	/*
	 * Буффер передатчика может быть записан только
	 * когда UDRE0 флаг регистра UCSR0A установлен
	 */
}

/*
 * Function USART0Print
 * Desc     Отправить массив байт в USART0
 * Input    __data: массив байт к отправке
 * Output   none
*/
void USART0Print(const char* __data)
{
	while(*__data != 0x00)
	{
		USART0Send(*(__data));
		__data++;
	}
}

/*
 * Function USART0Println
 * Desc     Отправить конец строки в USART0
 * Input    none
 * Output   none
*/
 void USART0PrintNL(void)
{
	USART0Print(EOL);
}


/*
 * Function USART0Println
 * Desc     Отправить массив байт и байт конца строки в USART0
 * Input    __data: массив байт к отправке
 * Output   none
*/
 void USART0Println(const char* __data)
{
	USART0Print(__data);
	USART0Print(EOL);
}


volatile char 		_inputBuf_[_USART_MAX_BUF_SIZE_] = {0};	/*буффер для полученных по USART0 данных*/
volatile uint8_t 	_inputBufCounterInput_ = 0;				/*индекс последнего сохраненного системой байта*/
volatile uint8_t 	_inputBufCounterOutput_ = 0;			/*индекс последнего сохраненного пользователем ф-ций байта*/
volatile bool 		_inputBufEmpty_ = true;



/*
 * Function ISR(USART0_RX_vect)
 * Desc     Обработчик прерывания для вектора USART0_RX
*/
ISR(USART0_RX_vect)
{
	if(_inputBufCounterInput_ >= _USART_MAX_BUF_SIZE_	/*проверить выход счетчика за границы буффера*/
			|| _inputBufEmpty_)							/*или буффер на пустоту*/
	{
		_inputBufCounterInput_ = 0;						/*начать запись с начала*/
	}

	_inputBuf_[_inputBufCounterInput_] = (char)UDR0;	/*сохранить данные*/

	if(_inputBuf_[_inputBufCounterInput_] != '\0')		/*проверить на мусор*/
	{
		_inputBufEmpty_ = false;						/*снять флаг пустоты*/
		_inputBufCounterInput_++;						/*переместиться на следующий индекс*/
	}
}

/*
 * Function USART0Read
 * Desc     Прочитать байт, полученный по USART0
 * Input    none
 * Output   Полученный байт
*/
char USART0Read(void)
{
	char __ret = '\0';
	if(_inputBufCounterOutput_ >= _USART_MAX_BUF_SIZE_)		/*проверить выход счетчика за границы буффера*/
	{
		_inputBufCounterOutput_ = 0;						/*начать с нуля*/
		_inputBufEmpty_ = true;								/*с пустым буффером*/
	}
	else if(_inputBufCounterOutput_ >= _inputBufCounterInput_)/*проверить что счетчик конца не опережает счетчик начала*/
	{
		__ret = _inputBuf_[_inputBufCounterOutput_];
		_inputBufCounterOutput_ = 0;						/*обнулить счетчики*/
		_inputBufCounterInput_  = 0;
		_inputBufEmpty_ = true;								/*опустошить буффер*/
	}
	else if(!_inputBufEmpty_)								/*если буффер не пуст*/
	{
		__ret = _inputBuf_[_inputBufCounterOutput_];
		_inputBufCounterOutput_++;							/*переместиться на следующий индекс для чтения*/
		if(_inputBufCounterOutput_ >= _USART_MAX_BUF_SIZE_)	/*проверить что счетчик не вышел за границы*/
		{
			_inputBufCounterOutput_ = 0;					/*начать с нуля*/
			_inputBufEmpty_ = true;							/*опустошить буффер*/
		}
	}
	return __ret;
}

/*
 * Function USART0Available
 * Desc     Проверить получен ли новый байт
 * Input    none
 * Output   Получен ли байт
*/
bool USART0Available(void)
{
	if(_inputBufCounterOutput_ >= _inputBufCounterInput_	/*проверить что счетчики не выходят за границы*/
	|| _inputBufCounterOutput_ >= _USART_MAX_BUF_SIZE_)
	{
		_inputBufCounterOutput_ = 0;
		_inputBufCounterInput_  = 0;
		_inputBufEmpty_ = true;								/*опустошить буффер*/
	}
	return !_inputBufEmpty_;
}

/*
 * Function USART0Flush
 * Desc     Удалить все пришедшие байты
 * Input    none
 * Output   none
*/
void USART0Flush(void)
{
	while(UCSR0A & (1 << RXC0))		/*пока существуют пришедшие байты*/
	{
		_inputBuf_[0] = (char)UDR0; /*для освобождения состояния аппарата USART нужно произвести чтение из UDR0*/
		_inputBufCounterInput_ = 0;
		_inputBufCounterInput_  = 0;
		_inputBufEmpty_ = true;
	}
}

/*
 * Function USART0Begin
 * Desc     Инициализировать USART0
 * Input    __baud: скорость передачи, бод
 * Output   none
*/
void USART0Begin(const uint64_t __baud)
{
		for(int i = 0; i < _USART_MAX_BUF_SIZE_; i++)		/*очистить буффер*/
		{
			_inputBuf_[i] = '\0';
		}

	UCSR0A = 1 <<  U2X0;									/*режим double speed*/
	uint16_t __baudPrescaller =  (uint16_t)((F_CPU / (8 * __baud))) - 1;//((частота / (16 * скорость))) - 1
														   /*для режима U2X0:
														  	((частота / (8 * скорость))) - 1*/
	if (((F_CPU == 16000000UL) && (__baud == 57600)) || (__baudPrescaller > 4095))	/*выключить режим double speed*/
	{																				/*если прескейлер слишком большой*/
		UCSR0A = 0;
		__baudPrescaller = (uint16_t)(F_CPU / (16 * __baud));
	}

	UBRR0L = (uint8_t)(__baudPrescaller);
	UBRR0H = (uint8_t)(__baudPrescaller >> 8);

		UCSR0B |= (1 << RXEN0) | (1 << RXCIE0);

		// UCSR0B |= (1 << TXEN0) | (1 << TXCIE0);
	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01); 	//размер символа в USART0 установлен в 8 бит
	/*
	 * Таблица размеров символов:
	 * 000 5-bit
	 * 001 6-bit
	 * 010 7-bit
	 * 011 8-bit
	 * 100 Reserved
	 * 101 Reserved
	 * 110 Reserved
	 * 111 9-bit
	 */
}
