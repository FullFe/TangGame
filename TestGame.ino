#include <Arduboy2.h>
Arduboy2 arduboy;

// Состояния игры
int currentScreen = 0; // 0 - меню, 1 - выбор уровня, 2 - игра, 3 - песочница
int selectedLevel = 0;
int selectedOption = 0;

// Фигуры танграма (7 классических фигур)
struct TangramPiece {
  int x, y;
  int shape; // 0-6 для разных фигур
  bool placed;
  int rotation; // 0-3 для вращения
};

TangramPiece pieces[7];
int selectedPiece = 0;
bool pieceGrabbed = false;

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
    case 0: // Приветственное меню
      drawMainMenu();
      handleMainMenuInput();
      break;
      
    case 1: // Выбор уровня
      drawLevelSelection();
      handleLevelSelectionInput();
      break;
      
    case 2: // Игровой экран
      drawGameScreen();
      handleGameInput();
      break;
      
    case 3: // Песочница
      drawSandboxScreen();
      handleSandboxInput();
      break;
  }
  
  arduboy.display();
}

void initializeGame() {
  // Инициализация фигур танграма
  for (int i = 0; i < 7; i++) {
    pieces[i] = {10 + (i % 4) * 18, 45 + (i / 4) * 12, i, false, 0};
  }
}

// ==================== ПРИВЕТСТВЕННОЕ МЕНЮ ====================
void drawMainMenu() {
  // Заголовок
  arduboy.setCursor(35, 8);
  arduboy.print("TANGRAM");
  arduboy.setCursor(20, 18);
  arduboy.print("CLASSIC PUZZLE");
  
  // Разделительная линия
  arduboy.drawLine(0, 30, 127, 30, WHITE);
  
  // Опции меню
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
      currentScreen = 1; // Выбор уровня
    } else {
      currentScreen = 3; // Песочница
    }
  }
}

// ==================== ВЫБОР УРОВНЯ ====================
void drawLevelSelection() {
  arduboy.setCursor(25, 2);
  arduboy.print("SELECT LEVEL");
  
  arduboy.drawLine(0, 12, 127, 12, WHITE);
  
  // Отображаем уровни 1-8 в сетке 4x2
  for (int i = 0; i < 8; i++) {
    int row = i / 4;
    int col = i % 4;
    int x = 5 + col * 32;
    int y = 18 + row * 20;
    
    // Рамка выбранного уровня
    if (i == selectedLevel) {
      arduboy.drawRect(x-2, y-2, 28, 14, WHITE);
    }
    
    // Номер уровня
    arduboy.setCursor(x + 8, y);
    arduboy.print(i + 1);
  }
  
  // Инструкция
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
    if (selectedLevel < 4) {
      selectedLevel += 4;
    }
  }
  if (arduboy.justPressed(UP_BUTTON)) {
    if (selectedLevel >= 4) {
      selectedLevel -= 4;
    }
  }
  if (arduboy.justPressed(A_BUTTON)) {
    currentScreen = 2; // Начать игру
    loadLevel(selectedLevel);
  }
  if (arduboy.justPressed(B_BUTTON)) {
    currentScreen = 0; // Вернуться в меню
  }
}

void loadLevel(int level) {
  // Сброс всех фигур
  for (int i = 0; i < 7; i++) {
    pieces[i] = {10 + (i % 4) * 18, 45 + (i / 4) * 12, i, false, 0};
  }
  selectedPiece = 0;
  pieceGrabbed = false;
}

// ==================== ИГРОВОЙ ЭКРАН ====================
void drawGameScreen() {
  // Разделительные линии
  arduboy.drawLine(85, 0, 85, 64);   // Вертикальная - разделяет поле и цель
  arduboy.drawLine(0, 45, 85, 45);   // Горизонтальная - разделяет поле и текущую фигуру
  
  // Область цели (справа)
  drawTargetArea();
  
  // Игровое поле (слева сверху)
  drawGameField();
  
  // Текущая фигура (слева снизу)
  drawCurrentPieceArea();
  
  // Подсказки по управлению (справа снизу)
  drawControlsHelp();
}

void drawTargetArea() {
  // Заголовок цели
  arduboy.setCursor(90, 2);
  arduboy.print("TARGET");
  
  // Целевая фигура
  drawTargetShape(105, 25);
}

