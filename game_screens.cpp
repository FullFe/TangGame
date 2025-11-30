#include "game_screens.h"
#include "constants.h"

extern Arduboy2 arduboy;
extern int currentScreen;
extern int selectedLevel;
extern int selectedOption;
extern TangramPiece pieces[7];
extern int selectedPiece;
extern bool pieceGrabbed;
extern LevelState currentLevel;
extern Cursor cursor;
extern GameState gameState;

// ==================== ПРИВЕТСТВЕННОЕ МЕНЮ ====================
void drawMainMenu() {
  arduboy.setCursor(35, 8);
  arduboy.print("TANGRAM");
  arduboy.setCursor(20, 18);
  arduboy.print("CLASSIC PUZZLE");
  
  arduboy.drawLine(0, 30, 127, 30, WHITE);
  
  arduboy.setCursor(25, 33);
  if (selectedOption == 0) {
    arduboy.print("> PLAY GAME");
  } else {
    arduboy.print("  PLAY GAME");
  }
  
  arduboy.setCursor(25, 42);
  if (selectedOption == 1) {
    arduboy.print("> SANDBOX");
  } else {
    arduboy.print("  SANDBOX");
  }
}

void handleMainMenuInput() {
  if (arduboy.justPressed(DOWN_BUTTON)) {
    selectedOption = (selectedOption + 1) % 2;
  }
  if (arduboy.justPressed(UP_BUTTON)) {
    selectedOption = (selectedOption + 1) % 2;
  }
  if (arduboy.justPressed(A_BUTTON)) {
    if (selectedOption == 0) {
      currentScreen = LEVEL_SELECT_SCREEN;
    } else {
      currentScreen = SANDBOX_SCREEN;
    }
  }
}

// ==================== ВЫБОР УРОВНЯ ====================
void drawLevelSelection() {
  arduboy.setCursor(25, 2);
  arduboy.print("SELECT LEVEL");
  
  arduboy.drawLine(0, 12, 127, 12, WHITE);
  
  for (int i = 0; i < 8; i++) {
    int row = i / 4;
    int col = i % 4;
    int x = 5 + col * 32;
    int y = 18 + row * 20;
    
    if (i == selectedLevel) {
      arduboy.drawRect(x-2, y-2, 28, 14, WHITE);
    }
    
    arduboy.setCursor(x + 8, y);
    arduboy.print(i + 1);
  }
  
  arduboy.setCursor(15, 55);
  arduboy.print("A:Play  B:Back");
}

void handleLevelSelectionInput() {
  if (arduboy.justPressed(RIGHT_BUTTON)) {
    selectedLevel = (selectedLevel + 1) % 8;
  }
  if (arduboy.justPressed(LEFT_BUTTON)) {
    selectedLevel = (selectedLevel + 7) % 8;
  }
  if (arduboy.justPressed(DOWN_BUTTON)) {
    if (selectedLevel < 4) selectedLevel += 4;
  }
  if (arduboy.justPressed(UP_BUTTON)) {
    if (selectedLevel >= 4) selectedLevel -= 4;
  }
  if (arduboy.justPressed(A_BUTTON)) {
    currentScreen = GAME_SCREEN;
    loadLevel(selectedLevel);
  }
  if (arduboy.justPressed(B_BUTTON)) {
    currentScreen = MENU_SCREEN;
  }
}

void loadLevel(int level) {
  for (int i = 0; i < 7; i++) {
    pieces[i] = {10 + (i % 4) * 18, 45 + (i / 4) * 12, i, false, 0};
    currentLevel.availablePieces[i] = LEVEL_PIECES_COUNT[level][i];
  }
  gameState.selectedPieceType = 0;
  gameState.heldPieceIndex = -1;
  gameState.pieceGrabbed = false;
  currentLevel.cursor = {64, 37, false};
}

// ==================== ИГРОВОЙ ЭКРАН ====================
void drawGameScreen() {
  drawPieceInfo();
  arduboy.drawLine(0, 12, 127, 12, WHITE);
  drawGameField();
}

