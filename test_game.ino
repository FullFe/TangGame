#include <Arduboy2.h>
#include "constants.h"
#include "game_screens.h"
#include "tangram_pieces.h"
#include "levels.h"

Arduboy2 arduboy;

int currentScreen = MENU_SCREEN;
int selectedLevel = 0;
int selectedOption = 0;
TangramPiece pieces[7];
int selectedPiece = 0;
bool pieceGrabbed = false;
LevelState currentLevel;
GameState gameState;

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(30);
  initializeGame();
}

void loop() {
  if (!arduboy.nextFrame()) return;
  arduboy.pollButtons();
  arduboy.clear();
  
  switch (currentScreen) {
    case MENU_SCREEN:
      drawMainMenu();
      handleMainMenuInput();
      break;
      
    case LEVEL_SELECT_SCREEN:
      drawLevelSelection();
      handleLevelSelectionInput();
      break;
      
    case GAME_SCREEN:
      drawGameScreen();
      handleGameInput();
      break;
    case INSTRUCTION_SCREEN:  
      drawInstructionScreen();
      handleInstructionInput();
      break;
      
  }
  
  arduboy.display();
}

void initializeGame() {
  for (int i = 0; i < 7; i++) {
    pieces[i] = {10 + (i % 4) * 18, 45 + (i / 4) * 12, i, false, 0};
  }
}