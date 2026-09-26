#include <Arduino.h>
const int dataPin  = 23;  // DS (Serial Input)
const int latchPin = 22;  // RCLK (Latch)
const int clockPin = 21;  // SRCLK (Clock)

// Hex code lookup array for numbers 0 to 9
// Because it is Common Anode, 0 = LED On, 1 = LED Off
// Mapped byte structure: [DP, G, F, E, D, C, B, A]
const byte caNumberMap[] = {
  0xC0, // 0 -> Binary: 11000000 (A,B,C,D,E,F are ON)
  0xF9, // 1 -> Binary: 11111001 (B,C are ON)
  0xA4, // 2 -> Binary: 10100100 (A,B,D,E,G are ON)
  0xB0, // 3 -> Binary: 10110000 (A,B,C,D,G are ON)
  0x99, // 4 -> Binary: 10011001 (B,C,F,G are ON)
  0x92, // 5 -> Binary: 10010010 (A,C,D,F,G are ON)
  0x82, // 6 -> Binary: 10000010 (A,C,D,E,F,G are ON)
  0xF8, // 7 -> Binary: 11111000 (A,B,C are ON)
  0x80, // 8 -> Binary: 10000000 (All segments are ON)
  0x90  // 9 -> Binary: 10010000 (A,B,C,D,F,G are ON)
};

void setup() {
  // Initialize the three ESP32 interface pins as outputs
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void loop() {
  // Incrementing loop to print digits 0 to 9
  for (int i = 0; i < 10; i++) {
    
    // Open the Shift Register workspace
    digitalWrite(latchPin, LOW);
    
    // Send out the 8-bit byte through the single data pin
    shiftOut(dataPin, clockPin, MSBFIRST, caNumberMap[i]);
    
    // Toggle the latch to instantly flash the current number onto the display
    digitalWrite(latchPin, HIGH);
    
    // Wait 1 second before moving to the next number
    delay(1000); 
  }
}