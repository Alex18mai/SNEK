#ifndef SNEK_JOYSTICK_H // header guard
#define SNEK_JOYSTICK_H

/*
 * Joystick Module
 *
 * Contains the functions for setting up the joystick and checking if the switch is pressed or if the joystick is moved.
 */

// joystick movement
#define NONE 0
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

// switch clicks
#define NO_BUTTON_CLICK 0
#define BUTTON_CLICK 1

// declare all the joystick pins
const int pinSW = 2,  // digital pin connected to switch output
          pinX = A0,  // A0 - analog pin connected to X output
          pinY = A1;  // A1 - analog pin connected to Y output

// constants for the minimum and maximum thresholds for the joystick + median value
const int minThreshold = 300,
          maxThreshold = 700,
          medianValue = 516;

// delay for debounce
const unsigned long debounceDelay = 50;

// setup
void joystickSetup() {
  // initialize the switch pin
  pinMode(pinSW, INPUT_PULLUP);
}

// function that checks if the switch is pressed using debounce
int checkSwitchAction() {
  static int lastSwitchValue = HIGH, switchState = HIGH;
  static unsigned long lastSwitchDebounceTime = 0;

  int switchValue = digitalRead(pinSW);

  if (switchValue != lastSwitchValue) {
    lastSwitchDebounceTime = millis();
  }
  lastSwitchValue = switchValue;

  if (millis() - lastSwitchDebounceTime > debounceDelay) {
    if (switchValue != switchState) {
      switchState = switchValue;

      if (switchState == HIGH) {
        return BUTTON_CLICK;
      }
    }
  }

  return NO_BUTTON_CLICK;
}

// function that checks if the joystick was moved using debounce and returns the corresponding value (NONE, UP, DOWN, LEFT, RIGHT)
int checkJoystickMovement() {
  static int lastXValue = medianValue, lastYValue = medianValue;
  static int joystickDebounceState = NONE;
  static unsigned long lastJoystickDebounceTime = 0;
  static unsigned long debounceDelayJoystick = 15;

  int xValue = analogRead(pinX);
  int yValue = analogRead(pinY);
  // Serial.println(xValue + semicolon + yValue);

  if (millis() - lastJoystickDebounceTime > debounceDelayJoystick && ((xValue < minThreshold || xValue > maxThreshold) || (yValue < minThreshold || yValue > maxThreshold))) {
    if ((lastXValue >= minThreshold && lastXValue <= maxThreshold) && (lastYValue >= minThreshold && lastYValue <= maxThreshold)) {
      lastJoystickDebounceTime = millis();
      joystickDebounceState = NONE;
    }
  }
  lastXValue = xValue;
  lastYValue = yValue;

  if (joystickDebounceState == NONE) {
    if (abs(xValue - medianValue) > abs(yValue - medianValue)) {  // the X coordinate has a bigger change
      if (xValue < minThreshold) {
        joystickDebounceState = UP;
        return UP;
      }
      if (xValue > maxThreshold) {
        joystickDebounceState = DOWN;
        return DOWN;
      }
    } else {  // the Y coordinate has a bigger change
      if (yValue < minThreshold) {
        joystickDebounceState = RIGHT;
        return RIGHT;
      }
      if (yValue > maxThreshold) {
        joystickDebounceState = LEFT;
        return LEFT;
      }
    }
  }

  return NONE;
}

#endif