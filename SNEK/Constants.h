// Constants

#ifndef SNEK_CONSTANTS_H
#define SNEK_CONSTANTS_H

/* ---------- states ---------- */

#define STATE_GREETINGS 0

#define STATE_MENU 1
#define STATE_MENU_HIGHSCORE 2
#define STATE_MENU_SETTINGS 3
#define STATE_MENU_ABOUT 4
#define STATE_MENU_HOW_TO_PLAY 5

#define STATE_GAME 6
#define STATE_GAME_END 7

#define STATE_SETTINGS_CHANGE_NAME 8
#define STATE_SETTINGS_DIFFICULTY 9
#define STATE_SETTINGS_LCD_BRIGHT 10
#define STATE_SETTINGS_MATRIX_BRIGHT 11
#define STATE_SETTINGS_SOUND 12
#define STATE_SETTINGS_RESET_HIGHSCORE 13

/* ---------- end states ---------- */

/* ---------- bounds ---------- */

#define MIN_DIFFICULTY 0
#define MAX_DIFFICULTY 3

#define MIN_LCD_BRIGHT 1
#define MAX_LCD_BRIGHT 10
#define LCD_BRIGHT_FACTOR 25

#define MIN_MATRIX_BRIGHT 1
#define MAX_MATRIX_BRIGHT 15

#define NO_SOUND 0
#define WITH_SOUND 1

/* ---------- end bounds ---------- */

/* ---------- Serial ---------- */

#define SERIAL_DATA_RATE 9600

/* ---------- end Serial ---------- */

#endif