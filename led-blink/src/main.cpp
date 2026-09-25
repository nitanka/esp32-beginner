/* simple test program to blink the onboard led 
Pin Reference: https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
*/

#include <Arduino.h>

const int pinLed = 2;

void setup() {
  // Set the digital pin as an output
  pinMode(pinLed, OUTPUT);
}


void loop() {

  digitalWrite(pinLed, HIGH);
  delay(500);
  digitalWrite(pinLed, LOW);
  //delay(2000);
  delay(500);
}

