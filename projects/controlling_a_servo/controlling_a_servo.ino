/*
 * This simple project controls a servo using different ways. First, a user must specify using UART the mode for the servo.
 * In first mode the position of the servo is changing by itself in a loop. In second mode the position is controlled using UART, and in the third it is controlled using external potentiometer.
 */

#include <Servo.h> // Include library to handle a servo

#define BAUD_RATE 9600
#define SERVO_PIN 2
#define POT_PIN A0

Servo servo_0;          // initialize a servo object
int mode_of_operation;  // initialize a number defining mode of operation
int servo_position = 0; // initialize the position of the servo, from 0 to 180
int servo_pos_change = 6; // for the loop mode initialize how much a servo position will change in one loop iteration
int potentiometer_value = 0; // analog value read from the potentiometer

void setup() {
  Serial.begin(BAUD_RATE);
  servo_0.attach(SERVO_PIN); // attach function tells the code that servo is connected to a given pin
  mode_of_operation = ask_user_to_choose_mode(); // get mode of operation from the user
  
}

void loop() {
  run_in_a_given_mode(mode_of_operation);
  delay(200);
}

// This function asks the user to enter the mode of operation the servo should work in
int ask_user_to_choose_mode() {
  int chosen_mode = 0;        // integer defining the mode of operation
  String received_mode = "";  // string received from the serial monitor defining the mode of operation
  
  Serial.println("Please enter the mode that the servo should operate in.");
  Serial.println("0 - servo runs automatically in a loop");
  Serial.println("1 - servo is controlled from a potentiometer");
  Serial.println("2 - servo is controlled using UART");
  
  while(Serial.available() == 0) {} // wait for the user to enter the mode

  received_mode = Serial.readStringUntil('\n');
  chosen_mode = received_mode.toInt(); // convert read string to an integer
  Serial.println("Chosen mode: " + received_mode);
  
  return(chosen_mode);
}

// This function calls different modes (other functions) depending on the input from the user
void run_in_a_given_mode(int mode) {
  // to switch between modes I use switch-case statement
  switch (mode) {
    case 0:
      loop_mode();
      break;
    case 1: 
      potentiometer_mode();
      break;
    case 2:
      UART_mode();
      break;
    default:
      loop_mode();
      break;
  }
}

// This mode continually increases the position of the servo from 0 to 180 and then resets it
void loop_mode() {
  if(servo_position < 180) {
    // if position is not max, write the current position to the servo
    servo_0.write(servo_position);
  }
  else {
    // if it is max or higher (>= 180) then reset it to 0
    servo_position = 0;
  }

  servo_position += servo_pos_change;
}

// This mode reads potentiometer value as analog input and based on that it sets the servo in the desired position 
void potentiometer_mode() {
  potentiometer_value = analogRead(POT_PIN);
  servo_position = map(potentiometer_value, 0, 1023, 0, 180); // map the potentiometer value to servo position
  servo_0.write(servo_position);
}

// This mode waits for the user to input the desired position in the Serial Monitor
// And based on that it sets the servo in the designated position
void UART_mode() {
  String read_position_str = ""; // initialize a string to store the position
  Serial.println("Please enter a value between 0 and 180:");

  while(Serial.available() == 0) {} // wait for user input
  
  if(Serial.available() > 0) {
    // read position as an integer
    read_position_str = Serial.readStringUntil('\n');
    servo_position = read_position_str.toInt();

    // if it is out of bounds print error message and call the function again
    if(servo_position < 0 || servo_position > 180) {
      Serial.println("Wrong input!");
      servo_position = 0;
      UART_mode();
    }
    // else write the position to the servo
    else {
      servo_0.write(servo_position);
      Serial.println(servo_position);
    }
  }
}
