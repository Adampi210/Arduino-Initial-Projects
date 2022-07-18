/*
 * Sometimes the programmer wants the program in an unpredictable way. For that purpose, 
 * random numbers can be used. Of course, the numbers returned by any microcontrollers function are not going to be truly random, 
 * rather - pseudorandom (ie. if I know the initial number and the algorithm to get them, I can always predict the result).
 * Nevertheless, in most applications, pseudorandom numbers will be suitable, which is why function random() and others are very useful.
 */

#define BAUD_RATE 9600

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(LED_BUILTIN, OUTPUT); // Set the mode of built-in led to output, to use that later
  randomSeed(analogRead(A0));   // This function sets the seed for random number generation
  // based on that the numbers will be generated pseudorandomly
  // Also, to make it random, I use analogRead on A0 pin, that isn't connected to anything
  // That means the reading will be some background noise, which will be random - exactly what I need

  // Select and print a random number from the specified range
  generate_some_random_numbers();

  // Blink the LED in a random manner
  random_LED_blinking(LED_BUILTIN);
}

void loop() {

}

// This function shows random number generation
void generate_some_random_numbers() {
  int lower_bound; // lower limit the random numbers should be generated from
  int upper_bound; // upper limit the random numbers should be generated up to

  // Ask the user to enter the bounds and read them
  Serial.println("Please enter lower and upper bounds for random numbers generation");

  // Enter lower bound
  Serial.print("Lower bound: ");
  while(Serial.available() == 0) {}
  lower_bound = (Serial.readStringUntil('\n')).toInt();
  Serial.println(lower_bound);
  
  // Enter upper bound
  Serial.print("Upper bound: ");
  while(Serial.available() == 0) {}
  upper_bound = (Serial.readStringUntil('\n')).toInt();
  Serial.println(upper_bound);
  
  // First generate a random number between 0 and 10:
  int loop_iterations = random(11); // without the lower bound specified, it will be 0. The upper bound is non-inclusive (meaning 11 is not in the pool)

  Serial.print("Random number from the specified range: ");
  // Then generate a random number from the specified range
  Serial.println(random(lower_bound, upper_bound + 1));
  // And then next a few random numbers (determined by previously generated number)
  Serial.println("Next " + String(loop_iterations) + " random numbers from the specified range");
  for(int i = 0; i < loop_iterations; ++i) {
    Serial.println(random(lower_bound, upper_bound + 1));
    delay(1000);
  }
} 

// This function blinks the LED in a random way
void random_LED_blinking(uint8_t LED_pin) {
  // The numbers generation boundaries were chosen randomly, can be easily changed if needed
  int time_on = random(10, 101) * 10;   // Time an LED will be on in ms
  int time_off = random(10, 101) * 10;  // Time an LED will be off in ms
  int blinks = random(5, 16);           // Number of times the diode will blink

  // Blink the LED in a random way
  for(int i = 0; i < blinks; ++i) {
    digitalWrite(LED_pin, HIGH);
    delay(time_on);
    digitalWrite(LED_pin, LOW);
    delay(time_off);  
  }
}
