/*
 * In this project I measure the temperature with Arduino.
 * There are various sensors that can do that, and here I show how to use two 
 * that differ in the way they read the temperature:
 *  - LM35 = an analog temperature sensor, datasheet: https://www.ti.com/lit/ds/symlink/lm35.pdf
 *  - DS18B20 = a programmable digital thermometer, datasheet: https://datasheets.maximintegrated.com/en/ds/DS18B20.pdf
 * One sensor is analog - it translates the measured value into an electrical signal, proportional
 * to the measurement. The other sensor is digital - uses digital circuitry to read the information in the 
 * form of bits and returns that information. 
 */

// Include libraries to communicate with and use the DS18B20 sensor
#include <OneWire.h>
#include <DallasTemperature.h>

#define BAUD_RATE 9600
#define VSS 5.0
#define LM35_SENSOR A0 // To read the analog output I connet the sensor to LM35
#define DS18B20_SENSOR 0 //

// The initial values set should be easy to overwrite by te measurements
float tempMAX = 0;    // the initial value of the tempMAX should be minimum possible temperature = 0*C
float tempMIN = 150;  //the initial value of the tempMIN should be maximum possible temperature = 150*C

void setup() {
  Serial.begin(BAUD_RATE);
  
}

void loop() {
  // read the temperature from the LM35 sensor
  // read_temp_LM35(LM35_SENSOR);

  // read and save max and min temperatures from the LM35 sensors
  read_max_min_temp_LM35(&tempMAX, &tempMIN, LM35_SENSOR);
}

// The function below reads the temperature from the LM35 analog sensor
void read_temp_LM35(int LM35) {
  
  // Initialize temperature, read the value from the sensor, and convert it to degrees celsius
  // First, use analogRead to read the value from LM35 sensor
  // Then to get read voltage divide by 1024 (analogRead reads value from 0 to 1023) and multiply by supply voltage
  // Finally, in the datasheet in subsectio 8.2.1.1, the temperature slope is 10mV/deg Celcius
  // So 100 degCelcius / 1V, which is why I multiply by 100
  float temperature = (analogRead(LM35) * VSS / 1024.0) * 100;

  // Then print the temperature
  Serial.print("Current temperature reading: ");
  Serial.print(temperature);
  Serial.println("*C");

  delay(200);
}

// The function below checks for maximum and minimum measured temperature
void read_max_min_temp_LM35(float* temp_MAX, float* temp_MIN, int LM35) {
  float temperature = (analogRead(LM35) * VSS / 1024.0) * 100; // Initialize and calculate temperature

  // If the calculated temperature is higher than the current max value then set that value to max value and print it out to the serial monitor
  if(temperature > *temp_MAX) {
    *temp_MAX = temperature;
    Serial.print("New max temperature: ");
    Serial.print(*temp_MAX);
    Serial.println("*C");
    
  }

  // If the calculated temperature is lower than the current min value then set that value to min value and print it out to the serial monitor
  if(temperature < *temp_MIN) {
    *temp_MIN = temperature;
    Serial.print("New min temperature: ");
    Serial.print(*temp_MIN);
    Serial.println("*C");
  }

  delay(200);
}

// TODO DS18B20 functions
