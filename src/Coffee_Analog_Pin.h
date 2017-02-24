#ifndef COFFEE_ANALOG_PIN_H
#define COFFEE_ANALOG_PIN_H
 
#include "Arduino.h"

class CoffeeAnalogPin
{
public:
	CoffeeAnalogPin(uint8_t pin)
	: pin_(pin)
	{}

	//light in percent 0-100
	uint16_t getValue()
	{
		return analogRead(pin_) / 1024.0 * 100.0;
	}

private:
	uint8_t pin_;
};


#endif //COFFEE_ANALOG_PIN_H
