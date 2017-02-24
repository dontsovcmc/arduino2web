#ifndef COFFEE_AC_SENSOR_H
#define COFFEE_AC_SENSOR_H
#include "Arduino.h"
 
//185 for 5A, 100 for 20A Module and 66 for 30A Module
#define VPERAMP_30A 66
#define VPERAMP_20A 100
#define VPERAMP_5A  185

class CoffeeACSensor
{
public:

	CoffeeACSensor(uint8_t pin, uint16_t mVperAmp, uint16_t read_ms = 75, float noise_mA = 0.0)
	: pin_(pin)
	, mVperAmp_(mVperAmp)
	, read_ms_(read_ms)
	, noise_mA_(noise_mA)
	{}

	//null value 0.05 for 30A
	float getAmpsRMS()
	{
		float VRMS;
		VRMS = (getVPP()/2.0) *0.707; 
		return (VRMS * 1000.0)/(mVperAmp_ * 1.0) - noise_mA_;
	}

private:
	float getVPP()
	{
	  	int readValue;          // value read from the sensor
	  	int maxValue = 0;       // store max value here
	  	int minValue = 1024;	// store min value here
	  
	   	uint32_t start_time = millis();
		while((millis()-start_time) < read_ms_)
		{
		   	readValue = analogRead(pin_);  //100mcsec in UNO
		   	if (readValue > maxValue) 
		      	maxValue = readValue;

		   	if (readValue < minValue) 
				minValue = readValue;
		}

	   	return ((maxValue - minValue) * 5.0)/1024.0;
	}

	uint8_t pin_;       //arduino pin
	uint16_t mVperAmp_; //sensor sensitive 
	uint16_t read_ms_;  //time to read data from sensor
	float noise_mA_;    //maybe there is a noise, minus from getAmpsRMS
};


#endif //COFFEE_AC_SENSOR_H
