#include <adc.h>

uint8_t _analogRef;
volatile uint16_t _analogPins[NUM_OF_ANALOG_PINS];
volatile uint8_t _currPin = 0;

/*
* Function ADCSetAnalogChanged
* Desc     Set state of "isNewMeasure"
* Input    __pin: state of what pin?
* 			__state: state to set
* Output   none
*/
void ADCSetAnalogChanged(uint8_t __pin, uint8_t __state)
{
	_analogPins[__pin] = (_analogPins[__pin] & (uint8_t)(~ADC_CHANGED_MASK)) | (uint8_t)(__state * ADC_CHANGED_MASK);
}

/*
* Function ADCGetAnalogChanged
* Desc     Return state of "isNewMeasure"
* Input    __pin: what pin get state
* Output   state
*/
bool ADCGetAnalogChanged(uint8_t __pin)
{
	return (_analogPins[__pin] & ADC_CHANGED_MASK) != 0;
}



/*
* Function ADCSendControl
* Desc     Set control signal to ADC
* Input    _contr: control signal
* Output   none
*/
void ADCSendControl(uint8_t __contr)
{
	ADCSRA |= __contr;
}

/*
* Function ADCSetRef
* Desc     Set analog reference source
* Input    __ref: analog reference source
* Output   none
*/
void ADCSetRef(uint8_t __ref)
{
	ADMUX |= __ref;
	_analogRef = __ref;
}

/*
* Function ADCSetPrescaller
* Desc     Set ADC prescaller
* Input    __prescaller: prescaller to set
* Output   none
*/
void ADCSetPrescaller(uint8_t __prescaller)
{
	ADCSRA = (uint8_t)((ADCSRA & ~ADC_PRESCALLER_MASK) | __prescaller);
}

/*
* Function ADCEnable
* Desc     Start ADC
* Input    none
* Output   none
*/
void ADCEnable(void)
{
	ADCSendControl(ADC_CONTROL_ENABLE);
}

/*
* Function ADCDisable
* Desc     Stop ADC
* Input    none
* Output   none
*/
void ADCDisable(void)
{
	ADCSRA = (uint8_t)(ADCSRA & ~ADC_CONTROL_ENABLE);
}

/*
* Function ADCStartConvert
* Desc     Start converting
* Input    none
* Output   none
*/
void ADCStartConvert(void)
{
	ADCSendControl(ADC_CONTROL_START_CONVERTION);
}

/*
* Function ADCStopConvert
* Desc     Stop converting
* Input    none
* Output   none
*/
void ADCStopConvert(void)
{
	ADCSRA = (uint8_t)(ADCSRA & ~ADC_CONTROL_START_CONVERTION);
}

/*
* Function ADCFlush
* Desc     Clear registers
* Input    none
* Output   none
*/
void ADCFlush(void)
{
	#ifdef ADCSRB
	ADCSRA = 0;
	ADCSRB = 0;
	#else
	ADCSR = 0;
	#endif
}


/*
* Function ADCInit
* Desc     Initialize ADC
* Input    none
* Output   none
*/
void ADCInit(void)
{
	for(uint8_t i = 0; i < NUM_OF_ANALOG_PINS; i++)
		_analogPins[i] = 0;
	ADCFlush();
	ADCSetRef(ADC_REF_AVCC);
	ADMUX |= _currPin;
	ADCSetPrescaller(ADC_PRESCALLER_32);
	ADCSendControl(ADC_CONTROL_INTERRUPT_EN);
	ADCEnable();
	ADCStartConvert();
}


/*
* Function analogRead
* Desc     Return measurment of pin
* Input    __pin: pin for returning measurment
* Output   measurment
*/
int analogRead(uint8_t __pin)
{
	ADCSetAnalogChanged(__pin, 0);
	return _analogPins[__pin] & ADC_DATA_MASK;
}

/*
* Function ISR(ADC_vect)
* Desc     Interrupt handler for vector ADC_vect
* Input    Interrupt vector
* Output   none
*/
ISR(ADC_vect)
{
	_analogPins[_currPin] = (uint16_t)(ADCL | (ADCH << 8));
	ADCSetAnalogChanged(_currPin, 1);
	_currPin++;
	if(_currPin >= NUM_OF_ANALOG_PINS)
	{
		_currPin = 0;
	}
	ADMUX = (uint8_t)(_analogRef | (_currPin & ADC_MUX_MASK));
}