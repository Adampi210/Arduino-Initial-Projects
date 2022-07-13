/*
 * This project shows how to use a DHT-11 humidity sensor, which can read the humidity and temperature of its surroundings.
 * DHT-11 is a digital sensor that uses a modified OneWire interface to communicate. Just like the DS18B20, the data pin has to 
 * be connected to Vss with a pull-up resistor. The temperature measurement range is 0 to 50*C +-2*C and
 * the humidity measurement range is 20-95%RH +-5%. (Note: RH = relative humidity, 0% == dry air
 * 100% == max vapor concentration -> water starts forming). Finall, I am using here the
 * arduino-DHT library: https://github.com/markruys/arduino-DHT.git
 * DHT-11 datasheet: https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf
 */

#include "DHT.h"

#define DHT11_SENSOR 2
#define BAUD_RATE 9600

DHT dht_0; // Initialize thr DHT sensor object
 
void setup()
{
  Serial.begin(BAUD_RATE);
  dht_0.setup(DHT11_SENSOR); // begin communication with the dht-11 sensor
}
 
void loop()
{
  get_humidity_and_temp(dht_0);
  delay(200);
}

// The function below gets the humidity from the dht-11 sensor and prints it to the serial monitor
void get_humidity_and_temp(DHT dht) {
  float humidity = dht.getHumidity();       // Initialize and read humidity
  float temperature = dht.getTemperature(); // Initialize and read temperature

  // If the connection was established properly (no errors) print the read values to the serial monitor
  if(dht.getStatusString() == "OK") {
    Serial.print("Humidity: " + String(humidity) + "%RH ");
    Serial.println("Temperature: " + String(temperature) + "*C");
  }

  // Wait until next measurement can be taken
  delay(dht.getMinimumSamplingPeriod());
}
