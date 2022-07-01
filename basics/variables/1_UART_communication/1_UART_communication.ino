/*
 * To communicate with the computer arduino uses UART - A universal asynchronous receiver-transmitter.
 * The way it works is it sends strings of bits that are assembled into information.
 * Transmission starts with a start bit (BS, always 0), then there are between 7 and 9 data bits, and stop bit (BK, always 1) at the end
 * In arduino there are two pins using UART - Tx, to transmit data (pin 1), and Rx to receive data (pin 0)
 * For the transmission to be successful, both parties communicating must have the same data exchange rate - baud-rate (number of bits transferred per second)
 * Arduino is equipped with a UART <-> USB converter, which allows it to communicate with a computer without using pins Rx and Tx.
 */

void setup() {
  // Arduino IDE has a built-in serial monitor to communicate with an Arduino board.
  Serial.begin(9600); // To begin communication with the serial monitor use Serial.begin(baud_rate)
  Serial.println("Hello World!"); // To print a line use Serial.println(expression_to_print);
}

void loop() {
  delay(5000);
  Serial.println("5 seconds have passed");
  

}
