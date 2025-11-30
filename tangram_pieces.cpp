#include "tangram_pieces.h"
#include "constants.h"
#include <math.h>

extern Arduboy2 arduboy;
extern int selectedLevel;

// Функция для поворота точки вокруг центра
void rotatePoint(int& x, int& y, int centerX, int centerY, int rotation) {
  int dx = x - centerX;
  int dy = y - centerY;
  
  switch(rotation % 4) {
    case 0: // 0 градусов
      x = centerX + dx;
      y = centerY + dy;
      break;
    case 1: // 90 градусов
      x = centerX - dy;
      y = centerY + dx;
      break;
    case 2: // 180 градусов
      x = centerX - dx;
      y = centerY - dy;
      break;
    case 3: // 270 градусов
      x = centerX + dy;
      y = centerY - dx;
      break;
  }
}

// Высота равностороннего треугольника со стороной a
int equilateralHeight(int side) {
  return (int)(side * sqrt(3) / 2);
}

void drawTangramPiece(int x, int y, int pieceType, int rotation) {
  int centerX, centerY;
  
  // Для уровня 1 используем новые фигуры
  if (selectedLevel == 0) {
    switch(pieceType) {
      case BIG_TRIANGLE_1: // Большой равносторонний треугольник (сторона 20)
        centerX = x + 10; centerY = y + equilateralHeight(20)/2;
        {
          int x1 = x, y1 = y + equilateralHeight(20);
          int x2 = x + 20, y2 = y + equilateralHeight(20);
          int x3 = x + 10, y3 = y;
          rotatePoint(x1, y1, centerX, centerY, rotation);
          rotatePoint(x2, y2, centerX, centerY, rotation);
          rotatePoint(x3, y3, centerX, centerY, rotation);
          arduboy.drawTriangle(x1, y1, x2, y2, x3, y3, WHITE);
        }
        break;
        
      case BIG_TRIANGLE_2: // Средний равносторонний треугольник (сторона 10)
        centerX = x + 5; centerY = y + equilateralHeight(10)/2;
        {
          int x1 = x, y1 = y + equilateralHeight(10);
          int x2 = x + 10, y2 = y + equilateralHeight(10);
          int x3 = x + 5, y3 = y;
          rotatePoint(x1, y1, centerX, centerY, rotation);
          rotatePoint(x2, y2, centerX, centerY, rotation);
          rotatePoint(x3, y3, centerX, centerY, rotation);
          arduboy.drawTriangle(x1, y1, x2, y2, x3, y3, WHITE);
        }
        break;
        
      case MEDIUM_TRIANGLE: // Второй средний равносторонний треугольник (сторона 10)
        centerX = x + 5; centerY = y + equilateralHeight(10)/2;
        {
          int x1 = x, y1 = y + equilateralHeight(10);
          int x2 = x + 10, y2 = y + equilateralHeight(10);
          int x3 = x + 5, y3 = y;
          rotatePoint(x1, y1, centerX, centerY, rotation);
          rotatePoint(x2, y2, centerX, centerY, rotation);
          rotatePoint(x3, y3, centerX, centerY, rotation);
          arduboy.drawTriangle(x1, y1, x2, y2, x3, y3, WHITE);
        }
        break;
        
      case SMALL_TRIANGLE_1: // Прямоугольник 5x10 
        centerX = x + 2; centerY = y + 5;
        {
          int x1 = x, y1 = y;
          int x2 = x + 5, y2 = y;
          int x3 = x + 5, y3 = y + 10;
          int x4 = x, y4 = y + 10;
          rotatePoint(x1, y1, centerX, centerY, rotation);
          rotatePoint(x2, y2, centerX, centerY, rotation);
          rotatePoint(x3, y3, centerX, centerY, rotation);
          rotatePoint(x4, y4, centerX, centerY, rotation);
          arduboy.drawLine(x1, y1, x2, y2, WHITE);
          arduboy.drawLine(x2, y2, x3, y3, WHITE);
          arduboy.drawLine(x3, y3, x4, y4, WHITE);
          arduboy.drawLine(x4, y4, x1, y1, WHITE);
        }
        break;
        
      case SMALL_TRIANGLE_2: // Прямоугольный треугольник (15, 25, 30)
        centerX = x + 7; centerY = y + 12;
        {
          // Используем катеты 15 и 25
          int x1 = x, y1 = y;
          int x2 = x + 15, y2 = y;
          int x3 = x, y3 = y + 25;
          rotatePoint(x1, y1, centerX, centerY, rotation);
          rotatePoint(x2, y2, centerX, centerY, rotation);
          rotatePoint(x3, y3, centerX, centerY, rotation);
          arduboy.drawTriangle(x1, y1, x2, y2, x3, y3, WHITE);
        }
        break;
        
      case SQUARE: // Маленький квадрат со стороной 5
        centerX = x + 2; centerY = y + 2;
        {
          int x1 = x, y1 = y;
          int x2 = x + 5, y2 = y;
          int x3 = x + 5, y3 = y + 5;
          int x4 = x, y4 = y + 5;
          rotatePoint(x1, y1, centerX, centerY, rotation);
          rotatePoint(x2, y2, centerX, centerY, rotation);
          rotatePoint(x3, y3, centerX, centerY, rotation);
          rotatePoint(x4, y4, centerX, centerY, rotation);
          arduboy.drawLine(x1, y1, x2, y2, WHITE);
          arduboy.drawLine(x2, y2, x3, y3, WHITE);
          arduboy.drawLine(x3, y3, x4, y4, WHITE);
          arduboy.drawLine(x4, y4, x1, y1, WHITE);
        }
        break;
        
      case PARALLELOGRAM: // Не используется в уровне 1
        break;
    }
  } else {
    
    switch(pieceType) {
      case BIG_TRIANGLE_1:
        centerX = x + 6; centerY = y + 6;
        {
          int x1 = x, y1 = y;
          int x2 = x + 12, y2 = y;
          int x3 = x, y3 = y + 12;
          rotatePoint(x1, y1, centerX, centerY, rotation);
          rotatePoint(x2, y2, centerX, centerY, rotation);
          rotatePoint(x3, y3, centerX, centerY, rotation);
          arduboy.drawTriangle(x1, y1, x2, y2, x3, y3, WHITE);
        }
        break;
        
      case BIG_TRIANGLE_2:
        centerX = x + 6; centerY = y + 6;
        {
          int x1 = x, y1 = y;
          int x2 = x + 12, y2 = y;
          int x3 = x + 12, y3 = y + 12;
          rotatePoint(x1, y1, centerX, centerY, rotation);
          rotatePoint(x2, y2, centerX, centerY, rotation);
          rotatePoint(x3, y3, centerX, centerY, rotation);
          arduboy.drawTriangle(x1, y1, x2, y2, x3, y3, WHITE);
        }
        break;
        
      case MEDIUM_TRIANGLE:
        centerX = x + 5; centerY = y + 5;
        {
          int x1 = x, y1 = y;
          int x2 = x + 10, y2 = y;
          int x3 = x, y3 = y + 10;
          rotatePoint(x1, y1, centerX, centerY, rotation);
          rotatePoint(x2, y2, centerX, centerY, rotation);
          rotatePoint(x3, y3, centerX, centerY, rotation);
          arduboy.drawTriangle(x1, y1, x2, y2, x3, y3, WHITE);
        }
        break;
        
      case SMALL_TRIANGLE_1:
        centerX = x + 4; centerY = y + 4;
        {
          int x1 = x, y1 = y;
          int x2 = x + 8, y2 = y;
          int x3 = x, y3 = y + 8;
          rotatePoint(x1, y1, centerX, centerY, rotation);
          rotatePoint(x2, y2, centerX, centerY, rotation);
          rotatePoint(x3, y3, centerX, centerY, rotation);
          arduboy.drawTriangle(x1, y1, x2, y2, x3, y3, WHITE);
        }
        break;
        
      case SMALL_TRIANGLE_2:
        centerX = x + 4; centerY = y + 4;
        {
          int x1 = x, y1 = y;
          int x2 = x + 8, y2 = y;
          int x3 = x + 8, y3 = y + 8;
          rotatePoint(x1, y1, centerX, centerY, rotation);
          rotatePoint(x2, y2, centerX, centerY, rotation);
          rotatePoint(x3, y3, centerX, centerY, rotation);
          arduboy.drawTriangle(x1, y1, x2, y2, x3, y3, WHITE);
        }
        break;
        
      case SQUARE:
        centerX = x + 4; centerY = y + 4;
        {
          int x1 = x, y1 = y;
          int x2 = x + 8, y2 = y;
          int x3 = x + 8, y3 = y + 8;
          int x4 = x, y4 = y + 8;
          rotatePoint(x1, y1, centerX, centerY, rotation);
          rotatePoint(x2, y2, centerX, centerY, rotation);
          rotatePoint(x3, y3, centerX, centerY, rotation);
          rotatePoint(x4, y4, centerX, centerY, rotation);
          arduboy.drawLine(x1, y1, x2, y2, WHITE);
          arduboy.drawLine(x2, y2, x3, y3, WHITE);
          arduboy.drawLine(x3, y3, x4, y4, WHITE);
          arduboy.drawLine(x4, y4, x1, y1, WHITE);
        }
        break;
        
      case PARALLELOGRAM:
        centerX = x + 6; centerY = y + 3;
        {
          int x1 = x, y1 = y;
          int x2 = x + 10, y2 = y;
          int x3 = x + 12, y3 = y + 6;
          int x4 = x + 2, y4 = y + 6;
          rotatePoint(x1, y1, centerX, centerY, rotation);
          rotatePoint(x2, y2, centerX, centerY, rotation);
          rotatePoint(x3, y3, centerX, centerY, rotation);
          rotatePoint(x4, y4, centerX, centerY, rotation);
          arduboy.drawLine(x1, y1, x2, y2, WHITE);
          arduboy.drawLine(x2, y2, x3, y3, WHITE);
          arduboy.drawLine(x3, y3, x4, y4, WHITE);
          arduboy.drawLine(x4, y4, x1, y1, WHITE);
        }
        break;
    }
  }
}

