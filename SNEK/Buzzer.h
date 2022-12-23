/*
 * Buzzer Module
 *
 * Contains the setup and 3 functions for 3 different sounds used in the game and menu.
 */

#ifndef SNEK_BUZZER_H // header guard
#define SNEK_BUZZER_H

#include "Memory.h"

const int buzzer = 3;
          

void buzzerSetup() {
  pinMode(buzzer, OUTPUT);
}

void beep() {
  static const int buzzerSound = 500,
                   buzzerTime = 200;
  if (soundSetting == WITH_SOUND) {
    tone(buzzer, buzzerSound, buzzerTime);
  }
}

void dyingSound() {
  static const int buzzerSound = 200,
                   buzzerTime = 1000;
  if (soundSetting == WITH_SOUND) {
    tone(buzzer, buzzerSound, buzzerTime);
  }
}

void levelUpSound() {
  static const int buzzerSound = 1000,
                   buzzerTime = 700;
  if (soundSetting == WITH_SOUND) {
    tone(buzzer, buzzerSound, buzzerTime);
  }
}

#endif