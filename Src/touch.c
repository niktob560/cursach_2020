#include <touch.h>

volatile bool touchWannaSwitch = false;
volatile uint8_t currADCMuxer = 0;
volatile vect TouchCoords = {TOUCH_ADC_ZERO_X, TOUCH_ADC_ZERO_Y};

/*
*	Function: 	TouchChannels
*	Desc:		Произвести операции с каналами АЦП
*	Input:		none
*	Output:		none
*/
void TouchChannels(void)
{
	if(touchWannaSwitch)
	{
		if(currADCMuxer == 0)
			currADCMuxer = 1;
		else
			currADCMuxer = 0;
		
		ADCSetPin(currADCMuxer);

		touchWannaSwitch = false;
	}
	else
	{
		TouchCoords = TouchGetCoords((dvect){
			ADCGetPin(TOUCH_ADC_MUX_X), 
			ADCGetPin(TOUCH_ADC_MUX_Y)});
		touchWannaSwitch = true;
	}
}



/*
*	Function: 	TouchTask
*	Desc:		Задача проверки нажатий
*	Input:		none
*	Output:		none
*/
void TouchTask(void)
{
						/*Если произошло нажатие*/
	if(TouchCoords.a > TOUCH_ADC_ZERO_X || TouchCoords.b > TOUCH_ADC_ZERO_Y)
	{
		ClickHandler(TouchCoords);
		TouchCoords = (vect){TOUCH_ADC_ZERO_X, TOUCH_ADC_ZERO_Y};
	}
}

/*
*	Function: 	ClickHandler
*	Desc:		Обработчик нажатия
*	Input:		click: координаты нажатия
*	Output:		none
*/
void ClickHandler(vect click)
{
	for(uint8_t i = 0; i < GOBJECT_BUTTONS; i++)
	{
		const vect 	coords = LayoutButtons[i].coords,
					size = LayoutButtons[i].size;
		if(click.a >= coords.a && click.a <= coords.a + size.a
		&& click.b >= coords.b && click.b <= coords.b + size.b)
		{
			ButtonClickHandler(LayoutButtons[i].clickSignal);
		}
	}
}

/*
*	Function: 	ButtonClickHandler
*	Desc:		Обработчик нажатий кнопок
*	Input:		clickCode: код нажатия
*	Output:		none
*/
void ButtonClickHandler(uint8_t clickCode)
{
	switch (clickCode)
	{
		case LAYOUT_BUTTON_SETTINGS:
		{
			LayoutSetDateSet();
			break;
		}
		case LAYOUT_BUTTON_H_UP:
		{
			break;
		}
		case LAYOUT_BUTTON_H_DOWN:
		{
			break;
		}
		case LAYOUT_BUTTON_M_UP:
		{
			break;
		}
		case LAYOUT_BUTTON_M_DOWN:
		{
			break;
		}
		case LAYOUT_BUTTON_S_UP:
		{
			break;
		}
		case LAYOUT_BUTTON_S_DOWN:
		{
			break;
		}
		case LAYOUT_BUTTON_D_UP:
		{
			break;
		}
		case LAYOUT_BUTTON_D_DOWN:
		{
			break;
		}
		case LAYOUT_BUTTON_m_UP:
		{
			break;
		}
		case LAYOUT_BUTTON_m_DOWN:
		{
			break;
		}
		case LAYOUT_BUTTON_Y_UP:
		{
			break;
		}
		case LAYOUT_BUTTON_Y_DOWN:
		{
			break;
		}
		case LAYOUT_BUTTON_DAY_UP:
		{
			break;
		}
		case LAYOUT_BUTTON_DAY_DOWN:
		{
			break;
		}
		case LAYOUT_BUTTON_SUBMIT:
		{
			DS1307WriteData((datetime){0, 0, 0, 0, 0, 0, 0});
			LayoutSetMainmenu();
			break;
		}
	}
}