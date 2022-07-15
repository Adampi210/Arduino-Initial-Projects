/*
 * This project shows how to use a HC-SR04 ultrasonic proximity sensor. The sensor (datasheet: https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf)
 * has 4 pins - two power pins, and two data pins - trigger and echo. It works by setting
 * a high signal on the trigger pin and then reading the response time on the echo pin. Knowing this, I can
 * find how far objects are from the sensor. The sensor is said to have a range of up to 4 meters, 
 * and can be used in variety of situations such as reading distance, proximity sensing, sonar, etc.
 */

#define BAUD_RATE 9600

#define SOUND_SPEED 343
#define TRIG_PIN_0 4
#define ECHO_PIN_0 3

void setup() {
  Serial.begin(BAUD_RATE);

  pinMode(TRIG_PIN_0, OUTPUT);  // Signal will be outputted to the Trigger pin
  pinMode(ECHO_PIN_0, INPUT);   // And measurement will be made on the Echo pin

}

void loop() {

  // Uncomment to show distance measurement
  // int distance = measure_display_distance(TRIG_PIN_0, ECHO_PIN_0);
  // Print the distance to the user on the serial monitor
  // Serial.println("Distance to an object: " + String(distance) + "cm");
  
  // Uncomment to show the range checking
  // check_if_good_range(TRIG_PIN_0, ECHO_PIN_0, 10, 40);
  delay(100);
}

// This function measures the distance from the sensor to a detected object
int measure_display_distance(int trig_pin, int echo_pin) {
  unsigned long time_response; // Time it takes the echo pin to receive a response (used to calculate the distance)
  int distance;                // Calculated distance from detected object
  
  // First I output LOW signal on the trigger pin, to make sure nothing from before interferes with the sensor operation
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(5);
  // Then I output the 10us (10 microsecond pulse) to the trigger pin which will send a ultrasonic signal from the sensor
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  // After that I set the trigger back to low and read the time of the response (which is when echo pin received a pulse from the sensor)
  digitalWrite(trig_pin, LOW);

  time_response = pulseIn(echo_pin, HIGH); // This function measures time of a high pulse (its width) on the echo pin

  // The width of the pulse is proportional to the distance from a detected object: 
  // More specifically, the time of high pulse on echo pin is equal to the time from sending ultrasonic signal to its return
  // To find the distance, I just have to multiply that time by the speed of sound and divide by 2 (singal goes to the object and returns)
  // Finally I need to divide by 10^4 since the time_response is in mircoseconds and I want the distance to be in cm (10^-2 m)
  distance = time_response * SOUND_SPEED * 1e-4 / 2;


  return distance;
}

// This function checks if a given object is in a required range from te sensor
void check_if_good_range(int trig_pin, int echo_pin, int min_distance, int max_distance) {
  int distance = measure_display_distance(trig_pin, echo_pin); // measure the distance

  // If the object is not in the required range, print the message
  if(distance < min_distance || distance > max_distance) {
    Serial.println("The object is not in the required range!!!");
    // More things could be added here to make an alarm like turning LEDs on and sounding a buzzer
  }
}
