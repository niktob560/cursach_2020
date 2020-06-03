#ifndef __TOUCH_H__
#define __TOUCH_H__

#include <main.h>
#include <glcd.h>

#define TOUCH_ADC_ZERO_X 0
#define TOUCH_ADC_ZERO_Y 0
#define TOUCH_ADC_MAX_X 1023
#define TOUCH_ADC_MAX_Y 1023


/*
*	Function: 	TouchGetX
*	Desc:		Преобразовать координаты полученные из АЦП в координаты дисплея
*	Input:		x_adc: координата из АЦП
*	Output:		координата на дисплее
*/
static inline uint8_t TouchGetX(uint16_t x_adc)
{
	return (uint8_t)(((x_adc - TOUCH_ADC_ZERO_X) * GLCD_WIDTH) / TOUCH_ADC_MAX_X);
}

/*
*	Function: 	TouchGetY
*	Desc:		Преобразовать координаты полученные из АЦП в координаты дисплея
*	Input:		y_adc: координата из АЦП
*	Output:		координата на дисплее
*/
static inline uint8_t TouchGetY(uint16_t y_adc)
{
	return (uint8_t)(((y_adc - TOUCH_ADC_ZERO_Y) * GLCD_HEIGHT) / TOUCH_ADC_MAX_Y);
}

/*
*	Function: 	TouchGetCoords
*	Desc:		Преобразовать координаты полученные из АЦП в координаты дисплея
*	Input:		adc: координата из АЦП
*	Output:		координата на дисплее
*/
static inline vect TouchGetCoords(dvect adc)
{
	return (vect){TouchGetX(adc.a), TouchGetY(adc.b)};
}

#endif