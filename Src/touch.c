#include <touch.h>

volatile bool touchWannaSwitch = false;
volatile uint8_t currADCMuxer = 0;
volatile vect TouchCoords = {0, 0};

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