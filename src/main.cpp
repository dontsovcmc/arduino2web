#include "Arduino.h"

#include "Coffee_AC_Sensor.h"
#include "Coffee_BMP180_Sensor.h"
#include "Coffee_Dallas_Sensor.h"
#include "Coffee_DHT_Sensor.h"
#include "Coffee_Analog_Pin.h"

#define BUF_LEN 150

CoffeeACSensor ac_all(A2, VPERAMP_30A, 75, 0.13);
CoffeeACSensor ac_pump(A3, VPERAMP_5A, 75, 0.02);
CoffeeBMP180Sensor pressure_sensor;
CoffeeDallasSensor temp_heater(3);
CoffeeDallasSensor temp_floor(4);
CoffeeDHTSensor  outside_sensor(7, DHT11);
CoffeeAnalogPin  light(A1);

int float2str(char *buf, int len, float f, uint8_t precision)
{
    char temp[20];
    char *p;
    p = dtostrf(f, 0, precision, temp);
    return snprintf(buf, len, "%s", temp);
}

int append_parameter(char *buf, int len, char *title, float value, uint8_t precision)
{ 
    int i = snprintf(buf, len, "%s", title);
    return i + float2str(buf+i, len-i, value, precision);
}

int append_parameter(char *buf, int len, char *title, uint16_t value)
{ 
    return snprintf(buf, len, "%s%d", title, value);
}


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
    uint16_t light_value = light.getValue();

    //Serial.print(millis()-start); Serial.println(" all"); start = millis();

    char buffer[BUF_LEN];
    char *ch;
    int i = 0;

    i += append_parameter(&buffer[i], BUF_LEN-i, "ac_all=", ac_all_data, 2);
    i += append_parameter(&buffer[i], BUF_LEN-i, ";ac_pump=", ac_pump_data, 2);
    i += append_parameter(&buffer[i], BUF_LEN-i, ";t_inside=", temperature_inside, 2);
    i += append_parameter(&buffer[i], BUF_LEN-i, ";pressure=", hg_pressure, 2);
    i += append_parameter(&buffer[i], BUF_LEN-i, ";t_heater=", temp_heater_data, 2);
    i += append_parameter(&buffer[i], BUF_LEN-i, ";t_floor=", temp_floor_data, 2);
    i += append_parameter(&buffer[i], BUF_LEN-i, ";h_outside=", humid_outside, 2);
    i += append_parameter(&buffer[i], BUF_LEN-i, ";t_outside=", temp_outside, 2);
    i += append_parameter(&buffer[i], BUF_LEN-i, ";case=", light_value);
    i += snprintf(&buffer[i], BUF_LEN-i, ";");
    Serial.println(buffer);
}

