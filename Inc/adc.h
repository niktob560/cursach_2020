#ifndef __ADC_H__
#define __ADC_H__ 1

#include <main.h>

/*
* Function: ADCEnable
* Desc:     Включить АЦП
* Input:    none
* Output:   none
*/
void ADCEnable(void);

/*
* Function: ADCDisable
* Desc:     Выключить АЦП
* Input:    none
* Output:   none
*/
void ADCDisable(void);

/*
* Function: ADCStartConvert
* Desc:     Запустить преобразования
* Input:    none
* Output:   none
*/
void ADCStartConvert(void);

/*
* Function: ADCStopConvert
* Desc:     Остановить преобразования
* Input:    none
* Output:   none
*/
void ADCStopConvert(void);

/*
* Function: ADCFlush
* Desc:     Очистить регистры АЦП
* Input:    none
* Output:   none
*/
void ADCFlush(void);

/*
* Function: ADCInit
* Desc:     Инициализировать АЦП
* Input:    none
* Output:   none
*/
void ADCInit(void);

/*
* Function: analogRead
* Desc:     Получить значение измерения
* Input:    __pin: канал АЦП
* Output:   измерение
*/
uint16_t ADCGetPin(uint8_t _pin);

/*
* Function: ADCSetPrescaler
* Desc:     Установить предделитель
* Input:    __prescaler: предделитель
* Output:   none
*/
void ADCSetPrescaler(uint8_t __prescaler);


/*
* Function: ADCSetRef
* Desc:     Установить источник опорного напряжения
* Input:    __ref: источник
* Output:   none
*/
void ADCSetRef(uint8_t __ref);


/*
* Function: ADCGetAnalogChanged
* Desc:     Обновлено ли значение после последнего чтения
* Input:    __pin: канал АЦП
* Output:   флаг
*/
bool ADCGetAnalogChanged(uint8_t __pin);


/*
* Function: ADCSetPin
* Desc:     Установить текущий Muxer
* Input:    __pin: канал АЦП
* Output:   none
*/
void ADCSetPin(uint8_t __pin);


/*================================Настройки================================*/

#define NUM_OF_ANALOG_PINS 	2
#define ADC_MUX_MASK		0x1F
#define ADC_DATA_MASK       1023
#define ADC_CHANGED_MASK    1024



/*===========================Таблица параметров===========================*/

/*---------------------------Опорное напряжение---------------------------*/
#define ADC_REF_AREF                   0							/*За опорное берется AREF*/
#define ADC_REF_AVCC                   (1 << REFS0)					/*За опорное берется AVCC с внешним конденсатором на ножке AREF*/
#define ADC_REF_INT_2_56V              ((1 << REFS0) | (1 << REFS1))/*Внутреннее 2.56V с внешним конденсатором на ножке AREF*/

/*-----------------------------Управление АЦП-----------------------------*/
#define ADC_CONTROL_ENABLE             (1 << ADEN)					/*Включение АЦП*/
#define ADC_CONTROL_START_CONVERTION   (1 << ADSC)					/*Старт преобразования*/
#define ADC_CONTROL_INTERRUPT_FLAG_EN  (1 << ADIF)					/*Поднять флаг по окончанию преобразования*/
#define ADC_CONTROL_INTERRUPT_EN       (1 << ADIE)					/*Разрешить прерывание по окончанию преобразования*/

/*------------------------------Предделители------------------------------*/
#define ADC_PRESCALER_MASK            ((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0))	/*Маска для очистки*/
#define ADC_PRESCALER_2               (1 << ADPS0)									/*2*/
#define ADC_PRESCALER_4               (1 << ADPS1)									/*4*/
#define ADC_PRESCALER_8               ((1 << ADPS0) | (1 << ADPS1))					/*8*/
#define ADC_PRESCALER_16              (1 << ADPS2)									/*16*/
#define ADC_PRESCALER_32              ((1 << ADPS2) | (1 << ADPS0))					/*32*/
#define ADC_PRESCALER_64              ((1 << ADPS2) | (1 << ADPS1))					/*64*/
#define ADC_PRESCALER_128             ((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0))	/*128*/




#endif
