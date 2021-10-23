#include <Arduino.h>
#include <SPI.h>

#define NUMBER_OF_ROWS 5
#define NUMBER_OF_COLS 9
#define NUMBER_OF_COLS_LEFT_SIDE 7
#define KEY_SEPARATOR "_"
#define REPORT_END_CHAR "$"

byte colPins[] = {7, 6, 5, 4, 3, 2, 10, 16, 14};
byte rowPins[] = {A0, A1, A2, A3, 15};

byte keys[NUMBER_OF_ROWS][NUMBER_OF_COLS];

void setup(){
  /* Serial.begin(115200); */
  Serial1.begin(9600);
}

void loop(){
  readMatrix();
  delay(100);
}

void readMatrix() {
  int keysReported = 0 ;
  int currentPosition = 0;

  for (int rowIndex = 0; rowIndex < NUMBER_OF_ROWS; rowIndex++) {
    byte rowPin = rowPins[rowIndex];
    pinMode(rowPin, OUTPUT);
    digitalWrite(rowPin, LOW);

    for (int colIndex = 0; colIndex < NUMBER_OF_COLS; colIndex++) {
      byte columnPin = colPins[colIndex];
      pinMode(columnPin, INPUT_PULLUP);
      keys[rowIndex][colIndex] = digitalRead(columnPin);
      pinMode(columnPin, INPUT);

      if (keys[rowIndex][colIndex] == 0) {
        if (keysReported < 5) {
          int p = getKeyPosition(rowIndex, colIndex);
          char c[2];
          sprintf(c, "%02u", p);

          if (keysReported > 0) {
            Serial1.print(KEY_SEPARATOR);
          }
          Serial1.print(c);
          keysReported += 1;
        }
      }
    }

    pinMode(rowPin, INPUT);
  }

  if (keysReported > 0) {
    Serial1.print(REPORT_END_CHAR);
  }
}

int getKeyPosition(int row, int col) {
  return (row * (NUMBER_OF_COLS + NUMBER_OF_COLS_LEFT_SIDE)) + NUMBER_OF_COLS_LEFT_SIDE + col;
}
