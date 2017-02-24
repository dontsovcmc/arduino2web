#include "Arduino.h"

#include "Coffee_AC_Sensor.h"
#include "Coffee_BMP180_Sensor.h"
#include "Coffee_Dallas_Sensor.h"
#include "Coffee_DHT_Sensor.h"

CoffeeACSensor ac_all(A2, VPERAMP_30A, 75, 0.13);
CoffeeACSensor ac_pump(A3, VPERAMP_5A, 75, 0.02);
CoffeeBMP180Sensor pressure_sensor;
CoffeeDallasSensor temp_heater(3);
CoffeeDallasSensor temp_floor(4);
CoffeeDHTSensor  outside_sensor(7, DHT11);


void setup()
{ 
    Serial.begin(9600);

    pressure_sensor.begin();
    temp_heater.begin();
    temp_floor.begin();
    outside_sensor.begin();
}

void loop()
{
    //uint32_t start = millis();
    float ac_all_data = ac_all.getAmpsRMS();
    float ac_pump_data = ac_pump.getAmpsRMS();

    float temperature_inside = pressure_sensor.getTemperature();
    float hg_pressure = pressure_sensor.getPressure();

    float temp_heater_data = temp_heater.getTemperature();
    float temp_floor_data = temp_floor.getTemperature();

    float humid_outside = outside_sensor.getHumidity();
    float temp_outside = outside_sensor.getTemperature();
    //Serial.print(millis()-start); Serial.println(" all"); start = millis();

/*
    Serial.println("*********");

    Serial.print(ac_all_data);
    Serial.println(" A RMS all");
    Serial.print(ac_pump_data);
    Serial.println(" A RMS pump");

    Serial.print(temperature_inside);
    Serial.println(" C temp inside");
    Serial.print(hg_pressure);
    Serial.println(" hg pressure");

    Serial.print(temp_heater_data);
    Serial.println(" C temp heater");
    Serial.print(temp_floor_data);
    Serial.println(" C temp bottom");

    Serial.print("Humidity: ");
    Serial.print(humid_outside);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.println(temp_outside);

    Serial.println("*********");*/

    delay(1000);
}

