#include "usart.h"

char _usart0_txbuf [USART_TX_BUF_LEN];
uint16_t _usart0_txbuf_len_start = 0;
uint16_t _usart0_txbuf_len_end = 0;

/*
 * Function USART0Send
 * Desc     Send byte to USART0
 * Input    _data: byte to send
 * Output   none
*/
void USART0Send(char __data)			//send 1 byte to USART0
{
	while(!(UCSR0A & (1 << UDRE0)));//TODO: send to buf and get with interrupt
	UDR0 = (uint8_t)__data;
	/*
	 * The transmit buffer can only be written
	 * when the UDRE0 Flag in the UCSR0A Register is set
	 * from atmega328p datasheet
	 */
}

/*
 * Function USART0Print
 * Desc     Send byte array to USART0
 * Input    __data: byte array to send
 * Output   none
*/
void USART0Print(const char* __data)	//send C-string to USART0
{
	while(*__data != 0x00)
	{
		USART0Send(*(__data));
		__data++;
	}
}

/*
 * Function USART0Println
 * Desc     Send EndOfLine to USART0
 * Input    none
 * Output   none
*/
 void USART0PrintNL(void)
{
	USART0Print(EOL);
}


/*
 * Function USART0Println
 * Desc     send char array and EndOfLine to USART0
 * Input    __data: char array to send
 * Output   none
*/
 void USART0Println(const char* __data)
{
	USART0Print(__data);
	USART0Print(EOL);
}

/*
 * Function ISR(USART0_TX_vect)
 * Desc     Interrupt handler for vector USART0_TX
 * Input    interrupt vector
 * Output   none
*/
// #ifdef USART0_TX_vect
// ISR(USART0_TX_vect)//interrupt handler called aftar transmitting data
// #else
// ISR(USART_TX_vect)//interrupt handler called aftar transmitting data
// #endif
// {
// 	// if(_usart0_txbuf_len_start != _usart0_txbuf_len_end)
// 	// {
// 	// 	UDR0 = _usart0_txbuf[_usart0_txbuf_len_start++];
// 	// }
// 	// else
// 	// {
// 	// 	_usart0_txbuf_len_start = 0;
// 	// 	_usart0_txbuf_len_end = 0;
// 	// }
// 	/*#ifdef INTERRUPT_CUSTOMFUNC_USART0_TX
// 		if(funcs[INTERRUPT_CUSTOMFUNC_USART0_TX] != NULL)
// 			funcs[INTERRUPT_CUSTOMFUNC_USART0_TX]();		//call custom function
// 	#endif
// 	*/
// }


volatile char _inputBuf_[_USART_MAX_BUF_SIZE_];//buffer for input from USART0
volatile uint8_t _inputBufCounterInput_ = 0;//index of last char placed by system
volatile uint8_t _inputBufCounterOutput_ = 0;//index of last char gotted by user
volatile uint8_t _inputBufEmpty_ = true;



/*
 * Function ISR(USART0_RX_vect)
 * Desc     Interrupt handler for vector USART0_RX
 * Input    interrupt vector
 * Output   none
*/
ISR(USART0_RX_vect)		   //interrupt handler called after recieving data
{
	if(_inputBufCounterInput_ >= _USART_MAX_BUF_SIZE_	//check that counters are in borders of buf size
			|| _inputBufEmpty_)					//or buf empty
	{
		_inputBufCounterInput_ = 0;				//start writing from zero
	}

	_inputBuf_[_inputBufCounterInput_] = (char)UDR0;	//save data

	if(_inputBuf_[_inputBufCounterInput_] != '\0')//check for garbage
	{
		_inputBufEmpty_ = false;				//set empty flag down
		_inputBufCounterInput_++;				//go next index for writing
	}


	// interrupt::call(interrupt::USART0_RX);
}

