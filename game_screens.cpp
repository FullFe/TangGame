#include "game_screens.h"
#include "constants.h"

extern Arduboy2 arduboy;
extern int currentScreen;
extern int selectedLevel;
extern int selectedOption;
extern TangramPiece pieces[7];
extern int selectedPiece;
extern bool pieceGrabbed;

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
  }
  selectedPiece = 0;
  pieceGrabbed = false;
}

// ==================== ИГРОВОЙ ЭКРАН ====================
void drawGameScreen() {
  // Рисуем информацию сверху
  drawPieceInfo();
  
  // Разделительная линия под информацией
  arduboy.drawLine(0, 12, 127, 12, WHITE);
  
  // Игровое поле (занимает основную часть экрана)
  drawGameField();

  // Подсказки по управлению (справа внизу)
}

void drawGameField() {

  // Рисуем уже размещенные фигуры внутри границ
  for (int i = 0; i < 7; i++) {
    if (pieces[i].placed) {
      drawTangramPiece(pieces[i].x, pieces[i].y, pieces[i].shape, pieces[i].rotation);
    }
  }
  
  // Если фигура взята, рисуем ее на поле
  if (pieceGrabbed) {
    drawTangramPiece(pieces[selectedPiece].x, pieces[selectedPiece].y, selectedPiece, pieces[selectedPiece].rotation);
  }
}


void drawPieceInfo() {
  // Считаем количество неиспользованных фигур того же типа
  int sameTypeCount = 0;
  for (int i = 0; i < 7; i++) {
    if (pieces[i].shape == selectedPiece && !pieces[i].placed) {
      sameTypeCount++;
    }
  }
  
  arduboy.setCursor(100, 2);
  arduboy.print("cnt:");
  arduboy.print(sameTypeCount);
  
  arduboy.setCursor(50, 0);
  arduboy.print("sh:");
  drawTangramPiece(70, 2, selectedPiece, pieces[selectedPiece].rotation);
  //print   
  arduboy.setCursor(5, 2);
  arduboy.print("lvl_");
  arduboy.print(selectedLevel + 1);
}

void handleGameInput() {
  if (!pieceGrabbed) {
    if (arduboy.justPressed(RIGHT_BUTTON)) {
      selectedPiece = (selectedPiece + 1) % 7;
    }
    if (arduboy.justPressed(LEFT_BUTTON)) {
      selectedPiece = (selectedPiece + 6) % 7;
    }
    if (arduboy.justPressed(A_BUTTON)) {
      pieceGrabbed = true;
      // Фигура появляется в центре игрового поля
      pieces[selectedPiece].x = 64;
      pieces[selectedPiece].y = 37;
    }
  } else {
    // Режим перемещения фигуры в пределах игрового поля
    if (arduboy.pressed(LEFT_BUTTON) && pieces[selectedPiece].x > 10) {
      pieces[selectedPiece].x--;
    }
    if (arduboy.pressed(RIGHT_BUTTON) && pieces[selectedPiece].x < 118 - getPieceWidth(selectedPiece, 0)) {
      pieces[selectedPiece].x++;
    }
    if (arduboy.pressed(UP_BUTTON) && pieces[selectedPiece].y > 20) {
      pieces[selectedPiece].y--;
    }
    if (arduboy.pressed(DOWN_BUTTON) && pieces[selectedPiece].y < 55 - getPieceHeight(selectedPiece, 0)) {
      pieces[selectedPiece].y++;
    }
    if (arduboy.justPressed(A_BUTTON)) {
      // Вращение фигуры
      pieces[selectedPiece].rotation = (pieces[selectedPiece].rotation + 1) % 4;
    }
    if (arduboy.justPressed(B_BUTTON)) {
      // Отмена - возвращаем фигуру на исходную
      pieces[selectedPiece].x = 10 + (selectedPiece % 4) * 18;
      pieces[selectedPiece].y = 45 + (selectedPiece / 4) * 12;
      pieceGrabbed = false;
    }
  }
  
  if (arduboy.justPressed(B_BUTTON) && !pieceGrabbed) {
    currentScreen = LEVEL_SELECT_SCREEN;
  }
}