// Buzzer

#ifndef SNEK_BUZZER_H
#define SNEK_BUZZER_H

#include "Memory.h";

const int buzzer = 3,
          buzzerSound = 1000,
          buzzerTime = 500;

void buzzerSetup() {
  pinMode(buzzer, OUTPUT);
}

void playSong() {
  if (soundSetting == NO_SOUND) {
    noTone(buzzer);
  }
  else{
    tone(buzzer, buzzerSound, buzzerTime);
  }
}

#endif