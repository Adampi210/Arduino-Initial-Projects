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
#include <OneWire.h> // Communication with the sensor is done with one wire
#include <DallasTemperature.h> // This library allows for easier control of the temperature sensor

#define BAUD_RATE 9600
#define VSS 5.0
#define LM35_SENSOR A0 // To read the analog output I connet the sensor to LM35
#define DS18B20_SENSOR A1 // DS18B20 is connected to A1
#define DS18B20_NUM_OF 1

// The initial values set should be easy to overwrite by te measurements
float tempMAX = 0;    // the initial value of the tempMAX should be minimum possible temperature = 0*C
float tempMIN = 150;  //the initial value of the tempMIN should be maximum possible temperature = 150*C

OneWire communication_line(DS18B20_SENSOR); // First initialize a OneWire object at pin DS18B20_SENSOR
DallasTemperature DS18B20_sensor(&communication_line); // Then initialize the DS18B20 sensor that communicates via OneWire

void setup() {
  Serial.begin(BAUD_RATE);
  DS18B20_sensor.begin(); // Begin communication with the DS18B20 sensor
}

void loop() {
  // Uncomment lines of code to see the outputs of each function
  
  // read the temperature from the LM35 sensor
  // read_temp_LM35(LM35_SENSOR);

  // read and save max and min temperatures from the LM35 sensor
  // read_max_min_temp_LM35(&tempMAX, &tempMIN, LM35_SENSOR);

  // read the temperature from the DS18B20 sensors
  // read_temp_DS18B20(DS18B20_sensor, DS18B20_NUM_OF);

  // read and save max and min temperatures from the DS18B20 sensors
  //read_max_min_temp_DS18B20(&tempMAX, &tempMIN, DS18B20_sensor, DS18B20_NUM_OF);
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

// The function below checks for maximum and minimum measured temperature with LM35
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

// The function below reads the temperature from the DS18B20 sensor and prints it to the serial monitor
// Its argument is the DallasTemperature object - the DS18B20 sensor 
void read_temp_DS18B20(DallasTemperature DS18B20, int num_of_sensors) {
  // When connecting the DS18B20 I need to connect a 4.7kOhm pullup resistor
  // I can connect more than one sensor to the same line - DS18B20_SENSOR
  // This is very useful, as one resistor can take care of many sensors
  // and the measurements can be taken in the software.
  DS18B20.requestTemperatures(); // Get the temperatures from the sensor(s) 
  
  // For every sensor print the temperature read:
  Serial.println("Current temperature reading: ");
  for(int i = 0; i < num_of_sensors; ++i) {
    Serial.print("Sensor number " + String(i) + ": ");
    Serial.print(DS18B20.getTempCByIndex(i));
    Serial.print("*C\t");
  }
  Serial.println();
  
  delay(500);
}

// The function below checks for maximum and minimum measured temperature with DS18B20
// For more functionality one can use the addresses of the sensors
void read_max_min_temp_DS18B20(float* temp_MAX, float* temp_MIN, DallasTemperature DS18B20, int num_of_sensors) {
  DS18B20.requestTemperatures(); // Get the temperatures from the sensor(s) 
  
  float temperature_arr[num_of_sensors - 1]; // initialize temperature array
  float current_tempMAX  = 0;   // min temperature of the current iteration
  float current_tempMIN = 150;  // max temperature of the current iteration
  
  for(int i = 0; i < num_of_sensors; ++i) {
    temperature_arr[i] = DS18B20.getTempCByIndex(i); // read temperature from every sensor
    // Also save max and min values from the array during the current read
    if(temperature_arr[i] > current_tempMAX) {
      current_tempMAX = temperature_arr[i];
    }
    if(temperature_arr[i] < current_tempMIN) {
      current_tempMIN = temperature_arr[i];
    }
  }
  
  // If the calculated temperature is higher than the current max value then set that value to max value and print it out to the serial monitor
  if(current_tempMAX > *temp_MAX) {
    *temp_MAX = current_tempMAX;
    Serial.print("New max temperature: ");
    Serial.print(*temp_MAX);
    Serial.println("*C");
  }

  // If the calculated temperature is lower than the current min value then set that value to min value and print it out to the serial monitor
  if(current_tempMIN < *temp_MIN) {
    *temp_MIN = current_tempMIN;
    Serial.print("New min temperature: ");
    Serial.print(*temp_MIN);
    Serial.println("*C");
  }

  delay(500);
}
