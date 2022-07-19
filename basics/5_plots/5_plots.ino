/*
 * Arduino IDE allows for quick plot drawing under Serial Plotter. Plots are very useful in illustrating
 * how a created system works, and overall in observing phenomena occurring in the system. Some examples were plots are
 * useful would be: gyroscope, efficiency, finding maximums and minimums, etc. 
 * To plot in Arduino, I just need to print the values I want to plot to the serial monitor. To use the plotter, 
 * I can click on Tools and Serial Plotter, or use the key shortcut.
 */

#define BAUD_RATE 9600

#define PHOTO_RESISTOR A1
#define POTENTIOMETER A3

void setup() {
  Serial.begin(BAUD_RATE);

  // Define pin modes
  pinMode(PHOTO_RESISTOR, INPUT);
  pinMode(POTENTIOMETER, INPUT);
}

void loop() {
  // Read values from the sensors connected to arduino
  int photoresistor_analog_value = analogRead(PHOTO_RESISTOR);
  int potentiometer_analog_value = analogRead(POTENTIOMETER);

  // To plot several values One after another, I need to use tabulator:
  Serial.print(photoresistor_analog_value); // Plot first value
  Serial.print('\t');
  Serial.print(potentiometer_analog_value); // Plot second value
  Serial.println();

}