void drawGameField() {
  // Cилует уровня
  drawLevelSilhouette(selectedLevel);

  for (int i = 0; i < 7; i++) {
    if (pieces[i].placed) {
      drawTangramPiece(pieces[i].x, pieces[i].y, pieces[i].shape, pieces[i].rotation);
    }
  }
  
  if (gameState.pieceGrabbed) {
    drawTangramPiece(pieces[gameState.heldPieceIndex].x, pieces[gameState.heldPieceIndex].y, 
                     pieces[gameState.heldPieceIndex].shape, pieces[gameState.heldPieceIndex].rotation);
  }
  
  if (currentLevel.cursor.visible && !gameState.pieceGrabbed) {
    arduboy.drawRect(currentLevel.cursor.x, currentLevel.cursor.y, 2, 2, WHITE);
  }
}

void drawPieceInfo() {
  arduboy.setCursor(100, 2);
  arduboy.print("cnt:");
  arduboy.print(currentLevel.availablePieces[gameState.selectedPieceType]);
  
  arduboy.setCursor(50, 0);
  arduboy.print("sh:");
  drawSmallTangramPiece(70, 2, gameState.selectedPieceType, 0);
  
  arduboy.setCursor(5, 2);
  arduboy.print("lvl_");
  arduboy.print(selectedLevel + 1);
}

// Функция для проверки попадания точки в фигуру
bool isPointInPiece(int x, int y, TangramPiece piece) {
  int pieceW = getPieceWidth(piece.shape, piece.rotation);
  int pieceH = getPieceHeight(piece.shape, piece.rotation);
  
  // Проверяем попадание в прямоугольную область фигуры
  bool hit = (x >= piece.x && x <= piece.x + pieceW &&
              y >= piece.y && y <= piece.y + pieceH);
  
  return hit;
}

// Функция для обработки долгого нажатия с индикатором прогресса
bool handleLongPress(bool buttonPressed, unsigned long& startTime, int barX, int barY, int barWidth) {
  if (buttonPressed) {
    if (startTime == 0) {
      startTime = millis();
    }
    
    unsigned long elapsed = millis() - startTime;
    if (elapsed < 1000) {
      int progress = (elapsed * barWidth) / 1000;
      arduboy.drawRect(barX, barY, barWidth, 4, WHITE);
      arduboy.fillRect(barX, barY, progress, 4, WHITE);
      return false;
    } else {
      startTime = 0;
      return true;
    }
  } else {
    startTime = 0;
    return false;
  }
}

void handleGameInput() {
  static ButtonStates btnState = {0, 0, false, false, false, false, 0, 0, 0};

  if (arduboy.pressed(UP_BUTTON) && arduboy.pressed(DOWN_BUTTON)) {
    exitLevel();
    return;
  }
  
  handleButtonTransitions(btnState);
  
  if (!gameState.pieceGrabbed) {
    if (currentLevel.cursor.visible) {
      handleCursorMode(btnState);
    } else {
      handleNoPieceMode(btnState);
    }
  } else {
    handlePieceInHandMode(btnState);
  }
}

void handleButtonTransitions(ButtonStates& btnState) {
  if (arduboy.justPressed(A_BUTTON)) {
    btnState.aPressStartTime = millis();
    btnState.aWasPressed = true;
    btnState.aIsLongPress = false;
  }
  if (arduboy.justPressed(B_BUTTON)) {
    btnState.bPressStartTime = millis();
    btnState.bWasPressed = true;
    btnState.bIsLongPress = false;
  }
  
  if (!gameState.pieceGrabbed) {
    // Долгое нажатие A - только в обычном режиме (не в режиме курсора)
    if (!currentLevel.cursor.visible && btnState.aWasPressed && arduboy.pressed(A_BUTTON)) {
      unsigned long elapsed = millis() - btnState.aPressStartTime;
      
      if (elapsed < 500) {
        int progress = (elapsed * 20) / 500;
        arduboy.drawRect(50, 55, 20, 4, WHITE);
        arduboy.fillRect(50, 55, progress, 4, WHITE);
      } else if (!btnState.aIsLongPress) {
        btnState.aIsLongPress = true;
        toggleCursor();
      }
    }
    
    // Долгое нажатие B - в обычном режиме выход, в режиме курсора - скрыть курсор
    if (btnState.bWasPressed && arduboy.pressed(B_BUTTON)) {
      unsigned long elapsed = millis() - btnState.bPressStartTime;
      
      if (currentLevel.cursor.visible) {
        // В режиме курсора - скрыть курсор (500ms)
        if (elapsed < 500) {
          int progress = (elapsed * 20) / 500;
          arduboy.drawRect(80, 55, 20, 4, WHITE);
          arduboy.fillRect(80, 55, progress, 4, WHITE);
        } else if (!btnState.bIsLongPress) {
          btnState.bIsLongPress = true;
          currentLevel.cursor.visible = false; // Скрыть курсор
        }
      } else {
        // В обычном режиме - выход из уровня (1000ms)
        if (elapsed < 1000) {
          int progress = (elapsed * 20) / 1000;
          arduboy.drawRect(80, 55, 20, 4, WHITE);
          arduboy.fillRect(80, 55, progress, 4, WHITE);
        } else if (!btnState.bIsLongPress) {
          btnState.bIsLongPress = true;
          exitLevel();
        }
      }
    }
  }
}

