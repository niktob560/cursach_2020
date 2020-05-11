#ifndef __ADC_H__
#define __ADC_H__ 1

#include <main.h>

void ADCEnable(void);
void ADCDisable(void);
void ADCStartConvert(void);
void ADCStopConvert(void);
void ADCFlush(void);
void ADCInit(void);
uint16_t ADCGetPin(uint8_t _pin);





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
#define ADC_PRESCALLER_MASK            ((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0))	/*Маска для очистки*/
#define ADC_PRESCALLER_2               (1 << ADPS0)									/*2*/
#define ADC_PRESCALLER_4               (1 << ADPS1)									/*4*/
#define ADC_PRESCALLER_8               ((1 << ADPS0) | (1 << ADPS1))				/*8*/
#define ADC_PRESCALLER_16              (1 << ADPS2)									/*16*/
#define ADC_PRESCALLER_32              ((1 << ADPS2) | (1 << ADPS0))				/*32*/
#define ADC_PRESCALLER_64              ((1 << ADPS2) | (1 << ADPS1))				/*64*/
#define ADC_PRESCALLER_128             ((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0))	/*128*/




#endif
