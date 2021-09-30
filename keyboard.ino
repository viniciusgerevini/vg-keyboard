#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"
#include "HIDKeys.h"
#include "KeyReport.h";

#if SOFTWARE_SERIAL_AVAILABLE
  #include <SoftwareSerial.h>
#endif

#define FACTORYRESET_ENABLE         0
#define MINIMUM_FIRMWARE_VERSION    "0.6.6"

Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

byte colPins[] = {5, 6, 9, 10, 11, 12, A5};
byte rowPins[] = {A0, A1, A2, A3, A4};

const int rowCount = 5;
const int colCount = 7;

byte keys[rowCount][colCount];


void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

void setup(void) {
  while (!Serial);  // required for Flora & Micro
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

  /* Add or remove service requires a reset */
  Serial.println(F("Performing a SW reset (service changes require a reset): "));
  if (! ble.reset() ) {
    error(F("Couldn't reset??"));
  }
}

void loop(void) {
  KeyReport report = readMatrix();
  if (report.wasKeyPressed()) {
//    Serial.println(report.getModifier(), HEX);
//    int* keys = report.getKeys();
//    ble.print("AT+BleKeyboard=");
//    ble.println("hello");

      ble.println(F("AT+BleKeyboardCode=02-00-04-05-06-00-00"));
      ble.println(F("AT+BLEKEYBOARDCODE=00-00"));

    if( ble.waitForOK() ) {
      Serial.println( F("OK!") );
    } else {
      Serial.println( F("FAILED!") );
    }
//    for (int i = 0; i < 6; i++) {
//      if (keys[i] != KEY_NONE){
//        ble.print("-07");
//        ble.print(keys[i],HEX);
//      }
      
//    }
//    ble.println("");
  
      //modifiers 
    //TODO get keys from left side
    //TODO send report
    //TODO release
    // key release notification
//    ble.println("AT+BleKeyboardCode=00-00");
  }
  delay(100);
}

KeyReport readMatrix() {
  KeyReport report;

  for (int rowIndex = 0; rowIndex < rowCount; rowIndex++) {
    // set row output to low
    byte rowPin = rowPins[rowIndex];
    pinMode(rowPin, OUTPUT);
    digitalWrite(rowPin, LOW);

    for (int colIndex = 0; colIndex < colCount; colIndex++) {
      byte columnPin = colPins[colIndex];
      pinMode(columnPin, INPUT_PULLUP);
      keys[rowIndex][colIndex] = digitalRead(columnPin);
      pinMode(columnPin, INPUT);
      if (keys[rowIndex][colIndex] == 0) {
        // TODO translate coordinates to key mappings
        // TODO isModifier
        report.addKey(KEY_D);
      }
    }
 
    pinMode(rowPin, INPUT);
  }

  return report;
}