void drawSmallTangramPiece(int x, int y, int pieceType, int rotation) {
  // Для уровня 1 переопределяем маленькие фигуры
  if (selectedLevel == 0) {
    switch(pieceType) {
      case BIG_TRIANGLE_1: // Большой равносторонний треугольник
        arduboy.drawTriangle(x, y+6, x+8, y+6, x+4, y, WHITE);
        break;
      case BIG_TRIANGLE_2: // Средний равносторонний треугольник
      case MEDIUM_TRIANGLE: // Средний равносторонний треугольник
        arduboy.drawTriangle(x, y+3, x+4, y+3, x+2, y, WHITE);
        break;
      case SMALL_TRIANGLE_1: // Прямоугольник 5x10
        arduboy.drawRect(x, y, 3, 6, WHITE);
        break;
      case SMALL_TRIANGLE_2: // Прямоугольный треугольник 
        arduboy.drawTriangle(x, y, x+4, y, x, y+6, WHITE);
        break;
      case SQUARE: // Маленький квадрат 5x5
        arduboy.drawRect(x, y, 3, 3, WHITE);
        break;
      case PARALLELOGRAM: 
        break;
    }
  } else {
    // Стандартные маленькие фигуры для других уровней
    switch(pieceType) {
      case BIG_TRIANGLE_1:
        arduboy.drawTriangle(x, y, x+6, y, x, y+6, WHITE);
        break;
      case BIG_TRIANGLE_2:
        arduboy.drawTriangle(x, y, x+6, y, x+6, y+6, WHITE);
        break;
      case MEDIUM_TRIANGLE:
        arduboy.drawTriangle(x, y, x+5, y, x, y+5, WHITE);
        break;
      case SMALL_TRIANGLE_1:
        arduboy.drawTriangle(x, y, x+4, y, x, y+4, WHITE);
        break;
      case SMALL_TRIANGLE_2:
        arduboy.drawTriangle(x, y, x+4, y, x+4, y+4, WHITE);
        break;
      case SQUARE:
        arduboy.drawRect(x, y, 4, 4, WHITE);
        break;
      case PARALLELOGRAM:
        arduboy.drawLine(x, y, x+5, y, WHITE);
        arduboy.drawLine(x+5, y, x+6, y+3, WHITE);
        arduboy.drawLine(x+6, y+3, x+1, y+3, WHITE);
        arduboy.drawLine(x+1, y+3, x, y, WHITE);
        break;
    }
  }
}

