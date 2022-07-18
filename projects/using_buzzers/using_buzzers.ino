/*
 * This project shows the usage of buzzers - audio signaling devices that output different tones. 
 * They are very useful in projects that involve sound generation. In this project I use two types of buzzers: 
 *  - buzzer with a geneator
 *  - buzzer without a generator
 *  As the names suggest, one buzzer has a generator that does the sound generation for its user, and the only thing that needs to be done
 *  to generate sound is connecting it to high voltage. The buzzer without the generator has to get an input signal at a certain frequency
 *  to output the sound - single high signal will cause the buzzer to output a single sound.
 */

#define BAUD_RATE 9600

#define BUZZER_GENERATOR_0 2 // Buzzer with generator pin
#define BUZZER_NO_GENERATOR_0 6 // Buzzer without a generator

void setup() {
  Serial.begin(BAUD_RATE);

  // Set modes of pins for the buzzers
  pinMode(BUZZER_GENERATOR_0, OUTPUT);
  pinMode(BUZZER_NO_GENERATOR_0, OUTPUT);
  
  // Play sound on the buzzer with generator for some time
  sound_generator_buzzer(BUZZER_GENERATOR_0, 4000);

  // Play manual sounds on the buzzer without the generator
  play_different_sounds_manually_buzzer_no_g(BUZZER_NO_GENERATOR_0);

  // Play sounds using tone function
  play_sounds_using_tone(BUZZER_NO_GENERATOR_0);

  // Buzzers can also be used to play melodies, as some tone frequencies correspond to certain music notes
}

void loop() {
  
}

// This function will play a sound on a buzzer with a generator for a specified time (in ms)
// To play a sound on a buzzer with a generator I just need to output a high signal to it
// As one can see, using a buzzer with a generator is relatively easy, but doesnt allow the programmer for much modification of the sound
void sound_generator_buzzer(int buzzer_pin, long time_sound) {
  digitalWrite(buzzer_pin, HIGH);
  delay(time_sound);
  digitalWrite(buzzer_pin, LOW);
}

// Buzzer without the generator allows for much better modification of the sounds play in exchange for more complicated operation
// This function plays the sounds manually using for loops and delays
void play_different_sounds_manually_buzzer_no_g(int buzzer_pin) {

  // Play 10 sounds with low frequency
  for(int i = 0; i < 10; ++i) {
    digitalWrite(buzzer_pin, HIGH);
    delay(500);
    digitalWrite(buzzer_pin, LOW);
    delay(500);
  }

  // Play 100 sounds with medium frequency
  for(int i = 0; i < 100; ++i) {
    digitalWrite(buzzer_pin, HIGH);
    delay(50);
    digitalWrite(buzzer_pin, LOW);
    delay(50);
  }

  // Play 1000 sounds with high frequency
  for(int i = 0; i < 1000; ++i) {
    digitalWrite(buzzer_pin, HIGH);
    delay(5);
    digitalWrite(buzzer_pin, LOW);
    delay(5);
  }
}

// This function also plays different frequency sounds but to do that it uses tone function
// The tone() function uses a timer that generates a PWM signal on pins 3 and 11 (Except for Mega boards)
// This means it will interfere with PWM generation on these pins. Also, only one tone can be generated at a time
// Reference: https://www.arduino.cc/reference/en/language/functions/advanced-io/tone/
void play_sounds_using_tone(int buzzer_pin) {
  // Lowest acceptable frequency is 31Hz
  // Highest possible frequency is 65534Hz
  tone(buzzer_pin, 100); // play frequency 100Hz for 2s
  delay(2000);
  noTone(buzzer_pin);
  delay(1000);
  
  tone(buzzer_pin, 1000); // play frequency 1kHz for 2s
  delay(2000);
  noTone(buzzer_pin);
  delay(1000);

  tone(buzzer_pin, 10000); // play frequency 10kHz for 2s
  delay(2000);
  noTone(buzzer_pin);
  delay(1000);

  // I could also run the tone function with third argument being the time of operation, but it causes some problems when calling tone more than once
  
  // Below the loop shows all frequencies from the lowest to the highest
  // Also one can notice that the sound is getting louder at some point even though the voltage is constant
  // That's because the buzzer reaches its resonant frequency
  // Also, notice I am using long, as 65534 is beyond int's range
  // If I used int the loop would run forever (int would cycle between its limits, never reaching 65534)
  for(long freq = 31; freq < 65535; ++freq) {
    tone(buzzer_pin, freq);
  }
  noTone(buzzer_pin);
} 
