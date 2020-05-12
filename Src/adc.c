#include <adc.h>

uint8_t _analogRef;
volatile uint16_t _analogPins[NUM_OF_ANALOG_PINS];
volatile uint8_t _currPin = 0;

/*
* Function: ADCSetAnalogChanged
* Desc:     Установить флаг обновлено ли значение после последнего чтения
* Input:    __pin: канал АЦП
* 			__state: флаг
* Output:   none
*/
void ADCSetAnalogChanged(uint8_t __pin, uint8_t __state)
{
	_analogPins[__pin] = (_analogPins[__pin] & (uint8_t)(~ADC_CHANGED_MASK)) | (uint8_t)(__state * ADC_CHANGED_MASK);
}

/*
* Function: ADCGetAnalogChanged
* Desc:     Обновлено ли значение после последнего чтения
* Input:    __pin: канал АЦП
* Output:   флаг
*/
bool ADCGetAnalogChanged(uint8_t __pin)
{
	return (_analogPins[__pin] & ADC_CHANGED_MASK) != 0;
}



/*
* Function: ADCSendControl
* Desc:     Отправить управляющйю последовательность АЦП
* Input:    _contr: последовательность
* Output:   none
*/
void ADCSendControl(uint8_t __contr)
{
	ADCSRA |= __contr;
}

/*
* Function: ADCSetRef
* Desc:     Установить источник опорного напряжения
* Input:    __ref: источник
* Output:   none
*/
void ADCSetRef(uint8_t __ref)
{
	ADMUX |= __ref;
	_analogRef = __ref;
}

/*
* Function: ADCSetPrescaler
* Desc:     Установить предделитель
* Input:    __prescaler: предделитель
* Output:   none
*/
void ADCSetPrescaler(uint8_t __prescaler)
{
	ADCSRA = (uint8_t)((ADCSRA & ~ADC_PRESCALER_MASK) | __prescaler);
}

/*
* Function: ADCEnable
* Desc:     Включить АЦП
* Input:    none
* Output:   none
*/
void ADCEnable(void)
{
	ADCSendControl(ADC_CONTROL_ENABLE);
}

/*
* Function: ADCDisable
* Desc:     Выключить АЦП
* Input:    none
* Output:   none
*/
void ADCDisable(void)
{
	ADCSRA = (uint8_t)(ADCSRA & ~ADC_CONTROL_ENABLE);
}

/*
* Function: ADCStartConvert
* Desc:     Запустить преобразования
* Input:    none
* Output:   none
*/
void ADCStartConvert(void)
{
	ADCSendControl(ADC_CONTROL_START_CONVERTION);
}

/*
* Function: ADCStopConvert
* Desc:     Остановить преобразования
* Input:    none
* Output:   none
*/
void ADCStopConvert(void)
{
	ADCSRA = (uint8_t)(ADCSRA & ~ADC_CONTROL_START_CONVERTION);
}

/*
* Function: ADCFlush
* Desc:     Очистить регистры АЦП
* Input:    none
* Output:   none
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
* Function: ADCInit
* Desc:     Инициализировать АЦП
* Input:    none
* Output:   none
*/
void ADCInit(void)
{
	for(uint8_t i = 0; i < NUM_OF_ANALOG_PINS; i++)
		_analogPins[i] = 0;
	ADCFlush();
	ADCSetRef(ADC_REF_AVCC);
	ADMUX |= _currPin;
	ADCSetPrescaler(ADC_PRESCALER_32);
	ADCSendControl(ADC_CONTROL_INTERRUPT_EN);
	ADCEnable();
	ADCStartConvert();
}


/*
* Function: analogRead
* Desc:     Получить значение измерения
* Input:    __pin: канал АЦП
* Output:   измерение
*/
uint16_t ADCGetPin(uint8_t __pin)
{
	ADCSetAnalogChanged(__pin, 0);
	return _analogPins[__pin] & ADC_DATA_MASK;
}

/*
* Function: ISR(ADC_vect)
* Desc:     Обработчик прерывания АЦП
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