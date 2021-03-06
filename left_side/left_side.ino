#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"
#include "HIDKeys.h"
#include "KeyReport.h";
#include "KeyMap.h";

#if SOFTWARE_SERIAL_AVAILABLE
  #include <SoftwareSerial.h>
#endif

#define FACTORYRESET_ENABLE         0
#define MINIMUM_FIRMWARE_VERSION    "0.6.6"

Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

#define NUMBER_OF_ROWS 5
#define NUMBER_OF_COLS 9

byte colPins[] = {5, 6, 9, 10, 11, 12, A5};
byte rowPins[] = {A0, A1, A2, A3, A4};

byte keys[NUMBER_OF_ROWS][NUMBER_OF_COLS];

bool wasReleased = true;
KeyReport previousReport;


void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

void setup(void) {
  delay(500);

  Serial.begin(115200);
  Serial.println(F("Adafruit Bluefruit HID Keyboard Example"));
  Serial.println(F("---------------------------------------"));

  /* Initialise the module */
  Serial.print(F("Initialising the Bluefruit LE module: "));

  if ( !ble.begin(VERBOSE_MODE) ) {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println( F("OK!") );

  if ( FACTORYRESET_ENABLE ) {
    /* Perform a factory reset to make sure everything is in a known state */
    Serial.println(F("Performing a factory reset: "));
    if ( !ble.factoryReset() ) {
      error(F("Couldn't factory reset"));
    }
  }

  /* Disable command echo from Bluefruit */
  ble.echo(false);

  Serial.println("Requesting Bluefruit info:");
  /* Print Bluefruit information */
  ble.info();

  /* Change the device name to make it easier to find */
  Serial.println(F("Setting device name to 'VG Keyboard': "));
  if (!ble.sendCommandCheckOK(F( "AT+GAPDEVNAME=VG Keyboard" )) ) {
    error(F("Could not set device name?"));
  }

  /* Enable HID Service */
  Serial.println(F("Enable HID Service (including Keyboard): "));
  if ( ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) ) {
    if ( !ble.sendCommandCheckOK(F( "AT+BleHIDEn=On" ))) {
      error(F("Could not enable Keyboard"));
    }
  }else {
    if (! ble.sendCommandCheckOK(F( "AT+BleKeyboardEn=On"  ))) {
      error(F("Could not enable Keyboard"));
    }
  }


  Serial1.begin(9600);

  /* Add or remove service requires a reset */
  /* Serial.println(F("Performing a SW reset (service changes require a reset): ")); */
  /* if (! ble.reset() ) { */
  /*   error(F("Couldn't reset??")); */
  /* } */
}

void loop(void) {
  KeyReport report = readMatrix();
  if (!wasReleased && report.isEqual(previousReport)) {
    delay(100);
    return;
  }

  if (report.wasKeyPressed()) {
    int* keys = report.getKeys();
    ble.print(F("AT+BLEKEYBOARDCODE="));
    ble.print(report.getModifier(), HEX);
    ble.print(F("-00"));
    for (int i = 0; i < 6; i++) {
      ble.print("-");
      ble.print(keys[i],HEX);
    }
    ble.println("");
    wasReleased = false;
    previousReport = report;
    if( ble.waitForOK() ) {
      Serial.println( F("OK!") );
    } else {
      Serial.println( F("FAILED!") );
    }
  } else if (!wasReleased) {
    wasReleased = true;
    ble.println(F("AT+BLEKEYBOARDCODE=00-00"));
    if( ble.waitForOK() ) {
      Serial.println( F("OK!") );
    } else {
      Serial.println( F("FAILED!") );
    }
  }

  delay(100);
}


KeyReport readMatrix() {
  KeyReport report;
  int positions[6];
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
        int keycode = getKeyCodeAt(rowIndex, colIndex);
        if (isLayerToggle(keycode)) {
          changeLayer(keycode);
        } else if (isModifier(keycode)) {
          report.addModifier(getModifierCode(keycode));
        } else if (currentPosition < 6) {
          positions[currentPosition] = getKeyPosition(rowIndex, colIndex);
          currentPosition += 1;
        }
      }
    }
 
    pinMode(rowPin, INPUT);
  }

  if (Serial1.available()) {
    char output[15] = "";
    int result = Serial1.readBytesUntil('$', output, 15);
    Serial.println(result);
    if (result > 0) {
      Serial.println(output);
      char* ptr = strtok(output, "_");
      while (ptr) {
        if (currentPosition >= 6) {
          break;
        }

        int rightSidePos = atol(ptr);
        int keycode = getKeyCodeAtPosition(rightSidePos);
        if (isLayerToggle(keycode)) {
          changeLayer(keycode);
        } else if (isModifier(keycode)) {
          report.addModifier(getModifierCode(keycode));
        } else if (currentPosition < 6) {
          positions[currentPosition] = rightSidePos;
          currentPosition += 1;
        }

        ptr = strtok(NULL, "_");
      }
    }
  }

  for (int pos = 0; pos < currentPosition; pos++) {
    report.addKey(getKeyCodeAtPosition(positions[pos]));
  }
  resetLayer();

  return report;
}
