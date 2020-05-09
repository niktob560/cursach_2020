#include "twi.h"

uint16_t	_twi_out_len = 0;														//2 bytes
uint8_t		_twi_out_curr = 0;														//1 byte
uint16_t	_twi_in_len = 0;														//2 bytes
uint16_t	_twi_usr_len = 0;														//2 bytes
uint8_t		_twi_usr_packs = 0;														//1 byte
uint8_t		_twi_usr_lens = 0;														//1 byte
uint8_t 	_twi_out_queue[_TWI_OUT_BUF_LEN];							//_OUT_BUF_LEN bytes
uint8_t 	_twi_in_queue[_TWI_IN_BUF_LEN];								//_IN_BUF_LEN bytes
uint8_t 	_twi_usr_in_queue[_TWI_USR_IN_BUF_LEN];				//_USR_IN_BUF_LEN bytes
uint8_t		_twi_usr_in_lens[_TWI_USR_IN_BUF_LEN];				//_USR_IN_BUF_LEN bytes

uint8_t		_twi_status = 0xFF;														//1 byte
//--------------------------------------------------------------------------------------------
//																											10 + _OUT_BUF_LEN + _IN_BUF_LEN + 2*_USR_IN_BUF_LEN bytes
//																											190 here






/*
* Function: I2C_SetFreq
* Desc:     Set working frequency of I2C bus
* Input:    _freq: what frequency set to
* Output:   none
*/
//inline void I2C_SetFreq(uint8_t _freq)
//{
//	TWBR = _freq;
//}







/*
*	Function:	_shiftLeft_
*	Desc:		Shift some array to left on N elements
*	Input:		void* arr: 		ptr to array shift to
				uint8_t size:	size of element
				uint32_t len: 	length of array
				uint32_t el:	num of elements
*	Output:		none
*/
void _shiftLeft_(uint8_t* arr, uint32_t len, uint32_t el)
{
	for(uint32_t i = 0; i < len - el; i++)
	{
		arr[i] = arr[i + el];
	}

}





/*
*	Function:	_shiftRight_
*	Desc:		Shift some array to right on N elements
*	Input:		void* arr: ptr to array shift to
				uint32_t len: length of array
*	Output:		none
*/
void _shiftRight_(uint8_t* arr, uint32_t len, uint32_t el)
{
	//cli();									//block interrupts, atomic block

	//for(uint32_t i = len - el; i < len - el; i++)
	while(len >= el)
	{
		arr[len] = arr[len - el];
		len--;
	}

	//sei();									//allow interrupts
}






/*
*	Function:	TWI_addPack
*	Desc:		Add package to user queue
*	Input:		uint8_t  addr:			what addr of slave set to
				const uint8_t* data:	pointer to data array
				uint8_t len:			num of bytes in data array
				uint8_t mode:			read or write mode use to
*	Output:		none
*/
void TWI_addPack(uint8_t addr, const uint8_t* data, uint8_t len, uint8_t mode)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		//cli();										//block interrupts, must be atomic
		addr = (uint8_t)(addr << 1);
		addr |= mode & 1;

		_twi_usr_packs++;
		_twi_usr_in_queue[_twi_usr_len++] = addr;	//add addr of slave device to queue
		for(int i = 0; i < len; i++)				//iterate in data array and add all bytes in usr queue
		{
			_twi_usr_in_queue[_twi_usr_len++] = data[i];
		}
		_twi_usr_in_lens[_twi_usr_lens++] = (uint8_t)(len + 1);	//set num of bytes in pack
		//sei();										//allow interrupts, atomic block ended
	}
}






/*
*	Function:	TWI_addPackSingle
*	Desc:		Add single-byte package to user queue
*	Input:		uint8_t  addr:		what addr of slave set to
				uint8_t data:		byte send to
				uint8_t mode:		read or write mode use to
*	Output:		none
*/
void TWI_addPackSingle(uint8_t addr, uint8_t data, uint8_t mode)
{
	addr = (uint8_t)(addr << 1);
	addr |= mode & 1;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		_twi_usr_packs++;
		_twi_usr_in_queue[_twi_usr_len] = addr;	//add addr of slave device
		_twi_usr_len++;
		_twi_usr_in_queue[_twi_usr_len] = data;	//				,byte to send
		_twi_usr_len++;
		_twi_usr_in_lens[_twi_usr_lens] = 2;		//				and num of bytes in pack
		_twi_usr_lens++;
	}
}


