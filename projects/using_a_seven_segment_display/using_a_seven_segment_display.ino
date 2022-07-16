/*
 * This project shows how to use a seven segment display with Arduino. Each of the segments
 * is an LED diode that form a shape of number 8 (with a dot on the right). To make the usage easier, 
 * one can denote each segment with a letter - starting from the top segment and going clockwise, the letters would be
 * A, B, C, D, E, F, and G in the middle (with the right dot being P for point).
 * Using a seven segment display is comparable to using diodes, and can be done both with the usage of simple commands
 * and with the usage of a library to make coding easier (library I use is: https://github.com/DeanIsMe/SevSeg.git). Finally, the sev-seg
 * I used is LDD040AAG-101, with a common cathode and inactive P diode.
 */

#include "SevSeg.h" // include the library to hande the sev-seg display

#define BAUD_RATE 9600

// Define segment connections. I am using Arduino Mega 2560, so The last segment is on pin 22
// The second digit (second batch of segments) should be connected to the same pins (So for example seg_a_0 and seg_a_1 both connect to pin 2 in Arduino)
// I do that so that I dont use up too much pins
// Instead of connecting a completely new set of pins, I can connect the cathodes via transistors and then turn the transistors on and off separately
// If I do that fast enough it will look as if both numbers are on at the same time
// The transistors I use are BC547B NPN transistors
#define SEG_A 2
#define SEG_B 3
#define SEG_C 4
#define SEG_D 5
#define SEG_E 6
#define SEG_F 7
#define SEG_G 22 

#define CATHODE_0 44
#define CATHODE_1 45

// This macro will blink each segment for some defined time
#define blink_segment(seg_letter, time_ms) do { \
  digitalWrite(seg_letter, HIGH);               \
  delay(time_ms);                               \
  digitalWrite(seg_letter, LOW);                \
  } while(false)

SevSeg sev_seg_disp_0; // Instantiate a sev-seg display object

void setup() {
  Serial.begin(BAUD_RATE);
  
  // Configure segments
  pinMode(SEG_A, OUTPUT);
  pinMode(SEG_B, OUTPUT);
  pinMode(SEG_C, OUTPUT);
  pinMode(SEG_D, OUTPUT);
  pinMode(SEG_E, OUTPUT);
  pinMode(SEG_F, OUTPUT);
  pinMode(SEG_G, OUTPUT);

  pinMode(CATHODE_0, OUTPUT);
  pinMode(CATHODE_1, OUTPUT);

  
  // Show different sequences of segments being switched on and off
  // show_segment_sequence(SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G);
  
  // Ask user to enter a number and display it on the sev-seg
  // display_number_from_user(SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G);

  // Initialize values defining the sev_seg display
  byte num_segment_fields = 2; // Number of segment fields
  byte cathode_pins[] = {CATHODE_0, CATHODE_1}; // Pins connected to the transistors that control the cathodes
  byte segment_pins[] = {SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G}; // Pins connected to the segments
  bool resistors_on_segments = true; // This specifies if resistors were connected before the sev-seg pins (I did that, so I put true)
  byte hardware_config = N_TRANSISTORS; // This specifies how I connected the display to control the segment fields - in this case I used N-type transistors which are active-high

  sev_seg_disp_0.begin(hardware_config, num_segment_fields, cathode_pins, segment_pins, resistors_on_segments); // begin usage of the sev-seg display

  // Display a number using the library
  display_number_from_user_w_library(sev_seg_disp_0);
}

void loop() {
  // put your main code here, to run repeatedly:

}

// This function shows a specified digit on the seven segment display
void show_digit(int digit, byte seg_a, byte seg_b, byte seg_c, byte seg_d, byte seg_e, byte seg_f, byte seg_g) {
  // Each segment should turn on when specific digits are passed as arguments
  // Also in digital write HIGH == 1 is true and LOW == 0 is true, so using an OR will work as expected
  digitalWrite(seg_a, digit == 0 || digit == 2 || digit == 3 || digit == 5 || digit == 6 || digit == 7 || digit == 8 || digit == 9);
  digitalWrite(seg_b, digit == 0 || digit == 1 || digit == 2 || digit == 3 || digit == 4 || digit == 7 || digit == 8 || digit == 9);
  digitalWrite(seg_c, digit == 0 || digit == 1 || digit == 3 || digit == 4 || digit == 5 || digit == 6 || digit == 7 || digit == 8 || digit == 9);
  digitalWrite(seg_d, digit == 0 || digit == 2 || digit == 3 || digit == 5 || digit == 6 || digit == 8 || digit == 9);
  digitalWrite(seg_e, digit == 0 || digit == 2 || digit == 6 || digit == 8);
  digitalWrite(seg_f, digit == 0 || digit == 4 || digit == 5 || digit == 6 || digit == 6 || digit == 8 || digit == 9);
  digitalWrite(seg_g, digit == 2 || digit == 3 || digit == 4 || digit == 5 || digit == 6 || digit == 8 || digit == 9);
}