void handleNoPieceMode(ButtonStates& btnState) {
  if (arduboy.justPressed(RIGHT_BUTTON)) {
    gameState.selectedPieceType = (gameState.selectedPieceType + 1) % 7;
  }
  if (arduboy.justPressed(LEFT_BUTTON)) {
    gameState.selectedPieceType = (gameState.selectedPieceType + 6) % 7;
  }
  
  if (arduboy.justReleased(A_BUTTON) && btnState.aWasPressed) {
    if (!btnState.aIsLongPress) {
      createNewPiece();
    }
    btnState.aWasPressed = false;
    btnState.aIsLongPress = false;
  }
  
  if (arduboy.justReleased(B_BUTTON) && btnState.bWasPressed) {
    btnState.bWasPressed = false;
    btnState.bIsLongPress = false;
  }
}

void handleCursorMode(ButtonStates& btnState) {
  if (arduboy.pressed(LEFT_BUTTON) && currentLevel.cursor.x > 10) {
    currentLevel.cursor.x--;
  }
  if (arduboy.pressed(RIGHT_BUTTON) && currentLevel.cursor.x < 118) {
    currentLevel.cursor.x++;
  }
  if (arduboy.pressed(UP_BUTTON) && currentLevel.cursor.y > 20) {
    currentLevel.cursor.y--;
  }
  if (arduboy.pressed(DOWN_BUTTON) && currentLevel.cursor.y < 55) {
    currentLevel.cursor.y++;
  }
  
  if (arduboy.justReleased(A_BUTTON) && btnState.aWasPressed) {
    if (!btnState.aIsLongPress) {
      bool hit = takePieceWithCursor();
      // ДЕТАЛЬНАЯ ОТЛАДКА
      arduboy.setCursor(0, 55);
      if (hit) {
        arduboy.print("HIT: true ");
      } else {
        arduboy.print("HIT: false");
        
        // Покажем координаты курсора и фигур для отладки
        arduboy.setCursor(0, 48);
        arduboy.print("C:");
        arduboy.print(currentLevel.cursor.x);
        arduboy.print(",");
        arduboy.print(currentLevel.cursor.y);
        
        // Покажем координаты первой фигуры
        arduboy.setCursor(40, 48);
        arduboy.print("P0:");
        arduboy.print(pieces[0].x);
        arduboy.print(",");
        arduboy.print(pieces[0].y);
        arduboy.print(" ");
        arduboy.print(getPieceWidth(pieces[0].shape, pieces[0].rotation));
        arduboy.print("x");
        arduboy.print(getPieceHeight(pieces[0].shape, pieces[0].rotation));
      }
    }
    btnState.aWasPressed = false;
    btnState.aIsLongPress = false;
  }
  
  if (arduboy.justReleased(B_BUTTON) && btnState.bWasPressed) {
    btnState.bWasPressed = false;
    btnState.bIsLongPress = false;
  }
}

