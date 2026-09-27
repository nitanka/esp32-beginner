#include <Arduino.h>

// Your validated hardware pins from the passing blink test
const int dataPin  = 19;  // DS (Pin 14) -> Connected to D19
const int latchPin = 18;  // RCLK (Pin 12) -> Connected to D18
const int clockPin = 21;  // SRCLK (Pin 11) -> Connected to D21

void pulseClock() {
  delayMicroseconds(50);
  digitalWrite(clockPin, HIGH);
  delayMicroseconds(50);
  digitalWrite(clockPin, LOW);
  delayMicroseconds(50);
}

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  
  digitalWrite(latchPin, LOW);
  digitalWrite(clockPin, LOW);
  digitalWrite(dataPin, LOW);
}

void loop() {
  // ==========================================
  // STATE 1: 00 (Both LEDs OFF)
  // ==========================================
  digitalWrite(latchPin, LOW);
  
  // Push 8 LOW bits down the conveyor belt
  digitalWrite(dataPin, LOW); pulseClock(); // Moves to Q7
  digitalWrite(dataPin, LOW); pulseClock(); // Moves to Q6
  digitalWrite(dataPin, LOW); pulseClock(); // Moves to Q5
  digitalWrite(dataPin, LOW); pulseClock(); // Moves to Q4
  digitalWrite(dataPin, LOW); pulseClock(); // Moves to Q3
  digitalWrite(dataPin, LOW); pulseClock(); // Moves to Q2
  digitalWrite(dataPin, LOW); pulseClock(); // Lands on Q1 (LED 2) -> OFF
  digitalWrite(dataPin, LOW); pulseClock(); // Lands on Q0 (LED 1) -> OFF
  
  digitalWrite(latchPin, HIGH);
  delay(1500); 

  // ==========================================
  // STATE 2: 01 (LED 1 ON, LED 2 OFF)
  // ==========================================
  digitalWrite(latchPin, LOW);
  
  digitalWrite(dataPin, LOW);  pulseClock(); // Moves to Q7
  digitalWrite(dataPin, LOW);  pulseClock(); // Moves to Q6
  digitalWrite(dataPin, LOW);  pulseClock(); // Moves to Q5
  digitalWrite(dataPin, LOW);  pulseClock(); // Moves to Q4
  digitalWrite(dataPin, LOW);  pulseClock(); // Moves to Q3
  digitalWrite(dataPin, LOW);  pulseClock(); // Moves to Q2
  digitalWrite(dataPin, LOW);  pulseClock(); // Lands on Q1 (LED 2) -> OFF
  digitalWrite(dataPin, HIGH); pulseClock(); // Lands on Q0 (LED 1) -> ON
  
  digitalWrite(latchPin, HIGH);
  delay(1500);

  // ==========================================
  // STATE 3: 10 (LED 1 OFF, LED 2 ON)
  // ==========================================
  digitalWrite(latchPin, LOW);
  
  digitalWrite(dataPin, LOW);  pulseClock(); // Moves to Q7
  digitalWrite(dataPin, LOW);  pulseClock(); // Moves to Q6
  digitalWrite(dataPin, LOW);  pulseClock(); // Moves to Q5
  digitalWrite(dataPin, LOW);  pulseClock(); // Moves to Q4
  digitalWrite(dataPin, LOW);  pulseClock(); // Moves to Q3
  digitalWrite(dataPin, LOW);  pulseClock(); // Moves to Q2
  digitalWrite(dataPin, HIGH); pulseClock(); // Lands on Q1 (LED 2) -> ON
  digitalWrite(dataPin, LOW);  pulseClock(); // Lands on Q0 (LED 1) -> OFF
  
  digitalWrite(latchPin, HIGH);
  delay(1500);

  // ==========================================
  // STATE 4: 11 (Both LEDs ON)
  // ==========================================
  digitalWrite(latchPin, LOW);
  
  digitalWrite(dataPin, LOW);  pulseClock(); // Moves to Q7
  digitalWrite(dataPin, LOW);  pulseClock(); // Moves to Q6
  digitalWrite(dataPin, LOW);  pulseClock(); // Moves to Q5
  digitalWrite(dataPin, LOW);  pulseClock(); // Moves to Q4
  digitalWrite(dataPin, LOW);  pulseClock(); // Moves to Q3
  digitalWrite(dataPin, LOW);  pulseClock(); // Moves to Q2
  digitalWrite(dataPin, HIGH); pulseClock(); // Lands on Q1 (LED 2) -> ON
  digitalWrite(dataPin, HIGH); pulseClock(); // Lands on Q0 (LED 1) -> ON
  
  digitalWrite(latchPin, HIGH);
  delay(1500);
}
