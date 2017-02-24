#include "Arduino.h"

#include "Coffee_AC_Sensor.h"
#include "Coffee_BMP180_Sensor.h"

CoffeeACSensor ac_all(A2, VPERAMP_30A, 75, 0.13);
CoffeeACSensor ac_pump(A3, VPERAMP_5A, 75, 0.02);
CoffeeBMP180Sensor pressure_sensor;

void setup()
{ 
    Serial.begin(9600);

    pressure_sensor.begin();
}

void loop()
{

    float ac_all_data = ac_all.getAmpsRMS();
    float ac_pump_data = ac_pump.getAmpsRMS();

    float temperature_inside = pressure_sensor.getTemperature();
    float hg_pressure = pressure_sensor.getPressure();

    Serial.print(ac_all_data);
    Serial.println(" A RMS all");
    Serial.print(ac_pump_data);
    Serial.println(" A RMS pump");
    Serial.print(temperature_inside);
    Serial.println(" C temp inside");
    Serial.print(hg_pressure);
    Serial.println(" hg pressure");


    delay(300);
}