void handlePieceInHandMode(ButtonStates& btnState) {
  const unsigned long ROTATION_DELAY = 300;
  
  if (arduboy.pressed(LEFT_BUTTON) && pieces[gameState.heldPieceIndex].x > 10) {
    pieces[gameState.heldPieceIndex].x--;
  }
  if (arduboy.pressed(RIGHT_BUTTON) && pieces[gameState.heldPieceIndex].x < 118 - getPieceWidth(pieces[gameState.heldPieceIndex].shape, pieces[gameState.heldPieceIndex].rotation)) {
    pieces[gameState.heldPieceIndex].x++;
  }
  if (arduboy.pressed(UP_BUTTON) && pieces[gameState.heldPieceIndex].y > 20) {
    pieces[gameState.heldPieceIndex].y--;
  }
  if (arduboy.pressed(DOWN_BUTTON) && pieces[gameState.heldPieceIndex].y < 55 - getPieceHeight(pieces[gameState.heldPieceIndex].shape, pieces[gameState.heldPieceIndex].rotation)) {
    pieces[gameState.heldPieceIndex].y++;
  }

  unsigned long currentTime = millis();
  if (currentTime - btnState.lastRotationTime > ROTATION_DELAY) {
    if (arduboy.justReleased(B_BUTTON) && btnState.bWasPressed) {
      if (millis() - btnState.bPressStartTime < 300) {
        rotatePiece(true);
        btnState.lastRotationTime = currentTime;
      }
      btnState.bWasPressed = false;
    }
    
    if (arduboy.justReleased(A_BUTTON) && btnState.aWasPressed) {
      if (millis() - btnState.aPressStartTime < 300) {
        rotatePiece(false);
        btnState.lastRotationTime = currentTime;
      }
      btnState.aWasPressed = false;
    }
  }

  if (handleLongPress(arduboy.pressed(A_BUTTON), btnState.placeStartTime, 50, 55, 20)) {
    placePiece();
    btnState.aWasPressed = false;
    btnState.aIsLongPress = false;
  }
  
  if (handleLongPress(arduboy.pressed(B_BUTTON), btnState.cancelStartTime, 80, 55, 20)) {
    cancelPiece();
    btnState.bWasPressed = false;
    btnState.bIsLongPress = false;
  }
}

bool takePieceWithCursor() {
  for (int i = 0; i < 7; i++) {
    if (!pieces[i].placed) {
      // Проверяем все 4 пикселя курсора (2x2)
      for (int cx = currentLevel.cursor.x; cx < currentLevel.cursor.x + 2; cx++) {
        for (int cy = currentLevel.cursor.y; cy < currentLevel.cursor.y + 2; cy++) {
          if (isPointInPiece(cx, cy, pieces[i])) {
            gameState.heldPieceIndex = i;
            gameState.pieceGrabbed = true;
            currentLevel.cursor.visible = false;
            return true; // Попадание в фигуру
          }
        }
      }
    }
  }
  return false; // Не попали ни в одну фигуру
}

void createNewPiece() {
  if (currentLevel.availablePieces[gameState.selectedPieceType] > 0) {
    for (int i = 0; i < 7; i++) {
      if (!pieces[i].placed) {
        pieces[i].shape = gameState.selectedPieceType;
        pieces[i].x = 64;
        pieces[i].y = 37;
        pieces[i].placed = false;
        pieces[i].rotation = 0;
        gameState.heldPieceIndex = i;
        gameState.pieceGrabbed = true;
        currentLevel.availablePieces[gameState.selectedPieceType]--;
        break;
      }
    }
  }
}

void rotatePiece(bool clockwise) {
  if (clockwise) {
    pieces[gameState.heldPieceIndex].rotation = (pieces[gameState.heldPieceIndex].rotation + 1) % 4;
  } else {
    pieces[gameState.heldPieceIndex].rotation = (pieces[gameState.heldPieceIndex].rotation + 3) % 4;
  }
}

void placePiece() {
  pieces[gameState.heldPieceIndex].placed = true;
  gameState.pieceGrabbed = false;
}

void cancelPiece() {
  int pieceType = pieces[gameState.heldPieceIndex].shape;
  pieces[gameState.heldPieceIndex].placed = false;
  gameState.pieceGrabbed = false;
  currentLevel.availablePieces[pieceType]++;
}

void toggleCursor() {
  currentLevel.cursor.visible = !currentLevel.cursor.visible;
  if (currentLevel.cursor.visible) {
    currentLevel.cursor.x = 64;
    currentLevel.cursor.y = 37;
  }
}

void exitLevel() {
  currentScreen = LEVEL_SELECT_SCREEN;
}