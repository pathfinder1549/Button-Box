#include <Arduino.h>

int buttonState;

void setup() {
  // put your setup code here, to run once:
  pinMode(0, OUTPUT);
  pinMode(5, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(5);
  if (buttonState == 1) {
    digitalWrite(0, 1);
  } else {
    digitalWrite(0, 0);
  }
}