void drawGameField() {
  // Рисуем поле для сборки (такой же размер как цель)
  arduboy.drawRect(15, 10, 55, 30, WHITE);
  
  // Рисуем уже размещенные фигуры
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

void drawCurrentPieceArea() {
  // Фон области текущей фигуры
  arduboy.drawRect(0, 45, 85, 19, WHITE);
  
  // Номер уровня и выбранная фигура
  arduboy.setCursor(2, 47);
  arduboy.print("Lvl_");
  arduboy.print(selectedLevel + 1);
  
  arduboy.setCursor(40, 47);
  arduboy.print("Cur:");
  
  // Рисуем превью выбранной фигуры снизу
  if (!pieceGrabbed) {
    drawTangramPiece(62, 47, selectedPiece, pieces[selectedPiece].rotation);
  }
}

void drawControlsHelp() {
  // Компактное отображение управления
  arduboy.setCursor(88, 48);
  arduboy.print("CONTROLS:");
  
  // Динамические подсказки в зависимости от состояния
  if (!pieceGrabbed) {
    arduboy.setCursor(90, 56);
    arduboy.print("A:Grab B:Back");
    arduboy.setCursor(90, 48);
    arduboy.print("L/R:Select");
  } else {
    arduboy.setCursor(90, 56);
    arduboy.print("A:Rot B:Cancel");
    arduboy.setCursor(90, 48);
    arduboy.print("Arrows:Move");
  }
}

void drawTargetShape(int x, int y) {
  // Рисуем контур целевой фигуры для текущего уровня
  switch(selectedLevel % 4) {
    case 0: // Квадрат
      arduboy.drawRect(x-15, y-15, 30, 30, WHITE);
      break;
    case 1: // Треугольник
      arduboy.drawTriangle(x-15, y+10, x, y-10, x+15, y+10, WHITE);
      break;
    case 2: // Параллелограмм
      arduboy.drawLine(x-20, y-5, x+10, y-5, WHITE);
      arduboy.drawLine(x+10, y-5, x+15, y+8, WHITE);
      arduboy.drawLine(x+15, y+8, x-15, y+8, WHITE);
      arduboy.drawLine(x-15, y+8, x-20, y-5, WHITE);
      break;
    case 3: // Кораблик
      arduboy.drawLine(x-12, y+8, x, y-8, WHITE);
      arduboy.drawLine(x, y-8, x+12, y+8, WHITE);
      arduboy.drawLine(x+12, y+8, x-12, y+8, WHITE);
      arduboy.drawLine(x-8, y, x+8, y, WHITE);
      break;
  }
}

void handleGameInput() {
  if (!pieceGrabbed) {
    // Режим выбора фигуры
    if (arduboy.justPressed(RIGHT_BUTTON)) {
      selectedPiece = (selectedPiece + 1) % 7;
    }
    if (arduboy.justPressed(LEFT_BUTTON)) {
      selectedPiece = (selectedPiece + 6) % 7;
    }
    if (arduboy.justPressed(A_BUTTON)) {
      pieceGrabbed = true;
      // Фигура появляется в центре области сборки
      pieces[selectedPiece].x = 42;
      pieces[selectedPiece].y = 25;
    }
  } else {
    // Режим перемещения фигуры
    if (arduboy.pressed(LEFT_BUTTON) && pieces[selectedPiece].x > 15) {
      pieces[selectedPiece].x--;
    }
    if (arduboy.pressed(RIGHT_BUTTON) && pieces[selectedPiece].x < 60) {
      pieces[selectedPiece].x++;
    }
    if (arduboy.pressed(UP_BUTTON) && pieces[selectedPiece].y > 10) {
      pieces[selectedPiece].y--;
    }
    if (arduboy.pressed(DOWN_BUTTON) && pieces[selectedPiece].y < 35) {
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
    currentScreen = 1; // Вернуться к выбору уровня
  }
}

// ==================== ПЕСОЧНИЦА ====================
void drawSandboxScreen() {
  arduboy.setCursor(40, 2);
  arduboy.print("SANDBOX MODE");
  
  arduboy.drawLine(0, 12, 127, 12, WHITE);
  
  // Инструкция
  arduboy.setCursor(10, 16);
  arduboy.print("Create your own design!");
  
  // Рисуем все доступные фигуры внизу
  for (int i = 0; i < 7; i++) {
    drawTangramPiece(10 + i * 17, 50, i, 0);
  }
  
  // Область для творчества (центр экрана)
  arduboy.drawRect(30, 25, 68, 20, WHITE);
  arduboy.setCursor(35, 28);
  arduboy.print("Build Area");
  
  // Инструкция
  arduboy.setCursor(5, 58);
  arduboy.print("B:Menu A:Clear");
}

void handleSandboxInput() {
  if (arduboy.justPressed(B_BUTTON)) {
    currentScreen = 0; // Вернуться в меню
  }
}

// ==================== ОБЩИЕ ФУНКЦИИ ====================
void drawTangramPiece(int x, int y, int pieceType, int rotation) {
  // Вращение фигуры (упрощенная версия)
  switch(pieceType) {
    case 0: // Большой треугольник 1
      arduboy.drawTriangle(x, y, x+12, y, x, y+12, WHITE);
      break;
    case 1: // Большой треугольник 2
      arduboy.drawTriangle(x, y, x+12, y, x+12, y+12, WHITE);
      break;
    case 2: // Средний треугольник
      arduboy.drawTriangle(x, y, x+10, y, x, y+10, WHITE);
      break;
    case 3: // Маленький треугольник 1
      arduboy.drawTriangle(x, y, x+8, y, x, y+8, WHITE);
      break;
    case 4: // Маленький треугольник 2
      arduboy.drawTriangle(x, y, x+8, y, x+8, y+8, WHITE);
      break;
    case 5: // Квадрат
      arduboy.drawRect(x, y, 8, 8, WHITE);
      break;
    case 6: // Параллелограмм
      arduboy.drawLine(x, y, x+10, y, WHITE);
      arduboy.drawLine(x+10, y, x+12, y+6, WHITE);
      arduboy.drawLine(x+12, y+6, x+2, y+6, WHITE);
      arduboy.drawLine(x+2, y+6, x, y, WHITE);
      break;
  }
}

int getPieceWidth(int pieceType, int rotation) {
  switch(pieceType) {
    case 0: case 1: return 12;
    case 2: return 10;
    case 3: case 4: case 5: return 8;
    case 6: return 12;
    default: return 8;
  }
}

int getPieceHeight(int pieceType, int rotation) {
  switch(pieceType) {
    case 0: case 1: return 12;
    case 2: return 10;
    case 3: case 4: case 5: return 8;
    case 6: return 6;
    default: return 8;
  }
}