
/*
 * LCD stands for Liquid Crystal Display, and allows me to display text on
 * a limited amount of space. Most LCDs have built in drivers that allow the user to program them easily. 
 * The LCD I used was 1602A and to work with it I use the LiquidCrystal library.
 * One must also connect the LCD to Arduino in a proper way for everything to work.
 */

#include <LiquidCrystal.h> // Include the library used to control the LCD

#define BAUD_RATE 9600
#define LCD_X 16
#define LCD_Y 2

LiquidCrystal lcd_0(2, 3, 4, 5, 6, 7); // Initialize the LCD on pins from 2 to 7
/*
 * pin 2 is connected to RS (Register Select) which shifts between command/data register
 * pin 3 is connected to E (Enable) which enables/disables the data reception
 * pins 4 to 7 are connected to D4 to D7 data pins of the LCD
 */

void setup() {
  Serial.begin(BAUD_RATE);
  
  lcd_0.begin(LCD_X, LCD_Y); // This method tells the program to begin working with an LCD that has 16 characters and 2 lines
  
  print_string_LCD(lcd_0); // print a string inputted by a user from the serial monitor

  blink_display(lcd_0); // blink a message on the LCD to the user

  LCD_timer(lcd_0);
  
  move_msg_along_LCD(lcd_0);
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
                          // Initially I set the cursor to position 0, 0 (X, Y)
  if(str_length <= LCD_X) {  // If the length of the string is lower than or equal to 16, I just print it on the LCD
    lcd.print(input_string);
  }
  else {                  // otherwise I print it on the two lines
    lcd.print(input_string.substring(0, LCD_X - 1));
    lcd_0.setCursor(0, 1);
    lcd.print(input_string.substring(LCD_X - 1, str_length)); // it will print it until the total length is 32, at which point the string is cut
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

// This function shows a changing timer on the LCD
void LCD_timer(LiquidCrystal lcd) {
  double time_measured = 0;   // Time measured since the user started the timer
  int upper_time_limit;       // Upper limit of the timer set by the user
  float time_interval = 0.5;  // Time interval that increases the time in every loop iteration
  String message_LCD = "Timer time: "; // Message shown on the LCD to the user
  
  lcd.setCursor(0, 0);            // Print message on the LCD
  lcd.print(message_LCD);
  lcd.setCursor(0, 1);

  Serial.println("Please enter how many seconds the timer should run for:");
  while(Serial.available() == 0) {}            // Wait for the user to enter the string
  upper_time_limit = (Serial.readStringUntil('\n')).toInt(); // Read the string until endline and convert it to integer

  // Run the timer until it reaches the upper limit set by the user
  while(time_measured <= upper_time_limit) {
    delay(time_interval * 1000);        // delay the timer by the required time
    lcd.print(time_measured);           // print the time on the LCD and increase the timer
    lcd.print("s");
    time_measured += time_interval;
    lcd.setCursor(0, 1);                // set the cursor to desired position
  }

  delay(10000); // At the end print final value for 10s and then clear lcd
  lcd.clear();
  
}

// The function below asks the user to enter a message to a serial monitor
// And then moves that message along on the LCD from left to right and top to bottom
void move_msg_along_LCD(LiquidCrystal lcd) {
  String user_msg;          // message from the user
  int msg_length;           // length of the message string
  int cursor_position = 0;  // position of the cursor
  
  Serial.println("Please enter the message that will move along the LCD:");
  Serial.println("(Length must be lower or equal to the width of LCD)");
  while(Serial.available() == 0) {}        // Wait for the user to enter the string
  user_msg = Serial.readStringUntil('\n'); // Read the string until endline
  Serial.println("User message: " + user_msg);
  
  msg_length = user_msg.length();          // Calculate the string length

  lcd.clear();                             // Clear the LCD to make sure nothing is there

  // Run the loop that will keep moving the message
  while(1) {
    // The formulas only work if msg_length <= LCD_X
    // Otherwise, the if statement wouldnt work (LCD_X - msg_length would be negative, cursor_position would always be greater than negative)
    lcd.setCursor(cursor_position % LCD_X, (cursor_position / LCD_X) % LCD_Y); // This sets the cursor in the desired position
    lcd.print(user_msg);                                                       // This prints the message on the LCD
    // If the message is moving over the boundary of the screen then print the substring that was cut off on the left side
    if(cursor_position % LCD_X > LCD_X - msg_length) {
      lcd.setCursor(0, (cursor_position / LCD_X  + 1) % LCD_Y); // Put the cursor on the left side of the screen and on the proper Y coordinate
      lcd.print(user_msg.substring((LCD_X - cursor_position % LCD_X), msg_length)); // Print the substring that disappeared on the right
    }
    delay(1000);
    lcd.setCursor(cursor_position % LCD_X, (cursor_position / LCD_X) % LCD_Y); // Move the cursor to the position of the start of message and clear the first letter
    lcd.print(" ");
    
    cursor_position += 1; // Increase the cursor position
    cursor_position %= LCD_Y * LCD_X; // This makes sure the cursor position moves in a loop - if it reaches the end of the LCD it is reset to 0
  }
}