// This function will show a few sequences of each segment being switched on and off
void show_segment_sequence(byte seg_a, byte seg_b, byte seg_c, byte seg_d, byte seg_e, byte seg_f, byte seg_g) {
  // Turn on the cathode 0 so that the sequences are only shown on the first segment field
  digitalWrite(CATHODE_0, HIGH);
  // Show each segment cycling the display 5 times
  for(int i = 0; i < 1; ++i) {
    blink_segment(seg_a, 500);
    blink_segment(seg_b, 500);
    blink_segment(seg_c, 500);
    blink_segment(seg_d, 500);
    blink_segment(seg_e, 500);
    blink_segment(seg_f, 500);
    blink_segment(seg_g, 500);
  }

  // Switch all on and back off
  digitalWrite(seg_a, HIGH);
  delay(500);
  digitalWrite(seg_b, HIGH);
  delay(500);
  digitalWrite(seg_c, HIGH);
  delay(500);
  digitalWrite(seg_d, HIGH);
  delay(500);
  digitalWrite(seg_e, HIGH);
  delay(500);
  digitalWrite(seg_f, HIGH);
  delay(500);
  digitalWrite(seg_g, HIGH);
  delay(1000);
  digitalWrite(seg_g, LOW);
  delay(500);
  digitalWrite(seg_f, LOW);
  delay(500);
  digitalWrite(seg_e, LOW);
  delay(500);
  digitalWrite(seg_d, LOW);
  delay(500);
  digitalWrite(seg_c, LOW);
  delay(500);
  digitalWrite(seg_b, LOW);
  delay(500);
  digitalWrite(seg_a, LOW);

  // Show each digit going up and then down
  for(int i = 0; i < 10; ++i) {
    show_digit(i, seg_a, seg_b, seg_c, seg_d, seg_e, seg_f, seg_g);
    delay(1000);
  }
  for(int i = 9; i >= 0; --i) {
    show_digit(i, seg_a, seg_b, seg_c, seg_d, seg_e, seg_f, seg_g);
    delay(1000);
  }

  // Turn the cathode off
  digitalWrite(CATHODE_0, LOW);
}

// This function asks the user to enter a number and displays that number on the sev-seg display
void display_number_from_user(byte seg_a, byte seg_b, byte seg_c, byte seg_d, byte seg_e, byte seg_f, byte seg_g) {
  int user_number; // Number from the user that will be displayed on the sev-seg display
  
  // Get the number to display from the user
  Serial.println("Please enter a number to be displayed on the sev-seg display (between 0 and 99):");
  while(Serial.available() == 0) {} 
  user_number = (Serial.readStringUntil('\n')).toInt();
  delay(200);

  // Keep showing the number until something is entered to the serial monitor
  Serial.println("Enter anything to stop displaying the number.");  

  // Loop runs until something is entered
  while(Serial.available() == 0) {
    // Turn right display on and show the right side of the number
    digitalWrite(CATHODE_1, HIGH);
    show_digit(user_number % 10, seg_a, seg_b, seg_c, seg_d, seg_e, seg_f, seg_g);
    delay(10);
    digitalWrite(CATHODE_1, LOW);
    // If the number is greater than 9 turn right side off, and left on and show the left number
    // Then turn the left off
    // This creates an illusion that the digits are continuous
    
    if(user_number > 9) {
      digitalWrite(CATHODE_0, HIGH);
      show_digit(user_number / 10, seg_a, seg_b, seg_c, seg_d, seg_e, seg_f, seg_g);
      delay(10);
      digitalWrite(CATHODE_0, LOW);
    }
  }
  /*
   * This solution is quite clever but doing it every time when using a sev-seg display to show numbers would be 
   * quite tedious. Furthermore, this function only works with 2 digit displays, but there can be more.  
   * That's why it's better to use a library (or write my own). I will use the library mentioned in the beginning
   */

   // Turn the cathodes off
   digitalWrite(CATHODE_0, LOW);
   digitalWrite(CATHODE_1, LOW);
}

// Just as the previous function, this one displays a number on the sev-seg display
// but this time it is done with the use of library
void display_number_from_user_w_library(SevSeg sev_seg_display) {
  int user_number; // Number from the user that will be displayed on the sev-seg display
  
  // Get the number to display from the user
  Serial.println("Please enter a number to be displayed on the sev-seg display (between 0 and 99):");
  while(Serial.available() == 0) {} 
  user_number = (Serial.readStringUntil('\n')).toInt();
  delay(200);

    // Keep showing the number until something is entered to the serial monitor
  Serial.println("Enter anything to stop displaying the number.");  

  // Loop runs until something is entered
  while(Serial.available() == 0) {
    sev_seg_display.setNumber(user_number, 2); // set the number to the display. The second argument specifies where a dot should be
                                               // In the display I use the dot is inactive, so I set it to 2
                                               // If the dot was active I could change that to set the dot in different place (ex. 2 could be 2.0 or 0.2)
    sev_seg_display.refreshDisplay(); // This takes care of turning the fields on and off
  }
  // The library also has other methods such as .setChars("AA"); which would set 2 chars AA to the sev-seg display
  // And many others
  // Turn the sev-seg off
  sev_seg_display.blank();
}
