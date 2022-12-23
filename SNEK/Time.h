#ifndef SNEK_TIME_H // header guard
#define SNEK_TIME_H

/*
 * Time (Pause) Module
 *
 * The module that takes care of the pause logic. The time spent in pause should not affect the game.
 */

unsigned long timePaused,
              pauseStart;

void timeSetup() {
  timePaused = 0;
  pauseStart = 0;
}

// function that returns the current millis() without the time spent in the pause state
unsigned long millisWithoutPause() {
  return millis() - timePaused;
}

// function for pause start
void startPause() {
  pauseStart = millis();
}

// function for pause end
void endPause() {
  timePaused += millis() - pauseStart;
  pauseStart = 0;
}

#endif