#ifndef SNEK_GAME_H // header guard
#define SNEK_GAME_H

/*
 * Game Module
 *
 * Contains all the functions of the game:
 *  -> gameSetup() : sets a random seed
 *  -> gameInit() : called every time a game is started, just resets everything needed for the game
 *  -> displayGame() : main game function, uses the following functions:
 *      -> doGameMovement() : does the snake movement
 *      -> updateGameDirection(int joystickMovement) : updates the direction based on the joystick input
 *      -> changeGameLcd() : updates the lcd during the game
 *      -> generateFood() : generates a new food
 *  -> displayGameEnd() : called every time the game ends (displays info and updates highscores)
 */

#include "Matrix.h"
#include "Lcd.h"
#include "Buzzer.h"
#include "Time.h"

struct config {
  int moveInterval,
      scorePerFood;
  bool isReversed;
};

const config diffConfig[] = { { 270, 10, false },   // D0 - snek is happy and eats fruit
                              { 200, 20, false },   // D1 - snek is fast boy
                              { 270, 30, true },    // D2 - snek is slow but confused (changes direction when eating fruit)
                              { 200, 40, true } };  // D3 - snek is fast and confused (changes direction when eating fruit)

struct position {
  int x, y;
};

const position initialSnek[] = { { 0, 2 }, { 0, 1 }, { 0, 0 } };
position snek[matrixSize * matrixSize];

const int initialSnekLenght = 3,
          numberOfLifes = 1;

const String scoreText = "SCORE : ",
             congratulations = "CONGRATULATIONS!",
             reachedDif = "Reached diff ",
             newHighscoreText = "NEW HIGHSCORE!",
             space = " ",
             levelText = "LVL";

int snekX,
    snekY,
    snekMovement,
    score,
    difficulty,
    snekLength;

bool gameEndScreenChanged,
     initFood,
     changedLength;

unsigned long lastMoved,
              lastDiffChange,
              diffChangeInterval = 10000,
              endDelay = 2000;

void gameSetup() {
  randomSeed(analogRead(0));
}

void gameInit() {
  for (int i = 0; i < matrixSize; i++) {
    for (int j = 0; j < matrixSize; j++) {
      matrix[i][j] = 0;
    }
  }

  matrixChanged = true;
  snekMovement = RIGHT;
  score = 0;
  difficulty = startDifficulty;

  lastMoved = millisWithoutPause();
  lastDiffChange = millisWithoutPause();
  initFood = true;

  snekLength = initialSnekLenght;
  for (int i = 0; i < snekLength; i++) {
    snek[i] = initialSnek[i];
    matrix[snek[i].x][snek[i].y] = 1;
  }
  snekX = snek[0].x;
  snekY = snek[0].y;

  changedLength = false;
}

void doGameMovement() {
  switch (snekMovement) {
    case UP:
      snekX--;
      break;

    case DOWN:
      snekX++;
      break;

    case LEFT:
      snekY--;
      break;

    case RIGHT:
      snekY++;
      break;

    default:
      break;
  }

  if (snekX >= 0 && snekX < matrixSize && snekY >= 0 && snekY < matrixSize) {
    matrixChanged = true;
    if (!changedLength) {
      matrix[snek[snekLength - 1].x][snek[snekLength - 1].y] = 0;
    }
    changedLength = false;
    for (int i = snekLength - 1; i >= 1; i--) {
      snek[i] = snek[i - 1];
    }
    snek[0] = { snekX, snekY };
    matrix[snekX][snekY] = 1;
  }
}

void updateGameDirection(int joystickMovement) {
  if (joystickMovement != NONE) {
    if ((snekMovement == UP || snekMovement == DOWN) && (joystickMovement == LEFT || joystickMovement == RIGHT)) {
      snekMovement = joystickMovement;
    } else if ((snekMovement == LEFT || snekMovement == RIGHT) && (joystickMovement == UP || joystickMovement == DOWN)) {
      snekMovement = joystickMovement;
    }
  }
}

