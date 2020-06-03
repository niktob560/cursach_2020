#include <ds1307.h>

uint8_t DS1307Registers[8] = {0};
volatile uint8_t DS1307RequestedRegisterAddress = 0;

/*
*	Function: 	DS1307RequestData
*	Desc:		Запросить данные о дате-времени по I2C
*	Input:		none
*	Output:		none
*/
void DS1307RequestData(void)
{
	TWIReqRead(DS1307_SLAVE_ADDR, DS1307RequestedRegisterAddress, 1);
}

/*
*	Function: 	DS1307SaveData
*	Desc:		Соханить данные о дате-времени из I2C
*	Input:		none
*	Output:		none
*/
void DS1307SaveData()
{
	DS1307Registers[DS1307RequestedRegisterAddress] = TWIGetByte();
	DS1307RequestedRegisterAddress++;
}

/*
*	Function: 	DS1307GetData
*	Desc:		Получить текущую дату-время
*	Input:		none
*	Output:		дата-время
*/
datetime DS1307GetData()
{
	return DS1307Datetime(DS1307Registers);
}

/*
*	Function: 	DS1307Halted
*	Desc:		Поднят ли бит CLOCK HALT
*	Input:		none
*	Output:		CLOCK HALT
*/
bool DS1307Halted(void)
{
	return DS1307Halt(DS1307Registers[0]);
}


/*
*	Function: 	DS1307WriteData
*	Desc:		Записать новые данные о дате-времени по I2C
*	Input:		new: новая дата-время
*	Output:		none
*/
void DS1307WriteData(datetime new)
{
	uint8_t newRegs[8] = {0};
	DS1307FromDatetime(new, newRegs);
	for(uint8_t i = 0; i < 8; i++)
		TWIWrite(DS1307_SLAVE_ADDR, i, newRegs[i]);
}