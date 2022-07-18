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

byte row_pins[N_ROWS] = {5, 4, 3, 2}; // Pins connected to the rows (top row to bottom row)
byte col_pins[N_COLS] = {6, 7, 8, 9}; // Pins connected to the rows (left column to right column)

char keys_pilot[N_ROWS][N_COLS] = { // mapping the keys of the keyboard to corresponding characters for a regular pilot
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

char keys_calculator[N_ROWS][N_COLS] = { // mapping the keys of the keyboard to corresponding characters for a calculator
  {'1', '2', '3', '+'},
  {'4', '5', '6', '-'},
  {'7', '8', '9', '*'},
  {'.', '0', '=', '/'}
};


Keypad keypad_0 = Keypad(makeKeymap(keys_pilot), row_pins, col_pins, N_ROWS, N_COLS); // Instantiate the keypad object
Keypad keypad_1 = Keypad(makeKeymap(keys_calculator), row_pins, col_pins, N_ROWS, N_COLS); // Instantiate the keypad object

void setup() {
  Serial.begin(BAUD_RATE);
}

void loop() {
  // Print the characters in serial monitor after they are pressed on the keypad
  // print_key_after_pressed(keypad_0);

  // Show calculator operation
  calculator_keypad(keypad_1);
}

// The function below waits for the user to press a button on a keypad and then prints the pressed key
void print_key_after_pressed(Keypad keypad_obj) {
  char pressed_key = keypad_obj.getKey(); // Instantiate an object of pressed key
                                          // Ususally it will be 0, unless a key is pressed, at which point a mapped char to that key will be saved into pressed_key
  // If any key was pressed, print it
  if(pressed_key) {
    Serial.println(pressed_key);
    delay(200); // delay for 200ms to give the user time to release the button
  }
}

// This function operates the calculator working with a keypad (only one operation at a time can be performed, it is a simple calculator)
// The keys must be mapped previously to correspond to a calculator keys
// Also, be careful to not go over float limit of 7 digits with decimal in between
void calculator_keypad(Keypad keypad_obj) {
  float first_number  = 0;    // first number inputted by the user from the calculator
  float second_number = 0;    // second number inputted by the user from the calculator
  float result;               // result of the operation inputted by the user
  long divider = 0;           // divider to get the numbers dynamically
  char operation = '\0';      // operation to be performed by the program in the calculator
  char pressed_key = NO_KEY;  // Key pressed by the user, initally no key is pressed

  // While the user does not want to get the result of operation
  while(pressed_key != '=') {
    // Keep getting the key as long as nothing is pressed
    while(pressed_key == NO_KEY) {
      pressed_key = keypad_obj.getKey(); // get the key 
      delay(10);
    }
    // If a key was pressed, delay for 200 and run the rest of the loop
    delay(200);

    // If a key pressed is an operation then save that operation to operation char
    if(pressed_key == '+' || pressed_key == '*' || pressed_key == '/' || pressed_key == '-') {
      operation = pressed_key;
      first_number /= divider == 0 ? 1 : divider; // divide the first number by the saved divider (or 1 if divider is 0)
      divider = 0;                                // reset the divider
    }
    
    // If it was a number and no operation was inputted change first number and print the digit:
    // Also . indicating a decimal point needs to be considered
    if(pressed_key >= '0' && pressed_key <= '9' || pressed_key == '.' ) {
      if(pressed_key == '.') {
        divider = 1; // this way the divider will increase only after the . is pressed
      }
      else {
        divider *= 10; // Increase the divider (first number will be divided by that to adjust for the decimal)
        // if no operation was entered then modify the first number
        if(operation == '\0') {
          first_number = first_number * 10 + (pressed_key - '0');
        }
        // otherwise modify the second number
        else {
          second_number = second_number * 10 + (pressed_key - '0');
        }
      }
    }
    
    Serial.print(pressed_key); // print the key to a serial monitor
    if(pressed_key != '=') {
      pressed_key = NO_KEY; // reset they key pressed to no key pressed at the end of the loop
      // unless it's a = sign, in which case the loop should end
    }
  }
  second_number /= divider == 0 ? 1 : divider; // divide the second number by the divider (or 1 if divider is 0);
  // depending on the operation calculate the result in a different way
  // default to 0
  switch(operation) {
    case '+':
      result = first_number + second_number;
      break;
    case '-':
      result = first_number - second_number;
      break;
    case '*':
      result = first_number * second_number;
      break;
    case '/':
      result = first_number / second_number;
      break;
    default:
      result = 0;
      break;
  }
  Serial.println(result, 4); // print the result with 4 decimal precision
}
