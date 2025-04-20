#include <Arduino.h>
#include <Wire.h>

const int mainSystemAddress = 0x10; // I2C address of this main system
const int bufferSize = 32; // Buffer size for incoming messages
void receiveEvent(int howMany);

void setup() {
  Serial.begin(9600);
  Wire.begin(mainSystemAddress); // Join I2C bus with address
  Wire.onReceive(receiveEvent);  // Register event for I2C data reception
}

void loop() {
  // Main loop does nothing, waiting for I2C events
  delay(100);
}

// Function to execute when data is received over I2C
void receiveEvent(int howMany) {
  char buffer[bufferSize];
  int index = 0;

  while (Wire.available() && index < bufferSize - 1) { // Leave space for null terminator
    char c = Wire.read();
    buffer[index++] = c;
  }
  buffer[index] = '\0'; // Null-terminate the buffer

  // Print the received message
  Serial.print("Received message: ");
  Serial.println(buffer);

  // Parse the message to ensure it follows the protocol
  if (strncmp(buffer, "$ARDU:ALLS:SHDN:YES;", 25) == 0) {
    Serial.println("Shutdown command received. Initiating shutdown procedure...");
  }
}