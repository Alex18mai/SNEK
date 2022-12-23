#ifndef SNEK_LCD_H // header guard
#define SNEK_LCD_H

/*
 * Lcd Module
 *
 * Contains the lcd, the setup and the custom chars.
 */

#include <LiquidCrystal.h>

#define FIRST_ROW 0, 0
#define SECOND_ROW 0, 1

#define LCD_ARROW_UP int(0)
#define LCD_ARROW_DOWN int(1)
#define LCD_PAUSE int(2)
#define LCD_SMILE int(3)
#define LCD_HEART int(4)

#define ARROW_UP_POSITION 15, 0
#define ARROW_DOWN_POSITION 15, 1

#define SCORE_POSITION 5, 1

#define PAUSE_POSITION 15, 1

const byte rs = 9,
           en = 8,
           d4 = 7,
           d5 = 13,
           d6 = 5,
           d7 = 4,
           lcdBacklight = 6;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte lcdMaskArrowUp[] = {
  B00000,
  B00100,
  B01110,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000
};

byte lcdMaskArrowDown[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B01110,
  B00100,
  B00000
};

byte lcdPause[] = {
  B00000,
  B11011,
  B11011,
  B11011,
  B11011,
  B11011,
  B11011,
  B00000
};

byte lcdSmile[] = {
  B00000,
  B01010,
  B01010,
  B00000,
  B10001,
  B01110,
  B00000,
  B00000
};

byte lcdHeart[] = {
  B00000,
  B01010,
  B10101,
  B10001,
  B01010,
  B00100,
  B00000,
  B00000
};

void lcdSetup() {
  lcd.begin(16, 2);
  lcd.clear();
  analogWrite(lcdBacklight, lcdBrightness * LCD_BRIGHT_FACTOR);

  lcd.createChar(LCD_ARROW_UP, lcdMaskArrowUp);
  lcd.createChar(LCD_ARROW_DOWN, lcdMaskArrowDown);
  lcd.createChar(LCD_PAUSE, lcdPause);
  lcd.createChar(LCD_SMILE, lcdSmile);
  lcd.createChar(LCD_HEART, lcdHeart);
}

#endif