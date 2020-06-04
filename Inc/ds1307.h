#ifndef __DS1307_h__
#define __DS1307_h__ 1

#include <main.h>
#include <twi.h>

#define DS1307_I2C_ADDR  	0x68
#define DS1307_SEC_ADDR  	0x00
#define DS1307_MIN_ADDR  	0x01
#define DS1307_HOUR_ADDR 	0x02
#define DS1307_DAY_ADDR  	0x03
#define DS1307_DATE_ADDR 	0x04
#define DS1307_MONTH_ADDR	0x05
#define DS1307_YEAR_ADDR 	0x06
#define DS1307_CONTROL_ADDR 0x07
#define DS1307_SLAVE_ADDR	0x68

typedef enum
{
	Sunday 		= 0,	/*Воскресенье*/
	Monday 		= 1,	/*Понедельник*/
	Tuesday 	= 2,	/*Вторник*/
	Wensday 	= 3,	/*Среда*/
	Thursday 	= 4,	/*Четверг*/
	Friday 		= 5,	/*Пятница*/
	Saturday 	= 6		/*Суббота*/
} Day;

static const char DayOfWeekStrings[7][4] = {	"Sun",
												"Mon",
												"Tue",
												"Wen",
												"Thu",
												"Fri",
												"Sat"
												};


/*Ф-ции преобразования в дату-время из регистров, полученных из памяти часов*/

static inline uint8_t 	DS1307Halt(const uint8_t reg) { return reg >> 7; }


static inline uint8_t 	DS1307Sec(const uint8_t reg) 
{
	return (uint8_t)((reg & 0x0F) + (((reg >> 4) & 0x07) * 10));
}


static inline uint8_t 	DS1307Min(const uint8_t reg) 
{
	return (uint8_t)((reg & 0x0F) + ((reg >> 4) * 10));
}


static inline uint8_t 	DS1307Hour(const uint8_t reg) 
{
	return (uint8_t)((reg & 0x0F) + (((reg >> 4) & 1) * 10));
}


static inline uint8_t 	DS1307Date(const uint8_t reg) 
{
	return (uint8_t)((reg & 0x0F) + ((reg >> 4) * 10));	
}


static inline uint8_t 	DS1307Month(const uint8_t reg) 
{
	return (uint8_t)((reg & 0x0F) + ((reg >> 4) * 10));
}


static inline uint16_t 	DS1307Year(const uint8_t reg) 
{
	return (uint16_t)((reg & 0x0F) + ((reg >> 4) * 10) + 2000);
}


static inline Day DS1307Day(const uint8_t reg) { return reg; }


/*Ф-ции обратного преобразования из даты-времени в регистры памяти часов*/


static inline uint8_t DS1307ToSec(const uint8_t sec) 
{
	return (uint8_t)(((sec / 10) << 4) | ((sec % 10) & 0x0F));
}


static inline uint8_t DS1307ToMin(const uint8_t min) 
{
	return (uint8_t)(((min / 10) << 4) | ((min % 10) & 0x0F));
}


static inline uint8_t DS1307ToHour(const uint8_t hour) 
{
	return (uint8_t)(((hour / 10) << 4) | ((hour % 10) & 0x0F));
}


static inline uint8_t DS1307ToDate(const uint8_t date) 
{
	return (uint8_t)(((date / 10) << 4) | ((date % 10) & 0x0F));
}


static inline uint8_t DS1307ToMonth(const uint8_t month) 
{
	return (uint8_t)(((month / 10) << 4) | ((month % 10) & 0x0F));
}


static inline uint8_t DS1307ToYear(const uint16_t year) 
{
	return (uint8_t)((((year % 100) / 10) << 4) | ((year % 10) & 0x0F));
}



static inline Day DS1307ToDay(const uint8_t day) { return day; }



typedef struct 
{
	uint8_t 	seconds,
				minutes,
				hours,
				date,
				month;
	uint16_t 	year;
	Day 		day;
} datetime;

static inline datetime DS1307Datetime(const uint8_t reg[8])
{
	return (datetime)
	{
		DS1307Sec 	(reg[DS1307_SEC_ADDR]),
		DS1307Min 	(reg[DS1307_MIN_ADDR]),
		DS1307Hour 	(reg[DS1307_HOUR_ADDR]),
		DS1307Date 	(reg[DS1307_DATE_ADDR]),
		DS1307Month (reg[DS1307_MONTH_ADDR]),
		DS1307Year 	(reg[DS1307_YEAR_ADDR]),
		DS1307Day 	(reg[DS1307_DAY_ADDR])
	};
}

static inline void DS1307FromDatetime(const datetime DateTime, uint8_t ret[8])
{
	ret[0] = DS1307ToSec(DateTime.seconds);
	ret[1] = DS1307ToMin(DateTime.minutes);
	ret[2] = DS1307ToHour(DateTime.hours);
	ret[3] = DS1307ToDay(DateTime.day);
	ret[4] = DS1307ToDate(DateTime.date);
	ret[5] = DS1307ToMonth(DateTime.month);
	ret[6] = DS1307ToYear(DateTime.year);
}


/*
*	Function: 	DS1307RequestData
*	Desc:		Запросить данные о дате-времени по I2C
*	Input:		none
*	Output:		none
*/
void DS1307RequestData(void);

/*
*	Function: 	DS1307GetData
*	Desc:		Получить текущую дату-время
*	Input:		none
*	Output:		дата-время
*/
datetime DS1307GetData();

/*
*	Function: 	DS1307SaveData
*	Desc:		Соханить данные о дате-времени из I2C
*	Input:		none
*	Output:		none
*/
void DS1307SaveData();

/*
*	Function: 	DS1307WriteData
*	Desc:		Записать новые данные о дате-времени по I2C
*	Input:		new: новая дата-время
*	Output:		none
*/
void DS1307WriteData(datetime new);

/*
*	Function: 	DS1307Halted
*	Desc:		Поднят ли бит CLOCK HALT
*	Input:		none
*	Output:		CLOCK HALT
*/
bool DS1307Halted(void);

#endif