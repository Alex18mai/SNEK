/*
 * The main .ino file
 *
 * Calls all the setup functions for the modules and manages and executes the current state in a loop.
 */

#include "Constants.h"
#include "Menu.h"
#include "Joystick.h"
#include "Matrix.h"
#include "Lcd.h"
#include "Memory.h"
#include "Game.h"
#include "StateManager.h"
#include "Buzzer.h"
#include "Time.h"

void setup() {
  memorySetup();

  menuSetup();
  joystickSetup();
  matrixSetup();
  lcdSetup();
  gameSetup();
  stateSetup();
  buzzerSetup();
  timeSetup();
  
  Serial.begin(SERIAL_DATA_RATE);
}

void loop() {
  manageCurrentState();
  executeCurrentState();
}