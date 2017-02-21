// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"

#define BUF_LEN 30

#define DHTPIN 3    

DHT dht(DHTPIN, DHT11);

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");

  pinMode(2, OUTPUT);   
  pinMode(4, OUTPUT);   
  digitalWrite(2, HIGH);
  digitalWrite(4, LOW);  
  
  dht.begin();
}

void loop() {

  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    return;
  }

  char buf[BUF_LEN];
  char outstr[15], outstr2[15];
  dtostrf(h,0,1, outstr);
  dtostrf(t,0,1, outstr2);
  sprintf (&buf[0], "%s;%s\n", outstr, outstr2);
  Serial.print(buf);
  //Serial.print("Humidity: ");
  //Serial.print(h);
  //Serial.print(" %\t");
  //Serial.print("Temperature: ");
  //Serial.print(t);
  //Serial.print(" *C\n");

}