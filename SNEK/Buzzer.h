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

void playSong() {
  if (soundSetting == NO_SOUND) {
    //noTone(buzzer);
  } else {
    //tone(buzzer, buzzerSound, buzzerTime);
  }
}

void beep() {
  if (soundSetting == WITH_SOUND) {
    tone(buzzer, buzzerSound, buzzerTime);
  }
}

#endif