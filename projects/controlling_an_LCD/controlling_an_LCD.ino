/*
 * LCD stands for Liquid Crystal Display, and allows me to display text on
 * a limited amount of space. Most LCDs have built in drivers that allow the user to program them easily. 
 * The LCD I used was 1602A and to work with it I use the LiquidCrystal library.
 * One must also connect the LCD to Arduino in a proper way for everything to work.
 */

#include <LiquidCrystal.h> // Include the library used to control the LCD

#define BAUD_RATE 9600

LiquidCrystal lcd_0(2, 3, 4, 5, 6, 7); // Initialize the LCD on pins from 2 to 7
/*
 * pin 2 is connected to RS (Register Select) which shifts between command/data register
 * pin 3 is connected to E (Enable) which enables/disables the data reception
 * pins 4 to 7 are connected to D4 to D7 data pins of the LCD
 */

void setup() {
  Serial.begin(BAUD_RATE);
  
  lcd_0.begin(16, 2); // This method tells the program to begin working with an LCD that has 16 columns and 2 rows
  
  print_string_LCD(lcd_0); // print a string inputted by a user from the serial monitor

  blink_display(lcd_0); // blink a message on the LCD to the user
}

void loop() {
  // put your main code here, to run repeatedly:

}

// The function below asks the user to enter some string input and print that input on an LCD
// It accepts an lcd instance as an argument
void print_string_LCD(LiquidCrystal lcd) {
  String input_string; // The string that will be inputted by the user
  int str_length;      // The length of the inputted string
  
  Serial.println("Enter a sentence (up to 32 characters) to display on the LCD:");
  
  while(Serial.available() == 0) {}            // Wait for the user to enter the string
  input_string = Serial.readStringUntil('\n'); // Read the string until endline
  str_length = input_string.length();          // save the length of the string

  lcd.setCursor(0, 0);    // The LCD displays the characters by setting a cursor position on the display and showing the character there
                          // Initially I set the cursor to position 0, 0
  if(str_length <= 16) {  // If the length of the string is lower than or equal to 16, I just print it on the LCD
    lcd.print(input_string);
  }
  else {                  // otherwise I print it on the two lines
    lcd.print(input_string.substring(0, 15));
    lcd_0.setCursor(0, 1);
    lcd.print(input_string.substring(15, str_length)); // it will print it until the total length is 32, at which point the string is cut
  }
  
  lcd.blink(); // At the end blink the cursor to show its position
  // if I wanted to make the cursor just appear stable I would use lcd.cursor(); 
  // lcd.noCursor(); would turn the cursor off
  // also there are 2 versions of a cursor - an underscore _, or a full rectangle []
  // blink/noBlink shows rectangle
  // cursor/noCursor shows undersocre
  
  Serial.println(input_string); 

  delay(10000);
  lcd.clear(); // After 10s of displaying the string, clear the display
  lcd.noBlink(); // Also stop blinking
}

// This function shows a message to an LCD and blinks the display
// It accepts an lcd instance as an argument
void blink_display(LiquidCrystal lcd) {
  lcd.setCursor(0, 0);      // Set cursor to position 0, 0
  lcd.print("Hello World!");// Print the message
  lcd.cursor();             // Show the cursor

  // Blink the message 5 times
  for(int i = 0; i < 5; ++i) {
    lcd.display();
    delay(2000);
    lcd.noDisplay();
    delay(2000);
  }
  
  lcd.clear();    // Clear the display at the end
  lcd.noCursor(); // and turn the cursor off
  
}

// TODO
