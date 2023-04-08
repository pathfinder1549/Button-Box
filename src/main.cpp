#include <Arduino.h>
#include <Joystick.h>

const int BUTTON_COUNT = 2;
const int HAT_COUNT = 0;
int lastButtonState[BUTTON_COUNT];

Joystick_ buttonBox(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
  BUTTON_COUNT, HAT_COUNT,
  false, false, false, false, false, false, false, false, false, false, false);

void setup() {
  // put your setup code here, to run once:
  pinMode(0, OUTPUT);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);

  buttonBox.begin();

  for (int i=0; i<BUTTON_COUNT; i++) {
    lastButtonState[i] = 0;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int index=0; index<BUTTON_COUNT; index++) {
    int currentButtonState = !digitalRead(index + 1);
    if (currentButtonState != lastButtonState[index]) {
      buttonBox.setButton(index, currentButtonState);
      lastButtonState[index] = currentButtonState;
    }
  }

  if (lastButtonState[1] == 1) {
    digitalWrite(0, 1);
  } else {
    digitalWrite(0, 0);
  }
}