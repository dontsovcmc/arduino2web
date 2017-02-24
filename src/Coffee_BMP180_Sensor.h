#ifndef COFFEE_BMP180_SENSOR_H
#define COFFEE_BMP180_SENSOR_H
#include <Wire.h>
#include <Adafruit_BMP085.h>
 
class CoffeeBMP180Sensor
{
public:

	//SDA + 4.7k resistor to Vcc
	//SDL + 4.7k resistor to Vcc
	//Vcc = 5 or 3.3V see datasheet (!)
	CoffeeBMP180Sensor()
	: work_(false)
	{}

	//call begin() in setup()
	void begin()
	{
		work_ = bmp180.begin();
	}

	//in C
	float getTemperature()
	{
		if (!work_) return 0.0;
		return bmp180.readTemperature();
	}
	
	//in mm hg
	float getPressure()
	{
		if (!work_) return 0.0;
		return bmp180.readPressure()/133.3;
	}

	bool work()
	{
		return work_;
	}

private:
	Adafruit_BMP085 bmp180;
	bool work_;
};


#endif //COFFEE_BMP180_SENSOR_H
