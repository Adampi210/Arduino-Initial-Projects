/*
 * This is a basic program for LED control.
 * When starting a program I always see two functions of void type: setup and loop.
 * The setup function executes once, and the loop function executes continually after setup.
 * In this program a basic LED control is presented.
 * In arduino one of the basic things is controlling the input and output pins of the board.
 * This allows me to translate the written code into real-world projects.
 */

#define LED_0 8 // defining a pin for LED_0 as 8 (this way I can later change it)
#define LED_1 9
#define LED_2 10
#define BUTTON_0 7 // defining a pin for a button as 7

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_0, OUTPUT);     // pinMode function allows me to set a mode of a pin - can be INPUT, OUTPUT, or INPUT_PULLUP
  pinMode(LED_1, OUTPUT); 
  pinMode(LED_2, OUTPUT); 
  pinMode(BUTTON_0, INPUT_PULLUP); // set mode to the button pin as INPUT_PULLUP 
  
  digitalWrite(LED_0, HIGH);  // digitalWrite function sets the state of a pin, either HIGH or LOW
  
  blink_an_LED(LED_1, 800, 3);

  blink_when_click(LED_2, 800, 3, BUTTON_0);

  delay(300);
}

void loop() {
  // put your main code here, to run repeatedly:
  // After the setup functions the LEDs will blink continually at different speeds
  digitalWrite(LED_0, HIGH);
  digitalWrite(LED_1, HIGH);
  digitalWrite(LED_2, HIGH);

  delay(500);
  digitalWrite(LED_2, LOW);
  delay(500);
  digitalWrite(LED_1, LOW);
  delay(1000);
  digitalWrite(LED_0, LOW);
  delay(1000);

}

// The function below blinks an LED a specified number of times, with a specified blinking interval time
void blink_an_LED(int LED_pin_number, int blinking_interval, int num_of_blinks) {
  // for loop determines how many times an LED will blink
  for(int i = 0; i < num_of_blinks; ++i) {
    digitalWrite(LED_pin_number, HIGH);
    delay(blinking_interval); // delay stops execution of a program by a desired time (in ms)
    digitalWrite(LED_pin_number, LOW);
    delay(blinking_interval);
  }
}

// This function awaits for the user to press the button and then blinks an LED in a specified way
void blink_when_click(int LED_pin_number, int blinking_interval, int num_of_blinks, int button) {
  // This while loop will keep running until a button is clicked, then the rest is executed
  while(digitalRead(button) == HIGH) {}
  // To blink an LED I just call blink_an_LED function
  blink_an_LED(LED_pin_number, blinking_interval, num_of_blinks);
}
