#include "main.h"
#include <util/atomic.h>

enum Responce { ACK = 1, NACK = 0 };

#define _TWI_OUT_BUF_LEN 40
#define _TWI_IN_BUF_LEN 60
#define _TWI_USR_IN_BUF_LEN 40

const uint8_t I2C_WRITE			= 0x00;
const uint8_t I2C_READ			= 0x01;
const uint8_t I2C_STANDBY		= 0x02;
const uint8_t I2C_FAIL			= 0x03;
const uint8_t I2C_RESTART_FAIL	= 0x04;
const uint8_t I2C_DISABLED		= 0xFF;

extern uint16_t	_twi_in_len;
extern uint16_t _twi_out_len;


/*
* Function: TWI_setFreq
* Desc:     Set working frequency of I2C bus
* Input:    _freq: what frequency set to
* Output:   none
*/
inline void TWI_setFreq(uint8_t _freq)
{
	TWBR = _freq;
}

/*
*	Function:	_shiftLeft_
*	Desc:		Shift some array to left on N elements
*	Input:		void* arr: 		ptr to array shift to
				uint8_t size:	size of element
				uint32_t len: 	length of array
				uint32_t el:	num of elements
*	Output:		none
*/
void _shiftLeft_(uint8_t* arr, uint32_t len, uint32_t el);

/*
*	Function:	_shiftRight_
*	Desc:		Shift some array to right on N elements
*	Input:		void* arr: ptr to array shift to
				uint32_t len: length of array
*	Output:		none
*/
void _shiftRight_(uint8_t* arr, uint32_t len, uint32_t el);

/*
*	Function:	TWI_addPack
*	Desc:		Add package to user queue
*	Input:		uint8_t  addr:			what addr of slave set to
				const uint8_t* data:	pointer to data array
				uint8_t len:			num of bytes in data array
				uint8_t mode:			read or write mode use to
*	Output:		none
*/
void TWI_addPack(uint8_t addr, const uint8_t* data, uint8_t len, uint8_t mode);

/*
*	Function:	TWI_addPackSingle
*	Desc:		Add single-byte package to user queue
*	Input:		uint8_t  addr:		what addr of slave set to
				uint8_t data:		byte send to
				uint8_t mode:		read or write mode use to
*	Output:		none
*/
void TWI_addPackSingle(uint8_t addr, uint8_t data, uint8_t mode);

/*
*	Function:	TWI_addPackDouble
*	Desc:		Add double-byte package to user queue
*	Input:		uint8_t  addr:		what addr of slave set to
				uint16_t data:		byte send to
				uint8_t mode:		read or write mode use to
*	Output:		none
*/
void TWI_addPackDouble(uint8_t addr, uint16_t data, uint8_t mode);

/*
*	Function:	TWI_getByte
*	Desc:		Get byte from input array(if have)
*	Input:		none
*	Output:		uint8_t: readed byte (0xFF if nothing to read)
*/
uint8_t TWI_getByte(void);

/*
*	Function: 	TWI_write
*	Desc:		Write a byte to reg on slave device
*	Input:		uint8_t addr: slave device addr
				uint8_t reg: what reg write to
				uint8_t data: what write to
*	Output:		none
*/
void TWI_write(uint8_t addr, uint8_t reg, uint8_t data);


/*
*	Function: 	TWI_reqRead
*	Desc:		Request a byte from reg on slave device
*	Input:		uint8_t addr: slave device addr
				uint8_t reg: what reg read from
				uint8_t len: len of data in bytes
*	Output:		none
*/
void TWI_reqRead(uint8_t addr, uint8_t reg, uint8_t len);


/*
*	Function:	TWI_start
*	Desc:		Start TWI state machine
*	Input:		none
*	Output:		none
*/
void TWI_start(void);

/*
*	Function:	TWI_stop
*	Desc:		Stop TWI state machine
*	Input:		none
*	Output:		none
*/
void TWI_stop(void);


/*
*	Function:	TWI_hadRead
*	Desc:		If have new bytes to read return 1(t), else 0(f)
*	Input:		none
*	Output:		bool
*/
inline bool TWI_hadRead(void)
{
	return (_twi_in_len > 0);
}
