#ifndef COFFEE_DALLAS_SENSOR_H
#define COFFEE_DALLAS_SENSOR_H
#include <OneWire.h>
#include <DallasTemperature.h>
 
class CoffeeDallasSensor
{
public:

	CoffeeDallasSensor(uint8_t pin)
	: work_(false)
	, pin_(pin)
	, oneWire(pin)
	, sensors(&oneWire)
	{}

	//call begin() in setup()
	void begin()
	{
		sensors.begin();
  		sensors.setWaitForConversion(false); //requestTemperatures() will not block current thread
		sensors_detected_ = sensors.getDeviceCount();
		work_ = sensors_detected_ > 0;
	}

	//in C
	float getTemperature(uint8_t index=0)
	{
		if (!work_ || index >= sensors_detected_) return 0.0;
		sensors.requestTemperatures();
  		return sensors.getTempCByIndex(index);
	}

	bool work()
	{
		return work_;
	}

private:
	bool work_;
	uint8_t sensors_detected_;
	uint8_t pin_;
	OneWire oneWire;
	DallasTemperature sensors;
};


#endif //COFFEE_DALLAS_SENSOR_H