/*
 * Function USART0Read
 * Desc     Read byte recieved from USART0
 * Input    none
 * Output   Recieved byte
*/
char USART0Read(void)//get data from input USART0 buffer
{
	if(_inputBufCounterOutput_ >= _USART_MAX_BUF_SIZE_)	//check that counters are in borders of buf size
	{
		_inputBufCounterOutput_ = 0;				//start from zero
		_inputBufEmpty_ = true;						//with empty buf
		return '\0';								//for bypassing -Wreturn-type
	}
	else if(_inputBufCounterOutput_ >= _inputBufCounterInput_)//check that counter for output not overtaked input
	{
		char ___ret = _inputBuf_[_inputBufCounterOutput_];//save data to temp var
		_inputBufCounterOutput_ = 0;						//set counters to zero
		_inputBufCounterInput_  = 0;
		_inputBufEmpty_ = true;								//empty buf
		return ___ret;									//return data
	}
	else if(!_inputBufEmpty_)								//if have data
	{
		char ___ret = _inputBuf_[_inputBufCounterOutput_];//save data to temp var
		_inputBufCounterOutput_++;							//go to next index for reading
		if(_inputBufCounterOutput_ >= _USART_MAX_BUF_SIZE_)		//check that counter is in borders of buf size
		{
			_inputBufCounterOutput_ = 0;					//start from zero
			_inputBufEmpty_ = true;							//empty buf
		}
		return ___ret;									//return data
	}
	else
	{
		return '\0';					//ERROR
	}
}

/*
 * Function USART0Available
 * Desc     Return is recieved new byte
 * Input    none
 * Output   Have new state
*/
bool USART0Available(void)
{
	if(_inputBufCounterOutput_ >= _inputBufCounterInput_	//check that counter for output not overtaked input
	|| _inputBufCounterOutput_ >= _USART_MAX_BUF_SIZE_)
	{
		_inputBufCounterOutput_ = 0;
		_inputBufCounterInput_  = 0;
		_inputBufEmpty_ = true;								//empty buf
	}
	return !_inputBufEmpty_;
}

/*
 * Function USART0Flush
 * Desc     Clear USART0 registers
 * Input    none
 * Output   none
*/
void USART0Flush(void)
{
	volatile uint8_t __temp = 0;
	__temp = __temp;//for bypassing -Wunused-but-set-variable
	while(UCSR0A & (1 << RXC0))
	{
		__temp = UDR0;
		_inputBufCounterInput_ = 0;
		_inputBufCounterInput_  = 0;
		_inputBufEmpty_ = true;
	}
}

/*
 * Function USART0SetBitSettings
 * Desc     Set USART0 packet parameters
 * Input    __bitness: mode for transmitting
 * Output   none
*/
void USART0SetBitSettings(uint8_t __bitness)
{
	UCSR0C = __bitness;
}

/*
 * Function USART0Begin
 * Desc     Initialize USART0
 * Input    __baud: baudrate for transmitting
 * Output   none
*/
void USART0Begin(uint64_t __baud)
{
		for(int i = 0; i < _USART_MAX_BUF_SIZE_; i++)//flush data array
		{
			_inputBuf_[i] = '\0';
		}

	UCSR0A = 1 <<  U2X0;									 //double speed mode
	uint16_t __baudPrescaller =  (uint16_t)((F_CPU / (8 * __baud))) - 1;//((Clock rate / (16 * baudrate))) - 1
														   //for U2X0 mode:
														  //((Clock rate / (8 * baudrate))) - 1
		if (((F_CPU == 16000000UL) && (__baud == 57600)) || (__baudPrescaller > 4095))	//disable double speed mode
		{																				//if prescaller is too high
			UCSR0A = 0;
			__baudPrescaller = (uint16_t)(F_CPU / (16 * __baud));
		}

	UBRR0L = (uint8_t)(__baudPrescaller);//set low bits of baud prescaller
	UBRR0H = (uint8_t)(__baudPrescaller >> 8);//set high bits of baud prescaller

		UCSR0B |= (1 << RXEN0) | (1 << RXCIE0);//enable recieve and interrupt on recieve

		UCSR0B |= (1 << TXEN0) | (1 << TXCIE0);//enable trancieve and interrupt on trancieve
											 //TODO: changable bit size
	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01); //set USART0 Character Size to 8 bit
	/*
	 * Character Size table:
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
