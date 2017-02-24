#ifndef COFFEE_DHT_SENSOR_H
#define COFFEE_DHT_SENSOR_H

#include "DHT.h"
 
class CoffeeDHTSensor
{
public:

	CoffeeDHTSensor(uint8_t pin, uint8_t dht_type)
	: work_(false)
	, pin_(pin)
	, dht_type_(dht_type)
	, dht(pin, dht_type)
	{}

	//call begin() in setup()
	void begin()
	{
		dht.begin();
		work_ = true;
	}

	//in C
	float getTemperature()
	{
		if (!work_) return 0.0;
		float t = dht.readTemperature();
		if (isnan(t)) return 0.0;
		return t;
	}

	float getHumidity()
	{
		if (!work_) return 0.0;
		float h = dht.readHumidity();
		if (isnan(h)) return 0.0;
		return h;
	}


	bool work()
	{
		return work_;
	}

private:
	bool work_;

	uint8_t pin_;
	uint8_t dht_type_;
	DHT dht;
};


#endif //COFFEE_DHT_SENSOR_H
