#include "Arduino.h"
#include "ESP8266LaboiteMAX72XX.h"

LedMatrixPanel::LedMatrixPanel(void) {

}

void LedMatrixPanel::init() {
  pinMode(pinMOSI, OUTPUT);
  digitalWrite(pinMOSI, LOW);

  pinMode(pinCS1, OUTPUT);
  digitalWrite(pinCS1, HIGH);

  pinMode(pinCS2, OUTPUT);
  digitalWrite(pinCS2, HIGH);

  pinMode(pinCLK, OUTPUT);
  digitalWrite(pinCLK, LOW);

  commandAll(DECODE_MODE, NO_DECODE);
  commandAll(INTENSITY, INTENSITY_MIN);
  commandAll(SCAN_LIMIT, DISPLAY_ALL_DIGITS);
  commandAll(SHUTDOWN, NORMAL_OPERATION);
  commandAll(DISPLAY_TEST, DISPLAY_TEST_NORMAL_OPERATION);
  clear();
}

void LedMatrixPanel::shiftMSBFirst(uint8_t data) {
  uint8_t k;
  for (uint8_t j = 0; j < 8; j++) {
    k = data & 0x80;  // return the MSB
    data = data << 1; // move the control character to the left one
    k = k >> 7;       // position the value at the LSB
    MAX72XX_CLK_0;
    MAX72XX_DATA(k);  // send the value to the data port
    CLK_DELAY;

    MAX72XX_CLK_1;    // clock pulse
    CLK_DELAY;
  }
}

void LedMatrixPanel::shiftLSBFirst(uint8_t data) {
  uint8_t k;
  for (uint8_t j = 0; j < 8; j++) {
    k = data & 0x01;  // return the LSB
    data = data >> 1; // move the control character to the right one
    MAX72XX_CLK_0;
    MAX72XX_DATA(k);  // send the value to the data port
    CLK_DELAY;

    MAX72XX_CLK_1;    // clock pulse
    CLK_DELAY;
  }
}

void LedMatrixPanel::command(uint8_t address, uint8_t data) {
  shiftMSBFirst(address);
  shiftMSBFirst(data);
}

void LedMatrixPanel::sendDigit(uint8_t digit, uint8_t data) {
  shiftMSBFirst(digit);
  shiftLSBFirst(data);
}

void LedMatrixPanel::commandAll(uint8_t address, uint8_t data) {
  MAX72XX_CS1_0;
  MAX72XX_CS2_0;

  for (uint8_t i = 0; i < 4; i++) {
    command(address, data);
  }

  MAX72XX_CS1_1;
  MAX72XX_CS2_1;
}

void LedMatrixPanel::intensity(uint8_t value) {
  // value between 0 and 15
  if (value > 15) {
    value = 15;
  }
  commandAll(INTENSITY, value);
}

void LedMatrixPanel::clear() {
  for (uint8_t digit = 1; digit < 9; digit++) {
    commandAll(digit, 0);
  }
}

void LedMatrixPanel::test() {
  while(1) {
    for (uint8_t digit = 1; digit < 9; digit++) {
      commandAll(digit, 0b10101010);
    }
    delay(1000);
    for (uint8_t digit = 1; digit < 9; digit++) {
      commandAll(digit, 0b01010101);
    }
    delay(1000);
  }
}


void LedMatrixPanel::display(uint8_t * buffer64) {
  for (uint8_t ligne = 1; ligne < 9; ligne++) {
    MAX72XX_CS1_0;
    for (uint8_t driver = 0; driver < 4; driver++) {
      sendDigit(ligne, buffer64[4 * (9 - ligne) - driver + 31]);
    }
    for (uint8_t driver = 0; driver < 4; driver++) {
      sendDigit(ligne, buffer64[4 * (9 - ligne) - driver - 1 ]);
    }
    MAX72XX_CS1_1;
  }
}
