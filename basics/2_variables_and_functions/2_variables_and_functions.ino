// Arduino uses C++ language to program the boards, and therefore it can use standard variables as seen below:
// Every variable not defined in a function is a global variable - available everywhere in the program

// Also, I define a macro here to print the variables easier
#define print_var_to_monitor(variable) do {           \
    Serial.print(#variable);                          \
    Serial.print(": ");                               \
    Serial.println(variable);                         \
  } while(false)

// This macro prints a number in a desired specified number base
#define print_num_in_base(number, base) do {                \
    Serial.print("Number in ");                             \
    Serial.print(#base);                                    \
    Serial.print(": ");                                     \
    Serial.println(number, base);                           \
  } while(false)
  
#define BAUD_RATE 9600

bool logic = false;    // bool(ean) - variables that can be either true or false
int integer_num = 10; // int - 16-bit (2 bytes) integers in a range from  -32,768 to 32,767 in Arduino uno
long large_integer_num = 2000000; // long - 32-bit (4 bytes) integers in a range from -2,147,483,648 to 2,147,483,647
float floating_point_number = 3.14159265; // float - numbers with a decimal point, stored as 32 bits (4 bytes) of information (float can only store 7 digits, regardless of where the decimal point is)
char character = 'a'; // char - variable storing a character value
String char_string = "Hello World!"; // String - stores a character array (one can also create char array);
byte byte_num = 128; // byte - stores an 8-bit (1 byte) value
int global_variable = 1;

void setup() {
  int setup_local_variable = 10; // declare a local variable in setup
  
  Serial.begin(BAUD_RATE);

  // print all the variables to the serial monitor
  print_var_to_monitor(logic);
  print_var_to_monitor(integer_num);
  print_var_to_monitor(large_integer_num);
  print_var_to_monitor(floating_point_number);
  print_var_to_monitor(character);
  print_var_to_monitor(char_string);
  print_var_to_monitor(setup_local_variable);
  print_var_to_monitor(byte_num);

  // print some numbers in different bases
  different_bases_output(17);
  different_bases_output(0x68);
  different_bases_output(0110);

  Serial.println();
  
  delay(2000);
}

void loop() {
  int loop_local_variable = 0; // declare a local variable in loop, will reset every time:
  print_var_to_monitor(loop_local_variable); // print the local variable to serial monitor (should always be 0)
  
  delay(1000);

  // Modify the variables using functions
  loop_local_variable = add_and_multiply(loop_local_variable, integer_num, global_variable);
  modify_num_with_addr(&global_variable);
  modify_num_with_addr(&integer_num);

  // print again, should change
  print_var_to_monitor(loop_local_variable);
  delay(2000);
}

// This function modifies a number by adding something to it and multiplying it
int add_and_multiply(int num_to_modify, int num_to_add, int multiplier) {
  return((num_to_modify + num_to_add) * multiplier);
}

// This function modifies a value at a specified address (this allows me to modify the variables)
void modify_num_with_addr(int* a_value) {
  if(*a_value >= -10 && *a_value < 10) {
    *a_value += 1; 
  }
  else {
    *a_value = -10;
  }
}

// In c++ int does NOT have a nmumber base - it can be defined and expressed in any base desired
// This function has an integer number as an argument and prints that number in different bases
void different_bases_output(int number) {
  print_num_in_base(number, DEC);
  print_num_in_base(number, BIN);
  print_num_in_base(number, HEX);
  print_num_in_base(number, OCT);
}
