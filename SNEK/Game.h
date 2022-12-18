// Game

#ifndef SNEK_GAME_H
#define SNEK_GAME_H

#include "Matrix.h"
#include "Lcd.h"

const int moveInterval = 100,
          scorePerFood = 10;

const String difficultyText = "     Diff : ",
             scoreText = "Score : ",
             congratulations = "CONGRATULATIONS!",
             reachedDif = "Reached diff ",
             newHighscoreText = "NEW HIGHSCORE!";

int snekX, 
    snekY,
    snekMovement,
    score,
    difficulty;

bool gameEndScreenChanged,
     initFood;

unsigned long lastMoved,
              lastDiffChange,
              diffChangeInterval = 10000,
              endDelay = 2000;

void gameSetup() {
  randomSeed(analogRead(0));
}

void gameInit() {
  for (int i=0; i<matrixSize; i++) {
    for (int j=0; j<matrixSize; j++) {
      matrix[i][j] = 0;
    }
  }

  matrixChanged = true;
  snekX = 0;
  snekY = 0;
  snekMovement = RIGHT;
  score = 0;
  difficulty = startDifficulty;
  lastMoved = millis();
  lastDiffChange = millis();
  matrix[snekX][snekY] = 1;
  initFood = true;
}

void doGameMovement() {
  int lastSnekX = snekX;
  int lastSnekY = snekY;

  switch (snekMovement) {
    case UP: 
      snekX --;  
      break;

    case DOWN:
      snekX ++;      
      break;

    case LEFT:
      snekY --;
      break;
    
    case RIGHT:
      snekY ++;
      break;
    
    default:
      break;
  }

  if (snekX >= 0 && snekX < matrixSize && snekY >= 0 && snekY < matrixSize) {
    matrixChanged = true;
    matrix[lastSnekX][lastSnekY] = 0;
    matrix[snekX][snekY] = 1;    
  }  
}

void updateGamePosition(int joystickMovement) {
  if (joystickMovement != NONE) {
    if ((snekMovement == UP || snekMovement == DOWN) && (joystickMovement == LEFT || joystickMovement == RIGHT)) {
      snekMovement = joystickMovement;    
    }
    else if ((snekMovement == LEFT || snekMovement == RIGHT) && (joystickMovement == UP || joystickMovement == DOWN)) {
      snekMovement = joystickMovement;    
    }
  } 
}

void changeGameLcd() {
  lcd.clear();
  lcd.setCursor(FIRST_ROW);
  for (int i=0; i<nameSize; i++) {
    lcd.print(currentName[i]);
  }

  lcd.print(difficultyText);
  lcd.print(difficulty);
  
  lcd.setCursor(SECOND_ROW);
  lcd.print(scoreText);
  lcd.print(score);  
}

void generateFood() {
  static unsigned long lastBlink = 0;
  static const int blinkDelay = 200;
  static int state = HIGH;
  static int currentFoodPosX, currentFoodPosY;

  if (initFood == true || (snekX == currentFoodPosX && snekY == currentFoodPosY)) {
    if (!initFood) {
      score += scorePerFood * difficulty;
    }    
    initFood = false;
    changeGameLcd();

    int newFoodPosX = random(matrixSize);
    int newFoodPosY = random(matrixSize);

    matrix[newFoodPosX][newFoodPosY] = state;

    currentFoodPosX = newFoodPosX;
    currentFoodPosY = newFoodPosY;

    matrixChanged = true;
  }

  if (millis() - lastBlink > blinkDelay) {
    state = !state;
    lastBlink = millis();
    matrix[currentFoodPosX][currentFoodPosY] = state;

    matrixChanged = true;
  } 
}

void displayGame() {
  if (millis() - lastDiffChange > diffChangeInterval) {
    lastDiffChange = millis();
    difficulty = min(difficulty + 1, MAX_DIFFICULTY);
  }
  if (millis() - lastMoved > moveInterval * (MAX_DIFFICULTY - difficulty + 1)) {
    // game logic
    doGameMovement();        
    lastMoved = millis();
  }
  generateFood();
  if (matrixChanged == true) {
    // matrix display logic
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

    for (int i=0; i<highscoreCount; i++) {
      if (score > highscorePoints[i]) {
        for (int j=highscoreCount-1; j>=i+1; j--) {
          highscorePoints[j] = highscorePoints[j-1];
          for (int k=0; k<nameSize; k++) {
            highscoreNames[j][k] = highscoreNames[j-1][k];     
          }
        }
        highscorePoints[i] = score;
        for (int k=0; k<nameSize; k++) {
          highscoreNames[i][k] = currentName[k];     
        }
        break;        
      }
    } 

    saveHighscores();   
  }
}

#endif