/*
*	Function:	TWI_addPackDouble
*	Desc:		Add double-byte package to user queue
*	Input:		uint8_t  addr:		what addr of slave set to
				uint16_t data:		byte send to
				uint8_t mode:		read or write mode use to
*	Output:		none
*/
void TWI_addPackDouble(uint8_t addr, uint16_t data, uint8_t mode)
{
	addr = (uint8_t)(addr << 1);
	addr |= mode & 1;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		//cli();											//block interrupts, must be atomic
		_twi_usr_packs++;
		_twi_usr_in_queue[_twi_usr_len++] = addr;		//add addr of slave device
		_twi_usr_in_queue[_twi_usr_len++] = data & 0xFF;//,byte to send
		_twi_usr_in_queue[_twi_usr_len++] = (uint8_t)((data >> 8) & 0xFF);
		_twi_usr_in_lens[_twi_usr_lens++] = 2;			//				and num of bytes in pack
		//sei();											//allow interrupts, atomic block ended
	}
}






/*
*	Function:	TWI_getByte
*	Desc:		Get byte from input array(if have)
*	Input:		none
*	Output:		uint8_t: readed byte (0xFF if nothing to read)
*/
uint8_t TWI_getByte(void)
{
	//USART0Println("reading byte from buf...");
	if(_twi_in_len > 0)
	{
		uint8_t _buf = _twi_in_queue[0];
		_shiftLeft_(_twi_in_queue, _twi_in_len--, 1);
		return _buf;
	}
	else
	{
		return 0xFF;//nothing to read
	}
}






/*
*	Function:	 _TWI_reply_
*	Desc:		Send reply to TWI (ACK or NACK)
*	Input:		uint8_t _ack: send ACK or NACK
*	Output:		none
*/
void _TWI_reply_(enum Responce _ack)
{
	if(_ack == ACK)
	{
		TWCR 	= (1 << TWEN) 	//enable TWI
				| (1 << TWIE) 	//set interrupt flag
				| (1 << TWINT) 	//allow interrupts
				| (1 << TWEA);	//allow ACK
	}
	else
	{
		TWCR 	= (1 << TWEN) 	//enable TWI
				| (1 << TWIE) 	//set interrupt flag
				| (1 << TWINT);	//allow interrupts
	}
}





/*
*	Function:	_TWI_start_
*	Desc:		Start TWI for state machine
*	Input:		none
*	Output:		none
*/
inline void _TWI_start_(void)
{
	TWCR 	= (1 << TWSTA)	//forming start
			| (1 << TWINT)	//set interrupt flag
			| (1 << TWEN) 	//enable TWI
			| (1 << TWIE);	//allow interrupts
}






/*
*	Function:	_TWI_stop_
*	Desc:		Stop TWI for state machine
*	Input:		none
*	Output:		none
*/
inline void _TWI_stop_(void)
{
	TWCR 	= (1 << TWEN)	//enable TWI
			| (1 << TWIE)	//allow interrupts
			| (1 << TWINT)	//set interrupt flag
			| (1 << TWSTO);	//forming stop
}






/*
*	Function:	TWI_start
*	Desc:		Start TWI state machine
*	Input:		none
*	Output:		none
*/
void TWI_start(void)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		//cli();												//block interrupts, must be atomic

		if(_twi_status != I2C_READ
			&& _twi_status != I2C_WRITE)
		{
			uint8_t bytes = _twi_usr_in_lens[0];				//get num of bytes to send
			_shiftLeft_(_twi_usr_in_lens, _twi_usr_lens--, 1);	//shift array with lens of packs to left for 1 element
			//cli();		//TODO: fix
			for(uint8_t i = 0; i < bytes; i++)
			{													//iterate "bytes" times and copy package
				_twi_out_queue[i] = _twi_usr_in_queue[i];
			}
			_shiftLeft_(_twi_usr_in_queue, _twi_usr_len, bytes);//remove from user queue
			//cli();		//TODO: fix

			_twi_usr_len -= bytes;
			_twi_out_len = bytes;
			_twi_status = (_twi_out_queue[0] & 1)? I2C_READ : I2C_WRITE;//save status
			_twi_usr_packs--;
			_TWI_start_();										//kick the TWI machine
		}
		//sei();												//allow interrupts, atomic block ended
	}
}





