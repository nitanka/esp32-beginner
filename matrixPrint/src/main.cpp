#include <Arduino.h>

// 74HC595 shift register wiring
const int pinData  = 23; // SER / DS
const int pinClock = 18; // SRCLK / SH_CP
const int pinLatch = 5;  // RCLK / ST_CP
// OE tied to GND (output always enabled) and MR tied to VCC (never reset)
// on the breadboard/diagram side.

// 74HC595 output QA..QH wired straight to 7-segment pins a,b,c,d,e,f,g,dp
// Byte bit0=a bit1=b bit2=c bit3=d bit4=e bit5=f bit6=g bit7=dp
void writeSegments(byte pattern) {
  digitalWrite(pinLatch, LOW);
  shiftOut(pinData, pinClock, MSBFIRST, pattern);
  digitalWrite(pinLatch, HIGH); // latch shifted byte onto QA..QH
}

// Single-digit 7-segment letter shapes (best-effort where no diagonal exists)
const byte SEG_A = 0x77;
const byte SEG_I = 0x06; // right-side vertical bar
const byte SEG_N = 0x54; // lowercase-style hump "n"
const byte SEG_T = 0x78; // lowercase-style "t"
const byte SEG_K = 0x76; // approximated (reuses an H-like shape)
const byte SEG_BLANK = 0x00;

const byte message[] = {
  SEG_N, SEG_I, SEG_T, SEG_A, SEG_N, SEG_K, SEG_A
};
const int messageLen = sizeof(message) / sizeof(message[0]);

void setup() {
  pinMode(pinData, OUTPUT);
  pinMode(pinClock, OUTPUT);
  pinMode(pinLatch, OUTPUT);
  writeSegments(SEG_BLANK);
}

void loop() {
  // one digit can only show one letter at a time, so step through them
  for (int i = 0; i < messageLen; i++) {
    writeSegments(message[i]);
    delay(600);
  }
  writeSegments(SEG_BLANK);
  delay(400);
}
