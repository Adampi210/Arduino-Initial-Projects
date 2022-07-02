/*
 * Arduino can be used to read/write (as PWM) signals. To do that
 * it uses ADC - Analog-Digital Converter that on some pins (A1 - AX)
 * reads a voltage value between 0V and 5V and converts it to a number between 0 and some upper boundary like 255 (8bit, can be different).
 * PWM - pulse width modulation is the fraction of time that the outputted signal is high. Basically, by switching a signal on and off
 * I can decide how much time it will be on and therefore how much energy will go to a device. 
 * It is very useful when controlling: brightness, servo position, and speed of a motor.
 */

// define macro for printing variables to serial monitor and other constants
#define print_var_to_monitor(variable) do {           \
    Serial.print(#variable);                          \
    Serial.print(" = ");                              \
    Serial.print(variable);                           \
  } while(false)

#define BAUD_RATE 9600
#define READING_PIN A0
#define PWM_PIN 2

int value_read_ADC = 0; // initialize value read using analogRead to 0
float voltage = 0;      // initialize voltage value to 0
int mapped_value = 0;   // initialize mapped_value to 0

int PWM_signal_width = 0;   // this determines the width of how long the signal is on. Width of 0 is signal off all the time, and width of 255 is signal on all the time
int PWM_signal_change = 5;  // this determines how fast a PWM will increase after one loop

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(PWM_PIN, OUTPUT);
}

void loop() {
  //____________ ADC ______________
  // read the value using analogRead function, in this case it will return value between 0 and 1023
  value_read_ADC = analogRead(READING_PIN);
  print_var_to_monitor(value_read_ADC);
  
  Serial.print(", ");
  
  voltage = measure_voltage(value_read_ADC);
  print_var_to_monitor(voltage);
  Serial.print("V, ");

  // I can also map the read value to a desired value:
  mapped_value = map(value_read_ADC, 0, 1023, 0, 10);
  print_var_to_monitor(mapped_value);
  Serial.println();
  
  //____________ PWM ______________
  analogWrite(PWM_PIN, PWM_signal_width); // analogWrite(PIN, width); writes a PWM signal at a given pin

  // This code will increase diode brightness from 0 to full in a constant loop
  if(PWM_signal_width < 255) {
    PWM_signal_width += PWM_signal_change;
  }
  else {
    PWM_signal_width = 0;
  }
  
  
  delay(300);
}

// this function is used to make a simple voltmeter (not too precise tough)
float measure_voltage(int value_read_ADC) {
  return(value_read_ADC * (5.0 / 1024.0));
}

/*
 * Example output:
 * value_read_ADC = 786, voltage = 3.84V, mapped_value = 7
 * value_read_ADC = 786, voltage = 3.84V, mapped_value = 7
 * value_read_ADC = 786, voltage = 3.84V, mapped_value = 7
 */