/*
*	Function:	TWI_stop
*	Desc:		Stop TWI state machine
*	Input:		none
*	Output:		none
*/
void TWI_stop(void)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		//cli();							//block interrupts, must be atomic

		_TWI_stop_();					//go to standby
		_twi_status = I2C_STANDBY;
		_twi_out_len = 0;
		if(_twi_usr_packs > 0)
		{
			TWI_start();					//kick state machine for new start
		}

		//sei();							//allow interrupts, atomic block ended
	}
}






/*
*	Function:	twiHadRead
*	Desc:		If have new bytes to read return 1(t), else 0(f)
*	Input:		none
*	Output:		bool
*/
//inline bool twiHadRead(void)
//{
//	return (_in_len > 0);
//}




/*
*	Function: 	write
*	Desc:		Write a byte to reg on slave device
*	Input:		uint8_t addr: slave device addr
				uint8_t reg: what reg write to
				uint8_t data: what write to
*	Output:		none
*/
void TWI_write(uint8_t addr, uint8_t reg, uint8_t data)
{
	TWI_addPackDouble(addr, (uint16_t)((reg << 8) | data), I2C_WRITE);
	TWI_start();
}


/*
*	Function: 	TWI_reqRead
*	Desc:		Request a byte from reg on slave device
*	Input:		uint8_t addr: slave device addr
				uint8_t reg: what reg read from
				uint8_t len: len of data in bytes
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
		case 0x00:												//bus fail
		{
			_twi_status = I2C_FAIL;
			TWI_stop();
			break;
		}
		case 0x08:												//start
		{
			_twi_out_curr = 0;
			TWDR = _twi_out_queue[_twi_out_curr++];
			_TWI_reply_(ACK);
			break;
		}
		case 0x10:												//reStart
		{
			_twi_out_curr = 0;
			TWDR = _twi_out_queue[_twi_out_curr++];
			_TWI_reply_(ACK);
			break;
		}
		case 0x28:												//byte+ACK
		case 0x18:												//SLA+W+ACK
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
					//_TWI_start_();
					_twi_status = I2C_STANDBY;
					TWI_start();
				}
				//_TWI_reply_(NACK);
			}
			break;
		}
		case 0x20:												//SLA+W+NACK
		{
				//handling of error
			if(_twi_status == I2C_READ) //TODO: TEST IT!
			{
				//for(uint8_t i = 0; i < _out_queue[1]; i++)
					//_in_queue[_in_len++] = -1;
			}
			else if((_twi_usr_in_queue[0] & 1) == 0)
			{
				//USART0Println("bypassing errors on try-to-read");
				//for(uint8_t i = 0; i < _usr_in_queue[1]; i++)
				//	_in_queue[_in_len++] = -1;
			}
			_twi_status = I2C_FAIL;
			TWI_stop();
			break;
		}
		case 0x30:												//byte+NACK
		{
			_twi_status = I2C_FAIL;
			TWI_stop();
			break;
		}
		case 0x38:												//collision
		{
			_twi_status = I2C_FAIL;
			TWI_stop();
			break;
		}
		case 0x40:												//SLA+R+ACK
		{
			if(_twi_out_queue[1] <= 1)
				_TWI_reply_(NACK);
			else
				_TWI_reply_(ACK);
			break;
		}
		case 0x48:												//SLA+R+NACK
		{
			_twi_status = I2C_FAIL;
			TWI_stop();
			break;
		}
		case 0x50:												//recive byte
		{
			_twi_in_queue[_twi_in_len++] = TWDR;
			_twi_out_queue[1]--;
			if(_twi_out_queue[1] <= 1)
				_TWI_reply_(NACK);
			else
				_TWI_reply_(ACK);
			break;
		}
		case 0x58:												//recive byte+NACK
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