void changeGameLcd() {
  lcd.clear();
  lcd.setCursor(FIRST_ROW);
  
  lcd.write(LCD_SMILE);
  lcd.print(space);
  
  for (int i = 0; i < nameSize; i++) {
    lcd.print(currentName[i]);
  }

  lcd.print(space + space);
  lcd.write(LCD_HEART);
  lcd.print(numberOfLifes);
  
  lcd.print(space + space + levelText + space); 
  lcd.print(difficulty);

  lcd.setCursor(SECOND_ROW);
  lcd.print(space + space + space + scoreText);
  lcd.print(score);

  if (pauseStart) {
    lcd.setCursor(PAUSE_POSITION);
    lcd.write(LCD_PAUSE);
  }
}

void generateFood() {
  static unsigned long lastBlink = 0;
  static const int blinkDelay = 100;
  static int state = HIGH;
  static int currentFoodPosX, currentFoodPosY;

  if (initFood == true || (snekX == currentFoodPosX && snekY == currentFoodPosY)) {
    if (!initFood) {
      score += diffConfig[difficulty].scorePerFood;
      snekLength++;
      changedLength = true;
      if (diffConfig[difficulty].isReversed) {
        // reverse snek
        for (int i = 0; i <= (snekLength - 2) / 2; i++) {
          position aux = snek[i];
          snek[i] = snek[snekLength - 2 - i];
          snek[snekLength - 2 - i] = aux;
        }
        if (snek[0].x == snek[1].x) {
          if (snek[0].y < snek[1].y) {
            snekMovement = LEFT;
          } else {
            snekMovement = RIGHT;
          }
        } else {
          if (snek[0].x < snek[1].x) {
            snekMovement = UP;
          } else {
            snekMovement = DOWN;
          }
        }
        snekX = snek[0].x;
        snekY = snek[0].y;
      }
      beep();
    }
    initFood = false;
    changeGameLcd();

    int newFoodPosX, newFoodPosY;
    bool badPosition = true;

    while (badPosition) {
      badPosition = false;
      newFoodPosX = random(matrixSize - 2) + 1;
      newFoodPosY = random(matrixSize - 2) + 1;
      for (int i = 0; i < snekLength; i++) {
        if (snek[i].x == newFoodPosX && snek[i].y == newFoodPosY) {
          badPosition = true;
          break;
        }
      }
    }

    matrix[newFoodPosX][newFoodPosY] = state;

    currentFoodPosX = newFoodPosX;
    currentFoodPosY = newFoodPosY;

    matrixChanged = true;
  }

  if (millisWithoutPause() - lastBlink > blinkDelay) {
    state = !state;
    lastBlink = millisWithoutPause();
    matrix[currentFoodPosX][currentFoodPosY] = state;

    matrixChanged = true;
  }
}

void displayGame() {
  // change difficulty
  if (millisWithoutPause() - lastDiffChange > diffChangeInterval) {
    levelUpSound();
    lastDiffChange = millisWithoutPause();
    difficulty = min(difficulty + 1, MAX_DIFFICULTY);
    changeGameLcd();
  }

  // game logic
  if (millisWithoutPause() - lastMoved > diffConfig[difficulty].moveInterval) {
    generateFood();
    doGameMovement();
    lastMoved = millisWithoutPause();
  }

  // martix display logic
  if (matrixChanged == true) {
    updateMatrix();
    matrixChanged = false;
  }
}

void displayGameEnd() {
  if (gameEndScreenChanged) {
    gameEndScreenChanged = false;
    displayMatrixImage(matrixImageGameEnd);

    lcd.clear();
    lcd.setCursor(FIRST_ROW);
    lcd.print(congratulations);

    lcd.setCursor(SECOND_ROW);
    lcd.print(reachedDif);
    lcd.print(difficulty);
    lcd.print("!");

    delay(endDelay);

    lcd.clear();
    lcd.setCursor(FIRST_ROW);
    lcd.print(scoreText);
    lcd.print(score);
    if (score > highscorePoints[0]) {
      lcd.setCursor(SECOND_ROW);
      lcd.print(newHighscoreText);
    }

    for (int i = 0; i < highscoreCount; i++) {
      if (score > highscorePoints[i]) {
        for (int j = highscoreCount - 1; j >= i + 1; j--) {
          highscorePoints[j] = highscorePoints[j - 1];
          for (int k = 0; k < nameSize; k++) {
            highscoreNames[j][k] = highscoreNames[j - 1][k];
          }
        }
        highscorePoints[i] = score;
        for (int k = 0; k < nameSize; k++) {
          highscoreNames[i][k] = currentName[k];
        }
        break;
      }
    }

    saveHighscores();
  }
}

#endif