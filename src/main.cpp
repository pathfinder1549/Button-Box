#include <Arduino.h>
#include <Joystick.h>

#define BUTTON_COUNT 15
#define HAT_COUNT 0
#define NUM_DI 3



int lastButtonState[BUTTON_COUNT];

// set matrix array
byte rows[] = {21,22,23};
const int rowCount = sizeof(rows)/sizeof(rows[0]);
byte cols[] = {9,10,11,12};
const int colCount = sizeof(cols)/sizeof(cols[0]);
byte matrixKeys[colCount][rowCount];

// set discrete input array
byte inputKeys[NUM_DI];

Joystick_ buttonBox(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
  BUTTON_COUNT, HAT_COUNT,
  false, false, false, false, false, false, false, false, false, false, false);

void setup() {
  // put your setup code here, to run once:
  //pinMode(9, OUTPUT);           // matrix col 0
  //pinMode(10, OUTPUT);          // matrix col 1
  //pinMode(11, OUTPUT);          // matrix col 2
  //pinMode(12, OUTPUT);          // matrix col 3
  pinMode(18, INPUT);           // start button
  pinMode(19, INPUT);           // switch 1
  pinMode(20, INPUT);           // switch 2
  //pinMode(21, INPUT_PULLUP);    // matrix row 0
  //pinMode(22, INPUT_PULLUP);    // matrix rox 1
  //pinMode(23, INPUT_PULLUP);    // matrix row 2
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


void readMatrix() {
	// iterate the columns
	for (int colIndex=0; colIndex < colCount; colIndex++) {
		// col: set to output to low
		byte curCol = cols[colIndex];
		pinMode(curCol, OUTPUT);
		digitalWrite(curCol, LOW);

		// row: interate through the rows
		for (int rowIndex=0; rowIndex < rowCount; rowIndex++) {
			byte rowCol = rows[rowIndex];
			pinMode(rowCol, INPUT_PULLUP);
			matrixKeys[colIndex][rowIndex] = digitalRead(rowCol);
			pinMode(rowCol, INPUT);
		}
		// disable the column
		pinMode(curCol, INPUT);
	}
}

void readDI() {
  for (int i=0; i<3; i++) {
    inputKeys[i] = !digitalRead(i+18);

  }
}