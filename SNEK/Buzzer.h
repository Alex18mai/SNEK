// Buzzer

#ifndef SNEK_BUZZER_H
#define SNEK_BUZZER_H

#include "Memory.h"

const int buzzer = 3,
          buzzerSound = 700,
          buzzerTime = 300;

void buzzerSetup() {
  pinMode(buzzer, OUTPUT);
}

void beep() {
  if (soundSetting == WITH_SOUND) {
    tone(buzzer, buzzerSound, buzzerTime);
  }
}

#endif