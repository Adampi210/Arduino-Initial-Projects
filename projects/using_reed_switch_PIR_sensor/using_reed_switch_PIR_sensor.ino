/*
 * This project shows how to use reed switches and PIR sensors in Arduino.
 * I decided to group these elements because together they can be used to create a simple security system.
 * 
 * The Reed Switch is a switch operated by an applied magnetic field. When a mangetnetic field is brought next to the switch,
 * the contacts inside it change their position (either connect or disconnect dependng on the type of switch). 
 * That change in state can be useful in many applications, for example by installing the reed switches on windows and doors, 
 * one can detect if and which window/door was opened.
 * 
 * 
 * The PIR Sensor (PIR = Passive Infra Red) is a sensor measuring infrared light (temperature) from its surroundings. Based on that 
 * it is capable of detecting general movement - whenever the sensor detects movement 
 * it changes its output state. Here I used the HC-SR501 PIR sensor. The sensor in question has the power pins, output pin, 
 * and two potentiometers - Tx and Sx. The Tx potentiometer regulates how long the output will have a HIGH state
 * after motion is detected - I set it to the lowest value, so the HIGH state will be outputted only for approx. 5s after motion is detected
 * (also it is high as long as it detects some motion). The Sx potentiometer regulates sensitivity.
 */

#define BAUD_RATE 9600

#define REED_SWITCH_0 2 // Pin of the Reed Switch
#define PIR_SENSOR_0 3    // Pin of the PIR sensor

void setup() {
  Serial.begin(BAUD_RATE);

  // set modes of pins connected to Reed Switch and the PIR sensor
  pinMode(REED_SWITCH_0, INPUT_PULLUP); // Input pullup since it's a switch
  pinMode(PIR_SENSOR_0, INPUT);         // Input for the PIR sensor

}

void loop() {
  bool first_sensor_result = detect_reed_switch(REED_SWITCH_0);
  bool second_sensor_result = detect_PIR_sensor(PIR_SENSOR_0);

  security_system(2, first_sensor_result, second_sensor_result);
  
  delay(50);
}

// This function detects if a reed switch is closed or open, and depending on that prints a corresponding message and returns true or false
bool detect_reed_switch(int reed_switch) {
  if(digitalRead(reed_switch) == LOW) {
    // Serial.println("OK: Reed switch closed"); // show a message if everything is ok (commented out to make the final output easier to read)
    return true;
  }
  else {
    Serial.println("ERROR: Reed switch open");
    return false;
  }
}

// This function detects if a PIR sensor detected motion, and depending on that prints a corresponding message and returns true or false
// It's very similar to the previous, but I still wanted to make it independently
bool detect_PIR_sensor(int PIR_sensor) {
  if(digitalRead(PIR_sensor) == LOW) {
    // Serial.println("OK: No motion detected"); // show a message if no motion (commented out to make the final output easier to read)
    return true;
  }
  else {
    Serial.println("ERROR: Motion detected");
    return false;
  }
}

// This function goes through all the connected sensors, and checks if all return true, meaning everything is ok
// If at least one returns false, then something is wrong, and the function will print that message
void security_system(int num_sensors, ...) {
  bool all_sensors_ok = true; // Instantiate variable storing info if all sensors are ok (initially true)
  
  va_list sensors; // varying list of sensors (number of sensors can change)
  va_start(sensors, num_sensors); // enable access to variadic function arguments (all sensor information)

  // Go through each sensor and read its value
  // Then AND that value with all_sensors_ok - if at least one is false, the result will be false
  for(int i = 0; i < num_sensors; ++i) {
    int sensor = va_arg(sensors, int);
    all_sensors_ok &= sensor == 1 ? true : false;
  }
  // If one of the sensors was false, print error message
  if(!all_sensors_ok) {
    Serial.println("ERROR: One of the sensors detected intrusion");
  }
}
