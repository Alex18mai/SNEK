// Time (for pause)

#ifndef SNEK_TIME_H
#define SNEK_TIME_H

unsigned long timePaused,
              pauseStart;

void timeSetup() {
  timePaused = 0;
  pauseStart = 0;
}

unsigned long myMillis() {
  return millis() - timePaused;
}

void startPause() {
  pauseStart = millis();
}

void endPause() {
  timePaused += millis() - pauseStart;
  pauseStart = 0;
}

#endif