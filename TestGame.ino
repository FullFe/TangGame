#include <Arduboy2.h>
Arduboy2 arduboy;

int x = 60, y = 28;
int currentScreen = 0; // 0 - главное меню, 1 - выбор фигуры, 2 - игровой экран
int selectedShape = 0;

struct Stamp { int x, y, shape; };
Stamp stamps[10];
int stampCount = 0;

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(30);
}

void loop() {
  if (!arduboy.nextFrame()) return;
  arduboy.pollButtons();
  arduboy.clear();
  
  switch (currentScreen) {
    case 0: // Главное меню
      drawMainMenu();
      handleMainMenuInput();
      break;
      
    case 1: // Экран выбора фигуры
      drawShapeSelectionScreen();
      handleShapeSelectionInput();
      break;
      
    case 2: // Игровой экран
      handleGameInput();
      drawGameScreen();
      break;
  }
  
  arduboy.display();
}

void drawMainMenu() {
  arduboy.setCursor(40, 10);
  arduboy.print("STAMP GAME");
  
  arduboy.setCursor(35, 25);
  arduboy.print("A: Start Game");
  
  arduboy.setCursor(35, 35);
  arduboy.print("B: Shape Select");
}

void handleMainMenuInput() {
  if (arduboy.justPressed(A_BUTTON)) {
    currentScreen = 2; // Переход прямо в игру
  }
  if (arduboy.justPressed(B_BUTTON)) {
    currentScreen = 1; // Переход к выбору фигуры
  }
}

void drawShapeSelectionScreen() {
  arduboy.setCursor(30, 5);
  arduboy.print("SELECT SHAPE");
  
  drawShape(20, 25, 0, selectedShape == 0);
  drawShape(60, 25, 1, selectedShape == 1);
  drawShape(100, 25, 2, selectedShape == 2);
  
  arduboy.setCursor(15, 50);
  arduboy.print("A:Start B:Back");
}

void handleShapeSelectionInput() {
  if (arduboy.justPressed(RIGHT_BUTTON)) selectedShape = (selectedShape + 1) % 3;
  if (arduboy.justPressed(LEFT_BUTTON)) selectedShape = (selectedShape + 2) % 3;
  if (arduboy.justPressed(A_BUTTON)) currentScreen = 2;
  if (arduboy.justPressed(B_BUTTON)) currentScreen = 0;
}

void handleGameInput() {
  // Управление движением
  if (arduboy.pressed(LEFT_BUTTON)) x--;
  if (arduboy.pressed(RIGHT_BUTTON)) x++;
  if (arduboy.pressed(UP_BUTTON)) y--;
  if (arduboy.pressed(DOWN_BUTTON)) y++;
  
  // Добавление отпечатка
  if (arduboy.justPressed(A_BUTTON) && stampCount < 10) {
    stamps[stampCount] = {x, y, selectedShape};
    stampCount++;
  }
  
  // Возврат в меню
  if (arduboy.justPressed(B_BUTTON)) {
    currentScreen = 0;
  }
  
  x = constrain(x, 0, 120);
  y = constrain(y, 0, 56);
}

void drawGameScreen() {
  // Рисуем все отпечатки
  for (int i = 0; i < stampCount; i++) {
    drawShape(stamps[i].x, stamps[i].y, stamps[i].shape);
  }
  // Рисуем текущую фигуру
  drawShape(x, y, selectedShape);
  
  // Отображаем информацию
  arduboy.setCursor(0, 0);
  arduboy.print("A:Stamp B:Menu");
}

void drawShape(int posX, int posY, int shape, bool isSelected) {
  if (isSelected) {
    arduboy.drawRect(posX-1, posY-1, 10, 10, WHITE);
  }
  
  if (shape == 0) {
    arduboy.fillRect(posX, posY, 8, 8);
  } else if (shape == 1) {
    arduboy.drawLine(posX+4, posY, posX, posY+7, WHITE);
    arduboy.drawLine(posX, posY+7, posX+8, posY+7, WHITE);
    arduboy.drawLine(posX+8, posY+7, posX+4, posY, WHITE);
  } else {
    arduboy.drawCircle(posX+4, posY+4, 4, WHITE);
  }
}

void drawShape(int posX, int posY, int shape) {
  if (shape == 0) {
    arduboy.fillRect(posX, posY, 8, 8);
  } else if (shape == 1) {
    arduboy.drawLine(posX+4, posY, posX, posY+7, WHITE);
    arduboy.drawLine(posX, posY+7, posX+8, posY+7, WHITE);
    arduboy.drawLine(posX+8, posY+7, posX+4, posY, WHITE);
  } else {
    arduboy.drawCircle(posX+4, posY+4, 4, WHITE);
  }
}