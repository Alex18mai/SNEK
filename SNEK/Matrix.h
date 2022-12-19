// Matrix

#ifndef SNEK_MATRIX_H
#define SNEK_MATRIX_H

#include <LedControl.h>
#include "Memory.h"

const uint64_t matrixImageSmile = 0x003c420000226600,
               matrixImageMenu = 0xc3c3c3dbffe7c381,
               matrixImageTop = 0x0e0a2e20e2a2e207,
               matrixImageSettings = 0xffffc0ffff03ffff,
               matrixImageAbout = 0x6666667e7e667e7e,
               matrixImageHowToPlay = 0x6666667e7e666666,
               matrixImageGameEnd = 0x7090977107d1b790;

const int dinPin = 12,
          clockPin = 11,
          loadPin = 10;

LedControl lc = LedControl(dinPin, clockPin, loadPin, 1);  // DIN, CLK, LOAD, No. DRIVER

const byte matrixSize = 8;

bool matrixChanged = true;

byte matrix[matrixSize][matrixSize] = {
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 }
};

void matrixSetup() {
  // the zero refers to the MAX7219 number, it is zero for 1 chip
  lc.shutdown(0, false);                 // turn off power saving, enables display
  lc.setIntensity(0, matrixBrightness);  // sets brightness (0~15 possible values)
  lc.clearDisplay(0);                    // clear screen
}

void updateMatrix() {
  for (int row = 0; row < matrixSize; row++) {
    for (int col = 0; col < matrixSize; col++) {
      lc.setLed(0, col, row, matrix[row][col]);
    }
  }
}

void displayMatrixImage(uint64_t image) {
  for (int i = 0; i < 8; i++) {
    byte row = (image >> i * 8) & 0xFF;
    for (int j = 0; j < 8; j++) {
      lc.setLed(0, j, i, bitRead(row, j));
    }
  }
}

#endif