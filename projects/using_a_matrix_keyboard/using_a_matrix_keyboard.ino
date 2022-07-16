/*
 * This project shows how to use a matrix keypad. The keypad I use is comprised of 16 buttons 
 * put in a 4x4 matrix. This means that the whole thing can be conrolled by 8 pins - 4 row and 4 column pins.  
 * By selecting a certain row and column I can locate every unique button. For simplicity I use the
 * Keypad.h library to for keypad usage (https://github.com/Chris--A/Keypad.git)
 */

#include <Keypad.h> // Import the library

#define BAUD_RATE 9600

#define N_ROWS 4 // number of rows
#define N_COLS 4 // number of columns

byte row_pins[ROWS] = {}; // finish setting up
byte col_pins[COLS] = {};

char keys[ROWS][COLS] = { // mapping the keys of the keyboard to corresponding characters
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

Keypad keypad_0 = Keypad(makeKeymap(keys), row_pins, col_pins, N_ROWS, N_COLS); // Instantiate the keypad object

void setup() {
  Serial.begin(BAUD_RATE);

}

void loop() {
  // put your main code here, to run repeatedly:

}
