/*
 * This project shows how to control regular RGB diodes and programmable diodes such as the WS2812.
 * Each RGB diode has a built in circuit that allows for communication with Arduino, which allows me to  
 * set a desired color of the light.
 */

#include <Adafruit_NeoPixel.h> // Include library for programmable diodes

#define BAUD_RATE 9600

#define RED_0 2
#define GREEN_0 3
#define BLUE_0 4

// These are parameters of the programmable diode I am using
#define NUM_PROG_DIODES 8                  // Number of diodes in a line
#define PROG_DIODES_PIN A0                 // The pin that the diode line is connected to
#define DIODES_INFO (NEO_GRB + NEO_KHZ800) // Type of NeoPixels that are connected

// macro that changes the first color to the second another continuously
#define change_colors(color_1, color_2) do {  \
    for(int i = 0; i < 255; ++i) {            \
      analogWrite(color_2, i);                \
      analogWrite(color_1, 255 - i);          \
      delay(10);                              \
    }                                         \
  } while(false)

// macro that shows a specified color on the whole diode line
// To set a color of a given pixel I use setPixelColor method
// It takes the pixel number as first argument (0 = lowest pixel) and the color it should be set to as the second argument
// To set the color I use the Color method, with 3 arguments representing RGB values from 0 to 255
#define show_color_all(diode_line, color_r, color_g, color_b) do {                \
    for(int i = 0; i < NUM_PROG_DIODES; ++i) {                                    \
      diode_line.setPixelColor(i, diode_line.Color(color_r, color_g, color_b));   \
    }                                                                             \
    diode_line.show();                                                            \
  } while(false)
  
// Initialize the Adafruit_NeoPixel object with specified parameters
Adafruit_NeoPixel diode_line = Adafruit_NeoPixel(NUM_PROG_DIODES, PROG_DIODES_PIN, DIODES_INFO);

void setup() {
  Serial.begin(BAUD_RATE);

  // As one can see just one RGB diode requires 3 pins. Adding more RGB diodes would use up all the pins quickly
  // Furthermore, to adjust the colors in a more detailed way, I would need all the pins to output PWM signal, which limits the functionality even more
  pinMode(RED_0, OUTPUT);
  pinMode(GREEN_0, OUTPUT);
  pinMode(BLUE_0, OUTPUT);

  // An alternative approach is to use a line of programmable RGB diodes - this way I can porgram many diodes with just one line
  diode_line.begin(); // initialize the line of programmable diodes
  
  // Show different sequences
  show_RGB_color_sequences(RED_0, GREEN_0, BLUE_0, 2000);
  show_color_change_RGB(RED_0, GREEN_0, BLUE_0);

  // Show different sequence on the programmable diodes
  show_programmable_diodes_color_sequences(diode_line);
}

void loop() {

}

// This function shows several color sequences in that the RGB diode is capable of outputting
void show_RGB_color_sequences(int red, int green, int blue, int seq_delay_time) {
  // First sequence turns each color on and off for some time
  digitalWrite(red, HIGH);
  delay(seq_delay_time);
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
  delay(seq_delay_time);
  digitalWrite(green, LOW);
  digitalWrite(blue, HIGH);
  delay(seq_delay_time);
  digitalWrite(blue, LOW);
  delay(seq_delay_time);

  // Second sequence turns all colors one after another and then back off
  digitalWrite(red, HIGH);
  delay(seq_delay_time);
  digitalWrite(green, HIGH);
  delay(seq_delay_time);
  digitalWrite(blue, HIGH);
  delay(seq_delay_time);
  digitalWrite(red, LOW);
  delay(seq_delay_time);
  digitalWrite(green, LOW);
  delay(seq_delay_time);
  digitalWrite(blue, LOW);
  delay(seq_delay_time);

  // Finally, third sequence turns all colors on at the same time and then off
  digitalWrite(red, HIGH);
  digitalWrite(green, HIGH);
  digitalWrite(blue, HIGH);
  delay(seq_delay_time);
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(blue, LOW);
}

// This function shows a continuous change of colors on the RGB diode
void show_color_change_RGB(int red, int green, int blue) {
  // Since this is PWM, I go from o to 255
  // 2 colos change while the third one is 0
  analogWrite(red, 255);
  analogWrite(green, 0);
  analogWrite(blue, 0);

  change_colors(red, blue);
  change_colors(blue, green);
  change_colors(green, red);
  change_colors(red, green);
  change_colors(green, blue);
  change_colors(blue, red);
  
  analogWrite(red, 0);
  analogWrite(green, 0);
  analogWrite(blue, 0);
}

void show_programmable_diodes_color_sequences(Adafruit_NeoPixel diode_line) {
  show_color_all(diode_line, 255, 0, 0); // All red
  delay(2000);
  show_color_all(diode_line, 0, 255, 0); // All green
  delay(2000);
  show_color_all(diode_line, 0, 0, 255); // All blue
  delay(2000);
  show_color_all(diode_line, 0, 0, 0);   // Turn all off

  // Show all turning on, and different colors
  for(int i = 0; i < NUM_PROG_DIODES; ++i) {
    diode_line.setPixelColor(i, diode_line.Color(255 * (i % 3 == 0 ? 1 : 0), 255 * (i % 3 == 1 ? 1 : 0), 255 * (i % 3 == 2 ? 1 : 0)));
    diode_line.show();
    delay(250);
  }
  delay(2000);
  // Then turn them off the same way:
  for(int i = NUM_PROG_DIODES - 1; i >= 0; --i) {
    diode_line.setPixelColor(i, diode_line.Color(0, 0, 0));
    diode_line.show();
    delay(250);
  }

  // show different colors appearing and disappearing:
  for(int i = 0; i < 3; ++i) {
    for(int j = 0; j < NUM_PROG_DIODES; ++j) {
      diode_line.setPixelColor(j, diode_line.Color(255 * (i % 3 == 0 ? 1 : 0), 255 * (i % 3 == 1 ? 1 : 0), 255 * (i % 3 == 2 ? 1 : 0)));
      diode_line.show();
      delay(250);
    }
  }
  delay(2000);
  show_color_all(diode_line, 0, 0, 0);

  // I can also change the colors similarly to the RGb diodes, with a few adjustments
  // This will change the color from red to green to blue and back to red
  for(int j = 0; j < 255; ++j) {
    show_color_all(diode_line, 255 - j, j, 0);
    delay(20);
  }
  for(int j = 0; j < 255; ++j) {
    show_color_all(diode_line, 0, 255 - j, j);
    delay(20);
  }
  for(int j = 0; j < 255; ++j) {
    show_color_all(diode_line, j, 0, 255 - j);
    delay(20);
  }
  delay(2000);

  show_color_all(diode_line, 255, 255, 255);
  delay(2000);
  show_color_all(diode_line, 0, 0, 0);

  // There are countless other ways to show different patterns these are just some of them
}
