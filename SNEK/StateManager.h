// State Manager

#ifndef SNEK_STATE_MANAGER_H
#define SNEK_STATE_MANAGER_H

#include "Menu.h"
#include "Memory.h"
#include "Joystick.h"
#include "Game.h"

volatile int currentState;

void stateSetup() {
  currentState = STATE_GREETINGS;
}

void returnToMenu(int joystickMovement) {
  if (joystickMovement == LEFT) {
    currentState = STATE_MENU;
    menuChanged = true; 
  } 
}

void returnToSettings(int joystickMovement) {
  if (joystickMovement == LEFT) {
    currentState = STATE_MENU_SETTINGS;
    menuChanged = true; 
  } 
}

void scrollItems(int joystickMovement, volatile int &counter, int minPos, int maxPos) {
  if (joystickMovement == UP && counter > minPos) {
    counter --;        
    menuChanged = true;     
  }               
  if (joystickMovement == DOWN && counter < maxPos) {
    counter ++;         
    menuChanged = true;    
  }  
}

void manageCurrentState() {
  int joystickMovement = checkJoystickMovement();
  int switchAction = checkSwitchAction();

  switch (currentState) {
    case STATE_GREETINGS: 
      if (millis() - greetingsStart > greetingsTime) {
        currentState = STATE_MENU; 
        currentItem = 0;
        menuChanged = true;   
      }               
      break;

    case STATE_MENU:
      scrollItems(joystickMovement, currentItem, 0, menuItemCount - 1);
      if (switchAction == BUTTON_CLICK) {
        currentState = menuItemState[currentItem];
        menuChanged = true;
        
        if (currentState == STATE_GAME) {
          gameInit();
        }
        else{
          currentHighscore = 0;
          currentAbout = 0;
          currentHowToPlay = 0;  
          currentSettings = 0;
        }
      }      
      break;

    case STATE_MENU_HIGHSCORE:    
      scrollItems(joystickMovement, currentHighscore, 0, highscoreCount - 1);
      returnToMenu(joystickMovement);  
      break;
      
    case STATE_MENU_SETTINGS:  
      scrollItems(joystickMovement, currentSettings, 0, settingsItemCount - 1);
      returnToMenu(joystickMovement);   
      if (switchAction == BUTTON_CLICK) {
        if (settingsItemState[currentSettings] == STATE_SETTINGS_RESET_HIGHSCORE) {
          initHighscores();
          readHighscores();
        }
        else {
          currentState = settingsItemState[currentSettings];
          menuChanged = true;
        }
      }                            
      break;
    
    case STATE_MENU_ABOUT:    
      scrollItems(joystickMovement, currentAbout, 0, aboutTextCount - 1);   
      returnToMenu(joystickMovement);                 
      break;
    
    case STATE_MENU_HOW_TO_PLAY: 
      scrollItems(joystickMovement, currentHowToPlay, 0, howToPlayTextCount - 1);
      returnToMenu(joystickMovement);               
      break;
    
    case STATE_GAME:   
      updateGamePosition(joystickMovement);   
      if (!(snekX >= 0 && snekX < matrixSize && snekY >= 0 && snekY < matrixSize)) {
        currentState = STATE_GAME_END;    
        gameEndScreenChanged = true;
        if (currentState == STATE_SETTINGS_CHANGE_NAME) {
          currentNameLetter = 0;   
          lockedNameLetter = false;       
        }
      }            
      break;

    case STATE_GAME_END:     
      if (switchAction == BUTTON_CLICK) {
        currentState = STATE_MENU;        
      }           
      break;

    case STATE_SETTINGS_CHANGE_NAME:
      if (!lockedNameLetter) {
        if (currentNameLetter == 0) {
          returnToSettings(joystickMovement);
        } 
        if (joystickMovement == LEFT && currentNameLetter > 0) {
          currentNameLetter --;        
          menuChanged = true;     
        }               
        if (joystickMovement == RIGHT && currentNameLetter < nameSize - 1) {
          currentNameLetter ++;         
          menuChanged = true;    
        }   
        if (switchAction == BUTTON_CLICK) {
          lockedNameLetter = true;
          menuChanged = true;
        }  
      }
      else {
        if (joystickMovement == UP && currentName[currentNameLetter] > 'A') {
          currentName[currentNameLetter] --;        
          menuChanged = true;     
        }               
        if (joystickMovement == DOWN && currentName[currentNameLetter] < 'Z') {
          currentName[currentNameLetter] ++;         
          menuChanged = true;    
        }  
        if (switchAction == BUTTON_CLICK) {
          lockedNameLetter = false;
          menuChanged = true;
        } 
      }
          
      break;  

    case STATE_SETTINGS_DIFFICULTY:
      scrollItems(joystickMovement, startDifficulty, MIN_DIFFICULTY, MAX_DIFFICULTY);
      returnToSettings(joystickMovement);
      break;  

    case STATE_SETTINGS_LCD_BRIGHT:
      scrollItems(joystickMovement, lcdBrightness, MIN_LCD_BRIGHT, MAX_LCD_BRIGHT);
      returnToSettings(joystickMovement);
      break;  

    case STATE_SETTINGS_MATRIX_BRIGHT:
      scrollItems(joystickMovement, matrixBrightness, MIN_MATRIX_BRIGHT, MAX_MATRIX_BRIGHT);
      returnToSettings(joystickMovement);
      break;  

    case STATE_SETTINGS_SOUND:
      scrollItems(joystickMovement, soundSetting, NO_SOUND, WITH_SOUND);
      returnToSettings(joystickMovement);
      break; 

    default:
      break;
  }         
}

void executeCurrentState() {
switch (currentState) {
    case STATE_GREETINGS:    
      displayGreetings();            
      break;

    case STATE_MENU:  
      displayMenu();              
      break;

    case STATE_MENU_HIGHSCORE:    
      displayHighscore();            
      break;
      
    case STATE_MENU_SETTINGS: 
      displaySettings();               
      break;
    
    case STATE_MENU_ABOUT:                
      displayAbout();
      break;
    
    case STATE_MENU_HOW_TO_PLAY:                
      displayHowToPlay();
      break;
    
    case STATE_GAME: 
      displayGame();               
      break;

    case STATE_GAME_END: 
      displayGameEnd();               
      break;
    
    case STATE_SETTINGS_CHANGE_NAME:
      displaySettingsChangeName();
      break;  

    case STATE_SETTINGS_DIFFICULTY:
      displaySettingsDifficulty();
      break;  

    case STATE_SETTINGS_LCD_BRIGHT:
      displaySettingsLcdBright();
      break;  

    case STATE_SETTINGS_MATRIX_BRIGHT:
      displaySettingsMatrixBright();
      break;  

    case STATE_SETTINGS_SOUND:
      displaySettingsSound();
      break;  
    
    default:
      break;
  }         
}

#endif