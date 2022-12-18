// Memory - EEPROM

#ifndef SNEK_MEMORY_H
#define SNEK_MEMORY_H

#include <EEPROM.h>

const bool needInitEEPROM = false;  // set true to initialize EEPROM values

const int highscoreStartingAddress = 0,
          settingsStartingAddress = 100,
          highscoreCount = 5,
          nameSize = 3;

char highscoreNames[highscoreCount][nameSize];
int highscorePoints[highscoreCount];

char currentName[nameSize];

volatile int startDifficulty,
             lcdBrightness,
             matrixBrightness,
             soundSetting;

void readHighscores() {
  int address = highscoreStartingAddress;
  
  for (int i=0; i<highscoreCount; i++) {
    for (int j=0; j<nameSize; j++) {
      EEPROM.get(address, highscoreNames[i][j]);
      address += sizeof(char);
    }
  }
  
  for (int i=0; i<highscoreCount; i++) {
    EEPROM.get(address, highscorePoints[i]);
    address += sizeof(int);
  }
}

void readSettings() {
  int address = settingsStartingAddress;

  for (int i=0; i<nameSize; i++) {
    EEPROM.get(address, currentName[i]);
    address += sizeof(char);
  }
  
  EEPROM.get(address, startDifficulty);
  address += sizeof(int);

  EEPROM.get(address, lcdBrightness);
  address += sizeof(int);

  EEPROM.get(address, matrixBrightness);
  address += sizeof(int);

  EEPROM.get(address, soundSetting);
  address += sizeof(int);
}

void initHighscores() {
  int address = highscoreStartingAddress;
  
  for (int i=0; i<highscoreCount; i++) {
    for (int j=0; j<nameSize; j++) {
      EEPROM.put(address, char('A'));
      address += sizeof(char);
    }
  }
  
  for (int i=0; i<highscoreCount; i++) {
    EEPROM.put(address, 0);
    address += sizeof(int);
  }
}

void initSettings() {
  int address = settingsStartingAddress;

  for (int i=0; i<nameSize; i++) {
    EEPROM.put(address, 'A');
    address += sizeof(char);
  }
  
  EEPROM.put(address, MIN_DIFFICULTY);
  address += sizeof(int);

  EEPROM.put(address, MAX_LCD_BRIGHT);
  address += sizeof(int);

  EEPROM.put(address, MAX_MATRIX_BRIGHT);
  address += sizeof(int);

  EEPROM.put(address, NO_SOUND);
  address += sizeof(int);
}

void memorySetup() {
  if (needInitEEPROM) {
    initHighscores();
    initSettings();
  }
  readHighscores();
  readSettings();
}

void saveHighscores() {
  int address = highscoreStartingAddress;
  
  for (int i=0; i<highscoreCount; i++) {
    for (int j=0; j<nameSize; j++) {
      EEPROM.put(address, highscoreNames[i][j]);
      address += sizeof(char);
    }
  }
  
  for (int i=0; i<highscoreCount; i++) {
    EEPROM.put(address, highscorePoints[i]);
    address += sizeof(int);
  }
}

void saveSettings() {
  int address = settingsStartingAddress;

  for (int i=0; i<nameSize; i++) {
    EEPROM.put(address, currentName[i]);
    address += sizeof(char);
  }
  
  EEPROM.put(address, startDifficulty);
  address += sizeof(int);

  EEPROM.put(address, lcdBrightness);
  address += sizeof(int);

  EEPROM.put(address, matrixBrightness);
  address += sizeof(int);

  EEPROM.put(address, soundSetting);
  address += sizeof(int);
}

#endif