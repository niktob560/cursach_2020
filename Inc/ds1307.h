#ifndef __DS1307_h__
#define __DS1307_h__ 1

#include <main.h>

#define DS1307_I2C_ADDR  	0x68
#define DS1307_SEC_ADDR  	0x00
#define DS1307_MIN_ADDR  	0x01
#define DS1307_HOUR_ADDR 	0x02
#define DS1307_DAY_ADDR  	0x03
#define DS1307_DATE_ADDR 	0x04
#define DS1307_MONTH_ADDR	0x05
#define DS1307_YEAR_ADDR 	0x06
#define DS1307_CONTROL_ADDR 0x07

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

// typedef enum Day Day;


/*Ф-ции преобразования в дату-время из регистров, полученных из памяти часов*/

static inline uint8_t DS1307Halt(const uint8_t reg) {	return reg >> 7; }



static inline uint8_t DS1307Sec1(const uint8_t reg) {	return reg & 0x0F; }



static inline uint8_t DS1307Sec10(const uint8_t reg) { return (reg >> 4) & 0x07; }



static inline uint8_t DS1307Sec(const uint8_t reg) { return (uint8_t)(DS1307Sec1(reg) + (DS1307Sec10(reg) * 10)); }



static inline uint8_t DS1307Min1(const uint8_t reg) { return reg & 0x0F; }



static inline uint8_t DS1307Min10(const uint8_t reg) { return reg >> 4; }



static inline uint8_t DS1307Min(const uint8_t reg) { return (uint8_t)(DS1307Min1(reg) + (DS1307Min10(reg) * 10)); }



static inline uint8_t DS1307Hour1(const uint8_t reg) { return reg & 0x0F; }



static inline uint8_t DS1307Hour10(const uint8_t reg) { return (reg >> 4) & 1; }



static inline uint8_t DS1307Hour(const uint8_t reg) { return (uint8_t)(DS1307Hour1(reg) + (DS1307Hour10(reg) * 10)); }



static inline uint8_t DS1307Date1(const uint8_t reg) { return reg & 0x0F; }



static inline uint8_t DS1307Date10(const uint8_t reg) { return reg >> 4; }



static inline uint8_t DS1307Date(const uint8_t reg) { return (uint8_t)(DS1307Date1(reg) + (DS1307Date10(reg) * 10)); }



static inline uint8_t DS1307Month1(const uint8_t reg) { return reg & 0x0F; }



static inline uint8_t DS1307Month10(const uint8_t reg) { return reg >> 4; }



static inline uint8_t DS1307Month(const uint8_t reg) { return (uint8_t)(DS1307Month1(reg) + (DS1307Month10(reg) * 10)); }



static inline uint8_t DS1307Year1(const uint8_t reg) { return reg & 0x0F; }



static inline uint8_t DS1307Year10(const uint8_t reg) { return reg >> 4; }



static inline uint16_t DS1307Year(const uint8_t reg) { return (uint16_t)(DS1307Year1(reg) + (DS1307Year10(reg) * 10)); }



static inline Day DS1307Day(const uint8_t reg) { return reg; }



typedef struct 
{
	uint8_t seconds,
			minutes,
			hours,
			date,
			month;
	uint16_t year;
	Day day;
} datetime;

static inline datetime DS1307Datetime(const uint8_t reg[8])
{
	return (datetime)
	{
		DS1307Sec(reg[DS1307_SEC_ADDR]),
		DS1307Min(reg[DS1307_MIN_ADDR]),
		DS1307Hour(reg[DS1307_HOUR_ADDR]),
		DS1307Date(reg[DS1307_DATE_ADDR]),
		DS1307Month(reg[DS1307_MONTH_ADDR]),
		DS1307Year(reg[DS1307_YEAR_ADDR]),
		DS1307Day(reg[DS1307_DAY_ADDR])
	};
}

#endif