int getPieceWidth(int pieceType, int rotation) {
  if (selectedLevel == 0) {
    switch(pieceType) {
      case BIG_TRIANGLE_1: return 20; 
      case BIG_TRIANGLE_2: 
      case MEDIUM_TRIANGLE: return 10; 
      case SMALL_TRIANGLE_1: return 5;  
      case SMALL_TRIANGLE_2: return 15;
      case SQUARE: return 5;            
      case PARALLELOGRAM: return 0;     
      default: return 8;
    }
  } else {
    // Стандартные размеры
    switch(pieceType) {
      case BIG_TRIANGLE_1: case BIG_TRIANGLE_2: return 12;
      case MEDIUM_TRIANGLE: return 10;
      case SMALL_TRIANGLE_1: case SMALL_TRIANGLE_2: case SQUARE: return 8;
      case PARALLELOGRAM: return 12;
      default: return 8;
    }
  }
}

int getPieceHeight(int pieceType, int rotation) {
  if (selectedLevel == 0) {
    switch(pieceType) {
      case BIG_TRIANGLE_1: return equilateralHeight(20); 
      case BIG_TRIANGLE_2: 
      case MEDIUM_TRIANGLE: return equilateralHeight(10); 
      case SMALL_TRIANGLE_1: return 10; 
      case SMALL_TRIANGLE_2: return 25; 
      case SQUARE: return 5;           
      case PARALLELOGRAM: return 0;     
      default: return 8;
    }
  } else {
    // Стандартные размеры
    switch(pieceType) {
      case BIG_TRIANGLE_1: case BIG_TRIANGLE_2: return 12;
      case MEDIUM_TRIANGLE: return 10;
      case SMALL_TRIANGLE_1: case SMALL_TRIANGLE_2: case SQUARE: return 8;
      case PARALLELOGRAM: return 6;
      default: return 8;
    }
  }
}